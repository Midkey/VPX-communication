#include <iostream>
#include <stdio.h>
#include "vpx_client.h"
#include <string.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	VPX_client *client = new VPX_client();
	printf("Conected VPX!\n");
	while(true)
	{
		Mat img;
		client->recv_img(img);
		// imshow("123",img);
		// waitKey(0);
		printf("recv %d %d\n", img.cols, img.rows);
		client->send_img((char*)img.data, img.cols, img.rows, 3);
		
	}
}
