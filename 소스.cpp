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

class Imgage{

};


int main(int argc, char *argv[])
{
	Mat srcImage = imread("C:\\Users\\sungmin\\Desktop\\sample07.png");
	Mat tempImage;
	Mat dstImage;

	int row = srcImage.rows;
	int col = srcImage.cols;

	resize(srcImage, tempImage, Size(col, row), 0, 0, CV_INTER_LINEAR);
	resize(srcImage, dstImage, Size(col, row), 0, 0, CV_INTER_LINEAR);

	cout << "row : " << srcImage.rows << ", col : " << srcImage.cols << endl;				//col and low count
	cout << "dimensions : " << srcImage.dims << ", total :" << srcImage.total() << endl;	//dimenstion and total num of pixel count


	//srcImage.at<Vec3b>
	//Mat gaussianSmoothedImg;
	//GaussianBlur(srcImage, dstImage, Size(3, 3), 1);


	//canny edge


	//sobel edge
	Mat sobelX;
	Mat sobelY;
	Sobel(srcImage, sobelX, CV_8U, 1, 0);
	Sobel(srcImage, sobelY, CV_8U, 0, 1);
	tempImage = abs(sobelX) + abs(sobelY);


	//Canny(tempImage, // 그레이레벨 영상
	//	dstImage, // 결과 외곽선
	//	100,  // 낮은 경계값
	//	200);  // 높은 경계값
	
	// remove shadow
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (srcImage.at<Vec3b>(r, c)[0] < 70)
			{
				//dstImage.at<Vec3b>(r, c)[0] = 100;
				//dstImage.at<Vec3b>(r, c)[1] = 100;
			
			}
		}
	}

	imshow("source", srcImage);
	imshow("result", dstImage);
	imshow("temp", tempImage);

	waitKey();
	return 0;
}

