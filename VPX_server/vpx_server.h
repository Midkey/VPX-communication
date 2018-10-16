#ifndef VPX_SERVER_H
#define VPX_SERVER_H
#define BUF_SIZE 100
#include "zmq.h"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <time.h>

using namespace cv;

static const char workerIP[5][32] = {
		/* 0 */ "127.0.0.1",
		/* 1 */ "",
		/* 2 */ "",
		/* 3 */ "",
		/* 4 */ ""
		};
class VPX_server{
	public:
		VPX_server();
		~VPX_server();
		void send_img(int wid, char *img, int width, int height, int channel);
		void recv_img(int &id, Mat &img);
		void send_data(int wid, char* str, uint32_t inDataSize);
		void recv_data(int &id, char* &data, int &data_size);
	private:
		int wid;
	    	void *worker[5];
	    	uint32_t inDataSize, outDataSize;
	    	void *context;
	    	void *receiver;
		
};

#endif
