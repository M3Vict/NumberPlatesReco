#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	// Czesc to jest test!
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
	cout << "????";
	return 0;
}