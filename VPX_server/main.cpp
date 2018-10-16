#include <opencv2/opencv.hpp>
#include <iostream>
#include "vpx_server.h"
#include <string.h>
using namespace cv;
using namespace std;   

int main()

{
	VPX_server *server = new VPX_server();
	int id;
	Mat img = imread("1.tif");
	int client_num = 5;
	int width = img.cols;
	int height = img.rows;
	int sub_width = width/client_num;
	for (int wid=0; wid < client_num; wid++){
		Mat sub_img;
		printf("%d, %d\n", wid, sub_width*wid);
		if (wid != client_num-1)
			img(Rect(sub_width*wid, 0, sub_width,height)).copyTo(sub_img);
		else
			img(Rect(sub_width*wid, 0, width-sub_width*wid,height)).copyTo(sub_img);
		server->send_img(0, (char*)sub_img.data, sub_img.cols, sub_img.rows, 3);
	}
	
	Mat output = Mat(height, width, CV_8UC3);
	for (int wid=0; wid < client_num; wid++){
		int id;
		Mat image;
		server->recv_img(id, image);
		printf("recv %d\n", id);
		if (wid != client_num-1)
			image.copyTo(output(Rect(sub_width*wid, 0, sub_width, height)));
		else
			image.copyTo(output(Rect(sub_width*wid, 0, width-sub_width*wid, height)));
	}
	imshow("123",output);
	waitKey(0);
	getchar();
}


