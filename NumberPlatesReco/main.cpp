#include <iostream>
#include <string>


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	string source= "C:\\Users\\Admin\\Desktop\\Garmin Dash Cam 55 Plus Sample Footage.mp4";
	//cin >> source;

	VideoCapture video(source);
	if (!video.isOpened())
	{
		cout << "Fatal ERROR! Could not open video file"<<source<<endl;
		return 1;
	}
	
	Rect trac_frame(300, 200, 100, 50);
	//MAT roi = frame(trac)
	
	while (true)
	{
		Mat frame;
		video >> frame;
		if (frame.empty())
			break;
		imshow("Video", frame);
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
		
	}

	return 0;
}