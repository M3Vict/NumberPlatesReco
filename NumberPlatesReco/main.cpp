#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	//tu Artur
	//UWAGA ostatni test! przysięgam
	//Tu Michal
	VideoCapture cap(0);
	if (!cap.isOpened())
		return 1;
	for (;;)
	{
		Mat frame;
		cap >> frame;
		imshow("Webcam", frame);

		if (waitKey(30) >= 0)
			break;
	}
	// Wgl ja mam na czerwono to i jako b³êdy :|
	// Ju¿ nie :)
	// Test
	return 0;
}