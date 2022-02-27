#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
    VideoCapture cap("ball.mp4");
    Mat frame,frame_hsv,frame_thresshold;

    int L_H = 0;
    int L_S = 100;
    int L_V = 0;

    int H_H = 13;
    int H_S = 255;
    int H_V = 255;


    namedWindow("TRACKBAR",WINDOW_AUTOSIZE);
    createTrackbar("low h","TRACKBAR",&L_H,179);
    createTrackbar("low s","TRACKBAR",&L_S,255);
    createTrackbar("low v","TRACKBAR",&L_V,255);

    createTrackbar("high h","TRACKBAR",&H_H,179);
    createTrackbar("high s","TRACKBAR",&H_S,255);
    createTrackbar("high v","TRACKBAR",&H_V,255);

    while (1)
    {
        cap >> frame;
        cvtColor(frame,frame_hsv,COLOR_BGR2HSV);
        inRange(frame_hsv,Scalar(L_H,L_S,L_V),Scalar(H_H,H_S,H_V),frame_thresshold);

        //FOR DETECTING COUNTOUR
        vector<vector<Point>>countours;
        vector<Vec4i>hierarchy;

        findContours(frame_thresshold,countours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        for (int i = 0; i < countours.size(); i++)
        {   
            vector<Point>kontur_baru;
            Point2f center;
            float radius;
            kontur_baru = countours[i];
            minEnclosingCircle(kontur_baru,center,radius);
            if (radius>100)
            {
                circle(frame,center,radius,Scalar(0,255,0),3);
            }
        }
        
        imshow("windows",frame);
        imshow("thress",frame_thresshold);
        char key = (char)waitKey(100);
        if (key == 'q')
        {
            break;
        }

    }
    
    cap.release();
    destroyAllWindows();
    return 0;
}
