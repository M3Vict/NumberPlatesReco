/*#include <iostream>
#include <string>


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void detectAndDisplay(Mat frame);

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

int main()
{
	//string source= "C:\\Users\\Admin\\Desktop\\Garmin Dash Cam 55 Plus Sample Footage.mp4";
	string source = "C:\\Users\\Admin\\Desktop\\Megamind.avi";
	//string source = "C:\\Users\\Admin\\Desktop\\samochody.mp4";
	//cin >> source;

	String face_cascade_name = "C:\\Users\\Admin\\Desktop\\faces.xml";
	String eyes_cascade_name = "C:\\Users\\Admin\\Desktop\\eyes.xml";
	if (!face_cascade.load(face_cascade_name))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	};
	if (!eyes_cascade.load(eyes_cascade_name))
	{
		cout << "--(!)Error loading eyes cascade\n";
		return -1;
	};


	VideoCapture video(source);
	if (!video.isOpened())
	{
		cout << "Fatal ERROR! Could not open video file"<<source<<endl;
		return 1;
	}
	Mat frame;
	video >> frame;

	/*Rect track_frame(300, 200, 100, 50);
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

	TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 15, 2);
	*/

/*	while (true)
	{
		
		video >> frame;
		if (frame.empty())
			break;


		/*Mat hsv, dst;
		cvtColor(frame, hsv, COLOR_BGR2HSV);

		calcBackProject(&hsv, 1, channels, roi_hist, dst, range);
		//imshow("Video", roi_hist);

		RotatedRect rot_rect = CamShift(dst, track_frame, term_crit);

		Point2f points[4];
		rot_rect.points(points);
		for (int i = 0; i < 4; i++)
		{
			line(frame, points[i], points[(i + 1) % 4], 255, 2);
			cout << "punkt 1:" << points[i] << " " << "punkt 2:" << points[(i + 1) % 4] << endl;
		}*/	

/*
		//imshow("Video", frame);
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;		
	}

	return 0;
}
*/

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
int main(int argc, const char** argv)
{
    String face_cascade_name = "C:\\Users\\Admin\\Desktop\\faces.xml";
    String eyes_cascade_name = "C:\\Users\\Admin\\Desktop\\eyes.xml";
    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    if (!eyes_cascade.load(eyes_cascade_name))
    {
        cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };
    string camera_device = "C:\\Users\\Admin\\Desktop\\Megamind.avi";
    VideoCapture capture;
    capture.open(0);
    if (!capture.isOpened())
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    Mat frame;
    while (capture.read(frame))
    {
        if (frame.empty())
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame);
        if (waitKey(10) == 27)
        {
            break; // escape
        }
    }
    return 0;
}
void detectAndDisplay(Mat frame)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);
    for (size_t i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
        Mat faceROI = frame_gray(faces[i]);
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale(faceROI, eyes);
        for (size_t j = 0; j < eyes.size(); j++)
        {
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle(frame, eye_center, radius, Scalar(255, 0, 0), 4);
        }
    }
    //-- Show what you got
    imshow("Capture - Face detection", frame);
}

