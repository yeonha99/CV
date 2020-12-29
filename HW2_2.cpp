//12181833 ��ǻ�ͺ��� HW2_2
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
	imshow("����", image);
	cvtColor(image, gray, COLOR_RGB2GRAY);
	my_corner(image, gray);
	waitKey();
	return 0;
}
void  my_corner(Mat src,Mat gray) {
	Mat inputImage = gray;

	inputImage.convertTo(inputImage, CV_32F, 1.0 / 255, 0);

	medianBlur(inputImage, inputImage, 3);//������ ���� ��ó��

	Mat grad_x(inputImage.size(), inputImage.type());//x�� ���� �̺� ��� ������ ����
	Mat grad_y(inputImage.size(), inputImage.type());//y�� ���� �̺� ����� ������ ����
	int width = inputImage.cols;
	int height = inputImage.rows;
	float Marr[2][2] = {0,0,0,0};//M��Ʈ���� �� ���� 2X2

	int r, c;
	float sum;

	//X ���� sobel
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			sum = 0; //0���� �ʱ�ȭ
			for (r = 0; r < 3; r++)
				for (c = 0; c < 3; c++)
					sum += (MaskSobelX[r][c] * inputImage.at<float>(i + r - 1, j + c - 1));
			grad_x.at<float>(i, j) = sum;
		}
	}


	//y ���� sobel
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{

			sum = 0; //0���� �ʱ�ȭ
			for (r = 0; r < 3; r++)
				for (c = 0; c < 3; c++)
					sum += (MaskSobelY[r][c] * inputImage.at<float>(i + r - 1, j + c - 1));
			grad_y.at<float>(i, j) = sum;
		}
	}
	//M��� �����,R����ϱ�
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
	
	//threshold����
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			if (R.at<float>(i, j) < 50) {
				R.at<float>(i, j) = 0;
			}
		}
	}
	imshow("finale_R", R);

	//���� threshold�� ����� ������� ���׶�� �׸���
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			if (R.at<float>(i, j) > 0) {
				circle(src, Point(i, j), 2, Scalar(0, 0, 255));
			}
		}
	}
	imshow("���� ����", src);

}