#include <opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#define SIZE 512
#define FILTERSIZE 
#define M_PI 3.141592
#define M_E 2.7182818284590452353

using namespace cv;
using namespace std;



int main(int argc, char *argv[])
{
	Mat srcImage = imread("C:\\Users\\sungmin\\Desktop\\sample02.png");
	Mat tempImage;
	Mat dstImage;




	resize(srcImage, tempImage, Size(779, 616), 0, 0, CV_INTER_LINEAR);

	resize(srcImage, dstImage, Size(779, 616), 0, 0, CV_INTER_LINEAR);

	cout << "row : " << srcImage.rows << ", col : " << srcImage.cols << endl;				//col and low count
	cout << "dimensions : " << srcImage.dims << ", total :" << srcImage.total() << endl;	//dimenstion and total num of pixel count

	int row = srcImage.rows;
	int col = srcImage.cols;

	Mat inputImg;
	Mat spImg;


	Mat gaussianSmoothedImg;
	//GaussianBlur(srcImage, dstImage, Size(3, 3), 1);


	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			//dstImage.at<uchar>(r, c) = 0;		
		}
	}

	//Canny(srcImage, dstImage, 30,90, 3);
	/*
	vector<Vec4i> lines;
	HoughLinesP(dstImage, lines, 1, CV_PI / 180, 30, 30, 3);
	for (int i = 0; i < lines.size(); i++){
		Vec4i L = lines[i];
		line(dstImage, Point(L[0], L[1]), Point(L[2], L[3]), Scalar(0, 0, 255), 1);
	}
	*/
	



	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (srcImage.at<uchar>(r, c) > 100 && srcImage.at<uchar>(r, c) < 150)
			{
				dstImage.at<uchar>(r, c) = srcImage.at<uchar>(r,c);
			}
		}
	}

	//canny edge


	//sobel edge
	//Mat sobelX;
	//Mat sobelY;
	//Sobel(srcImage, sobelX, CV_8U, 1, 0);
	//Sobel(srcImage, sobelY, CV_8U, 0, 1);
	//tempImage = abs(sobelX) + abs(sobelY);


	//Canny(tempImage, // 그레이레벨 영상
	//	dstImage, // 결과 외곽선
	//	500,  // 낮은 경계값
	//	500);  // 높은 경계값
	



	imshow("source", srcImage);
	imshow("result", dstImage);
	//imshow("temp", tempImage);

	waitKey();
	return 0;
}

