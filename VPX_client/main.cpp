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
	char a;
	while(true)
	{
		client->recv_data();
		printf("%s\n", client->data);
		a = getchar();
		while(getchar()!='\n') continue;
		client->send_data(&a, 1);
		
		if (a=='Y'){
			Mat img;
			client->recv_img(img);
			//img = Mat(client->height, client->width, CV_8UC3, (uchar*)client->img);
			imshow("123",img);
			waitKey(0);
			client->send_img((char*)img.data, img.cols, img.rows, 3);
		}
		else{
			printf("No!\n");
			break;
		}
		
	}
}
