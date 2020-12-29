//12181833 컴퓨터비전 HW2_2
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

float MaskSobelX[3][3] = { {-1,0,1},
								{-2,0,2},
								{-1,0,1} };
float MaskSobelY[3][3] = { {1,2,1},
						{0,0,0},
					{-1,-2,-1} };
void my_corner(Mat src, Mat gray);
int main() {

	Mat image = imread("test2.jpg", 1);
	Mat gray;
	imshow("원본", image);
	cvtColor(image, gray, COLOR_RGB2GRAY);
	my_corner(image, gray);
	waitKey();
	return 0;
}
void  my_corner(Mat src,Mat gray) {
	Mat inputImage = gray;

	inputImage.convertTo(inputImage, CV_32F, 1.0 / 255, 0);

	medianBlur(inputImage, inputImage, 3);//노이즈 제거 전처리

	Mat grad_x(inputImage.size(), inputImage.type());//x에 대한 미분 결과 저장할 변수
	Mat grad_y(inputImage.size(), inputImage.type());//y에 대한 미분 결과를 저장할 변수
	int width = inputImage.cols;
	int height = inputImage.rows;
	float Marr[2][2] = {0,0,0,0};//M메트릭스 값 저장 2X2

	int r, c;
	float sum;

	//X 방향 sobel
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			sum = 0; //0으로 초기화
			for (r = 0; r < 3; r++)
				for (c = 0; c < 3; c++)
					sum += (MaskSobelX[r][c] * inputImage.at<float>(i + r - 1, j + c - 1));
			grad_x.at<float>(i, j) = sum;
		}
	}


	//y 방향 sobel
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{

			sum = 0; //0으로 초기화
			for (r = 0; r < 3; r++)
				for (c = 0; c < 3; c++)
					sum += (MaskSobelY[r][c] * inputImage.at<float>(i + r - 1, j + c - 1));
			grad_y.at<float>(i, j) = sum;
		}
	}
	//M행렬 만들기,R계산하기
	Mat R(inputImage.size(), inputImage.type());
	for (int i = 1; i < height-1; i++) {
		for (int j = 1; j < width-1; j++) {
			Marr[0][0] = pow(grad_x.at<float>(i, j), 2);
			Marr[0][1] = grad_x.at<float>(i, j) * grad_y.at<float>(i, j);
			Marr[1][1] = pow(grad_y.at<float>(i, j), 2);
			Marr[1][0] = grad_x.at<float>(i, j) * grad_y.at<float>(i, j);
			R.at<float>(i, j) = Marr[0][0] * Marr[1][1] - 0.04 * pow((Marr[0][0] + Marr[1][1]), 2);
		}
	}

	imshow("R", R);
	
	//threshold적용
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			if (R.at<float>(i, j) < 50) {
				R.at<float>(i, j) = 0;
			}
		}
	}
	imshow("finale_R", R);

	//최종 threshold한 결과를 기반으로 동그라미 그리기
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			if (R.at<float>(i, j) > 0) {
				circle(src, Point(i, j), 2, Scalar(0, 0, 255));
			}
		}
	}
	imshow("최종 검출", src);

}