#include <iostream>
#include <malloc.h>
#include <opencv2/opencv.hpp>

#include "vpx_client.h"
#include "zmq.h"
#pragma comment(lib,"WS2_32")
using namespace std;
using namespace cv;


VPX_client::VPX_client(){
	context = zmq_ctx_new();

    //  Socket to send messages to
    sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://127.0.0.1:5558");
    printf("Connected to Server.\n");
    //  Socket to receive messages on
    receiver = zmq_socket(context, ZMQ_PULL);
    zmq_bind(receiver, "tcp://*:5557");
    zmq_recv(receiver, (char *)&id, sizeof(int), 0);
}

void VPX_client::send_img(char *img, int width, int height, int channel=3){
	zmq_send(sender, &id, sizeof(int), 0);
	zmq_send(sender, (const char*)&width, 4, 0); 
	zmq_send(sender, (const char*)&height, 4, 0);
	int len = width * height * channel;
	zmq_send(sender, img, len, 0);
}

void VPX_client::recv_img(Mat &image){
	int width;
	int height;
	char* img = NULL;
	// zmq_recv(receiver, &id, sizeof(int), 0);
	zmq_recv(receiver, (char *)&width, 4, 0);
	zmq_recv(receiver, (char *)&height, 4, 0);
	printf("clos:%d\nrows:%d\n", width, height);

	int len = width*height*3;
	img = (char*)malloc(sizeof(char)*len);
	zmq_recv(receiver, img, len, 0);
	image = Mat(height, width, CV_8UC3, img);
}


void VPX_client::recv_data(){
	// zmq_recv(receiver, &id, sizeof(int), 0);
	zmq_recv(receiver, (char *)&len, sizeof(int), 0);
	free(data);
	data = (char*)malloc(sizeof(char)*len);
	zmq_recv(receiver, data, len, 0);
}

void VPX_client::send_data(char* str,int inDataSize)
{

	zmq_send(sender, &id, sizeof(int), ZMQ_SNDMORE);
	zmq_send(sender, &inDataSize, sizeof(uint32_t), ZMQ_SNDMORE);
	zmq_send(sender, str, inDataSize, 0);
}

VPX_client::~VPX_client(){
	zmq_close(receiver);
    zmq_close(sender);
    zmq_ctx_destroy(context);
}
