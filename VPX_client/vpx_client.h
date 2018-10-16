#ifndef VPX_CLIENT_H
#define VPX_CLIENT_H
#define BUF_SIZE 100
#include "zmq.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


class VPX_client{
public:
	VPX_client();
	~VPX_client();
	void recv_img(Mat &image);
	void recv_data();
	void send_data(char* str,int inDataSize);
	void send_img(char *img, int width, int height, int channel);

	void *receiver;
	void *sender;
	void *context;
	int width;
	int height;
	char* img;
	int len;
	char* data;
	
private:
	int id;
};

#endif

