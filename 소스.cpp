#include <opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

#define SIZE 512
#define FILTERSIZE 



using namespace cv;
using namespace std;

class Imgage{

};

class Color{
	int color[3];
};


int main(int argc, char *argv[])
{
	int MASTSIZE = 7;
	Mat srcImage = imread("C:\\Users\\sungmin\\Desktop\\sample07.png");

	int row = srcImage.rows;
	int col = srcImage.cols;

	Mat tempImage;		
	Mat dstImage;
	Mat dstImage2;											// 도로의 후보지 선정
	Mat dstImage3;

	Mat grayImage = Mat(row, col, CV_8UC1, Scalar(0));		//그레이 이미지

	resize(srcImage, tempImage, Size(col, row), 0, 0, CV_INTER_LINEAR);
	resize(srcImage, dstImage, Size(col, row), 0, 0, CV_INTER_LINEAR);
	resize(srcImage, dstImage2, Size(col, row), 0, 0, CV_INTER_LINEAR);
	resize(srcImage, dstImage3, Size(col, row), 0, 0, CV_INTER_LINEAR);

	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			dstImage.at<Vec3b>(r, c)[0] = 255;
			dstImage.at<Vec3b>(r, c)[1] = 255;
			dstImage.at<Vec3b>(r, c)[2] = 255;
		}
	}

	//test
	for (int r = 0; r < MASTSIZE; r++)
	{
		for (int c = 0; c < MASTSIZE; c++)
		{
			dstImage.at<Vec3b>(r, c)[0] = 0;
			dstImage.at<Vec3b>(r, c)[1] = 0;
			dstImage.at<Vec3b>(r, c)[2] = 0;
		}
	}

	int border;
	border = ( MASTSIZE + 1) / 2;
	Mat BoderMat;
	//padding만드는 부분
	copyMakeBorder(srcImage, BoderMat, border, border, border, border, BORDER_REPLICATE, 0);
	// 주위를 복사 

	// 이진화
	Mat temp;
	int sum = 0;
	int mean = 0;
	int sMean = 0;
	int sSum = 0;

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			temp = BoderMat(Rect(c, r, MASTSIZE, MASTSIZE));
			sum = 0;
			sSum = 0;

			for (int i = 0; i < MASTSIZE; i++)
			{
				for (int j = 0; j < MASTSIZE; j++)
				{
					sum += (temp.at<Vec3b>(i, j)[0] + temp.at<Vec3b>(i, j)[1] + temp.at<Vec3b>(i, j)[2]) / 3;

					
				}
			}
			mean = sum /( MASTSIZE * MASTSIZE );

			//cout << sMean << endl;

			if (60 < mean && mean < 100 )
			{
				dstImage.at<Vec3b>(r, c)[0] = 0;
				dstImage.at<Vec3b>(r, c)[1] = 0;
				dstImage.at<Vec3b>(r, c)[2] = 0;
			}
		}
	}
	//그림자
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (srcImage.at<Vec3b>(r, c)[2] < 50
				&& srcImage.at<Vec3b>(r, c)[1] < 60
				&& srcImage.at<Vec3b>(r, c)[0] < 90
				&& srcImage.at<Vec3b>(r, c)[2] < srcImage.at<Vec3b>(r, c)[1]
				&& srcImage.at<Vec3b>(r, c)[1] < srcImage.at<Vec3b>(r, c)[0])
			{
				dstImage.at<Vec3b>(r, c)[0] = 0;
				dstImage.at<Vec3b>(r, c)[1] = 0;
				dstImage.at<Vec3b>(r, c)[2] = 0;
			}
		}
	}// 도로 후보 검출 이진화
	
	
	//

	MASTSIZE = 9;

	Mat BoderMat2;

	copyMakeBorder(dstImage, BoderMat2, border, border, border, border, BORDER_REPLICATE, 0);

	int diff;

	for (int r = 0; r < row - MASTSIZE; r++)
	{
		for (int c = 0; c < col - MASTSIZE; c++)
		{

			temp = BoderMat2(Rect(c, r, MASTSIZE, MASTSIZE));
			sum = 0;
			for (int i = 0; i < MASTSIZE; i++)
			{
				for (int j = 0; j < MASTSIZE; j++)
				{
					sum += (temp.at<Vec3b>(i, j)[0] + temp.at<Vec3b>(i, j)[1] + temp.at<Vec3b>(i, j)[2]) / 3;
				}
			}
			mean = sum / (MASTSIZE*MASTSIZE);
			//cout << mean << endl;
			if (mean < 10)
			{
				for (int i = 0; i < MASTSIZE; i++)
				{
					for (int j = 0; j < MASTSIZE; j++)
					{
						dstImage2.at<Vec3b>(r + i, c + j)[0] = 0;
						dstImage2.at<Vec3b>(r + i, c + j)[1] = 0;
						dstImage2.at<Vec3b>(r + i, c + j)[2] = 0;
					}
				}
			}
		}
	}	





	//sobel edge
	Mat sobelImage;
	Mat sobelX;
	Mat sobelY;
	Sobel(srcImage, sobelX, CV_8U, 1, 0);
	Sobel(srcImage, sobelY, CV_8U, 0, 1);
	sobelImage = abs(sobelX) + abs(sobelY);

	//canny edge
	Mat cannyImage;
	Canny(srcImage, // 그레이레벨 영상
		cannyImage, // 결과 외곽선
		100,  // 낮은 경계값
		200);  // 높은 경계값
	
	Mat erodeImage, dilatedImage;
	Mat mask = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));

	erode(dstImage, erodeImage, mask, Point(-1, -1), 1);
	dilate(erodeImage, dilatedImage, mask, Point(-1, -1), 2);


	Mat gaussianSmoothedImg;
	GaussianBlur(srcImage, gaussianSmoothedImg, Size(3, 3), 3);

	//imshow("source", srcImage);

	imshow("source", srcImage);
	imshow("candidate", dstImage);
	//imshow("grayImage", grayImage);
	imshow("result2", dstImage2);
	//imshow("result3", dstImage3);
	
	//imshow("canny", cannyImage);
	//imshow("sobel", sobelImage);
	//imshow("erode", erodeImage);
	imshow("dilate", dilatedImage);
	//imshow("temp", tempImage);
	//imshow("bluring", gaussianSmoothedImg);

	waitKey();
	return 0;
}

