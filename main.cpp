//opencv
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>

#include <unistd.h>

using namespace cv;
using namespace std;
 

int main(int argc, char* argv[])
{
	Mat camDirBack;
	Mat camDirLaser;
	Mat camEsqBack;
	Mat camEsqLaser;
	Mat dst;

	int imageCount = 0;

	int op = 1;

	VideoCapture camEsq(1);
	VideoCapture camDir(2);

	camEsq.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	camEsq.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
	camEsq.set(CV_CAP_PROP_FPS, 5);
	//camEsq.set(CV_CAP_PROP_CONVERT_RGB, true);


	camDir.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	camDir.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
	camDir.set(CV_CAP_PROP_FPS, 5);
	//camDir.set(CV_CAP_PROP_CONVERT_RGB, true); 

	while(true) {

		cout << "Capturando background (pressione ESC)\n"; 
		while(true) {
			camDir >> camDirBack;
			camEsq >> camEsqBack;
			threshold(camEsqBack, camEsqBack, 235, 255, CV_THRESH_BINARY_INV);
			imshow("oi", camDirBack);
			if (waitKey(30) >= 0)
				break;

		}
		cout << "Capturando com laser (pressione ESC)\n"; 
		while(true) {
			camDir >> camDirLaser;
			camEsq >> camEsqLaser;
			threshold(camEsqLaser, camEsqLaser, 235, 255, CV_THRESH_BINARY_INV);
			imshow("oi", camDirLaser);
			if (waitKey(30) >= 0)
				break;
		}
  

		absdiff(camEsqLaser, camEsqBack, dst);
		
		

		int dilation_size = 2;

		Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(2*dilation_size + 1, 2*dilation_size+1));

		dilate(dst, dst, element1);

		//threshold(dst, dst, 235, 255, CV_THRESH_BINARY_INV);


		cout << "Fotos capturadas (pressione ESC)" << endl;
		while(true) {



			
			namedWindow("oi", 0);
			resizeWindow("oi", 500,500);
			imshow("oi", dst);
			if (waitKey(30) >= 0)
				break;
		}
		

		imageCount++;

	} 
	
}