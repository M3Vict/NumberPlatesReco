#include <iostream>
#include <string>


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	//string source= "C:\\Users\\Admin\\Desktop\\Garmin Dash Cam 55 Plus Sample Footage.mp4";
	string source = "C:\\Users\\Admin\\Desktop\\Megamind.avi";
	//cin >> source;

	VideoCapture video(source);
	if (!video.isOpened())
	{
		cout << "Fatal ERROR! Could not open video file"<<source<<endl;
		return 1;
	}
	Mat frame;
	video >> frame;

	Rect track_frame(300, 200, 100, 50);
	Mat roi = frame(track_frame), hsv_roi, mask;
	cvtColor(roi, hsv_roi, COLOR_BGR2HSV);
	inRange(hsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mask);

	float range_[] = { 0, 180 };
	const float* range[] = { range_ };
	Mat roi_hist;
	int histSize[] = { 180 };
	int channels[] = { 0 };
	calcHist(&hsv_roi, 1, channels, mask, roi_hist, 1, histSize, range);
	normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);

	TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);

	while (true)
	{
		Mat hsv, dst;
		video >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		calcBackProject(&hsv, 1, channels, roi_hist, dst, range);

		RotatedRect rot_rect = CamShift(dst, track_frame, term_crit);

		Point2f points[4];
		rot_rect.points(points);
		for (int i = 0; i < 4; i++)
			line(frame, points[i], points[(i + 1) % 4], 255, 2);

		imshow("Video", frame);
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
		
	}

	return 0;
}