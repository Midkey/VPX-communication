#include <iostream>
#include "vpx_server.h"
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
//#pragma comment(lib,"WS2_32")
using namespace std;
using namespace cv;


VPX_server::VPX_server(){
	char address[32];
	context = zmq_ctx_new();
	receiver = zmq_socket(context, ZMQ_PULL);
    zmq_bind(receiver, "tcp://*:5558");
	
	for (wid = 0; wid < 5; wid++) {
		if (strlen(workerIP[wid]) == 0)
			continue;
	
        sprintf(address, "tcp://%s:5557", workerIP[wid]);
        worker[wid] = zmq_socket(context, ZMQ_PUSH);
        zmq_connect(worker[wid], address);
        zmq_send(worker[wid], (char*)&wid, sizeof(int), 0); 
        printf("Connected %s\n", address);
	}
}

void VPX_server::send_img(int wid, char *img, int width, int height, int channel=3){
	// zmq_send(sender, &id, sizeof(int), ZMQ_SNDMORE);
	zmq_send(worker[wid], (const char*)&width, 4, 0); 
	zmq_send(worker[wid], (const char*)&height, 4, 0);
	int len = width * height * channel;
	zmq_send(worker[wid], img, len, 0);
}

void VPX_server::recv_img(int &id, Mat &image){
	int width;
	int height;
	char* img = NULL;
	zmq_recv(receiver, &id, sizeof(int), 0);
	zmq_recv(receiver, (char *)&width, 4, 0);
	zmq_recv(receiver, (char *)&height, 4, 0);
	printf("clos:%d\nrows:%d\n", width, height);

	int len = width*height*3;
	img = (char*)malloc(sizeof(char)*len);
	zmq_recv(receiver, img, len, 0);
	image = Mat(height, width, CV_8UC3, img);
}

void VPX_server::send_data(int wid, char* str,uint32_t inDataSize)
{
	// zmq_send(worker[wid], &id, sizeof(int), ZMQ_SNDMORE);
	zmq_send(worker[wid], &inDataSize, sizeof(int), 0);
	zmq_send(worker[wid], str, inDataSize, 0);
}

void VPX_server::recv_data(int &id, char* &data, int &data_size)
{
	zmq_recv(receiver, &id, sizeof(int), 0);
    zmq_recv(receiver, &data_size, sizeof(int), 0);
	data = (char*)malloc(sizeof(char)*(data_size));
    zmq_recv(receiver, data, data_size, 0);
}


VPX_server::~VPX_server(){
	zmq_close(receiver);
    zmq_ctx_destroy(context);
	for (wid = 0; wid < 5; wid++) {
		if (workerIP[wid] == "")
			continue;
		zmq_close(worker[wid]);
	}
}
