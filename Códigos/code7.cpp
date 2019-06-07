/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ 
- apresentação e desenvolvimento de algoritmo para trabalhar com conversção de distintas formatações de cores
*/
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp" 
#include <iostream>

using namespace cv;
using namespace std;

char *source_window = "Video";
char *channel_1 = "Canal 1";
char *channel_2 = "Canal 2";
char *channel_3 = "Canal 3";

Mat src, dst;
vector<Mat> channels(3);

int main( int argc, char* argv[] )
{
	namedWindow(source_window, WINDOW_NORMAL);
	namedWindow(channel_1, WINDOW_NORMAL);
	namedWindow(channel_2, WINDOW_NORMAL);
	namedWindow(channel_3, WINDOW_NORMAL);

	char* videoName = argv[1];

	VideoCapture cap(videoName);

	if ( !cap.isOpened() )
	{
		cout << "Erro ao abrir o video" << endl;
		return -1;
	}   

	while (waitKey(33) != 27 && cap.isOpened())
	{
		cap.read(src);

		cvtColor(src , dst , CV_RGBA2RGB);
		//cvtColor(src, dst, CV_BGR2HSV);
		//cvtColor(src, dst, CV_BGR2HLS);
		split(dst, channels);

		imshow(source_window, src);
		imshow(channel_1, channels[0]);
		imshow(channel_2, channels[1]);
		imshow(channel_3, channels[2]);

		waitKey(0);
	}

	return 0;
}
