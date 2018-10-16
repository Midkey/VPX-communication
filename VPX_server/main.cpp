#include <opencv2/opencv.hpp>
#include <iostream>
#include "vpx_server.h"
#include <string.h>
using namespace cv;
using namespace std;   

int main()

{
	VPX_server *server = new VPX_server();
	char aa[50];
	int id;
	char* data;
	int data_size;
	while(1)
	{	
		char msg[] = "Do you want to watch picture?[Y/N]";
		server->send_data(0, msg, strlen(msg));
		server->recv_data(id, data, data_size);
		if (*data == 'Y'){
			Mat img = imread("1.png");
			Mat img2;
			int id;
			printf("cols:%d\nrows:%d\nchannels:%d\n", img.rows, img.cols, img.channels());
			server->send_img(0, (char*)img.data, img.cols, img.rows, 3);
			server->recv_img(id, img2);
			printf("recive %d\n", id);
			imshow("123",img2);
			waitKey(0);
		}
		else{
			printf("No!\n");
			break;
		}
		
		// cin >> aa;
		// server->send_data(0, aa, strlen(aa)+1);
		// server->recv_data(outId, outData, inDataSize);
		// printf("recv %s\n", server->data);
	}

}


