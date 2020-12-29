//12181833_������_HW2_1
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

float MaskSobelX[3][3] = { {-1,0,1},
								{-2,0,2},
								{-1,0,1} };
float MaskSobelY[3][3] = { {1,2,1},
						{0,0,0},
					{-1,-2,-1} };
Mat my_Hog(Mat src);

void get_persentage(Mat comp) {//������׷��� ��ġ�� ��� 
	long  equal = 0;

	long  all = comp.rows * comp.cols;//��ü�ȼ��� ���
	for (int i = 0; i < comp.rows; i++) {//��ġ�ϴ� �ȼ��� ���
		for (int j = 0; j < comp.cols; j++) {
			if (comp.ptr<uchar>(i)[j] != 0) {//0�� �ƴ϶�� �� ��ġ �� ���
				equal++;//��ġ�� ����
			}

		}
	}
	cout << "��ġ�ȼ��� : " << equal << endl;
	cout << "��ü�ȼ��� : " << all << endl;
}

Mat show_histogram(std::string const& name, cv::Mat1b const& image, std::string const& name2) {
	
	int bins = 30;//30�� ���� �������� ���ڿ� �߱� ������ bin�� ������ 30���� ����
	int histSize[] = { bins };
	
	float lranges[] = { 0, 330 };//0���� 360�������� ���� ������׷� 360�� 0���� �����ϹǷ� �̷��� ǥ���Ѵ�.
	const float* ranges[] = { lranges };

	Mat hist;
	int channels[] = { 0 };

	
	int const hist_height = 255;
	Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

	calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

	double max_val = 0;
	minMaxLoc(hist, 0, &max_val);

	// visualize each bin
	for (int b = 0; b < bins; b++) {
		float const binVal = hist.at<float>(b);
		int   const height = cvRound(binVal * hist_height / max_val);//����ȭ�Ͽ� ���� ��Ÿ�� �� norm1�� ǥ��
		cv::line
		(hist_image
			, Point(b, hist_height - height), Point(b, hist_height)
			, Scalar::all(255)
		);
	}
	namedWindow(name, WINDOW_NORMAL);
	resizeWindow(name, 300, 300);
	imshow(name, hist_image);

	return hist_image;

}
int main(int ac, char** av) {

	VideoCapture cap("test_HW2_1.mp4");

	if (!cap.isOpened())
	{
		printf("Can't open the camera");
		return -1;
	}
	Mat result;
	Mat img;
	Mat gray;
	Mat prev;//���� ���ɿ����� ������׷� ����
	Mat now;//���� ���ɿ����� ������׷� ����
	Mat com;//������ ���� ���ɿ����� ������׷��� ������� �ȼ����� ��ġ ���� ����
	while (1)
	{
		cap >> img;

		if (img.empty())
		{
			printf("empty image");
			return 0;
		}
		Mat reim;
		resize(img, reim, cv::Size(600, 600), 0, 0);

		for (int i = 0; i < 2; i++)
		{
			
			Rect2d r = selectROI(reim);
			Mat go_or = reim(r);
			cvtColor(go_or, go_or, COLOR_RGB2GRAY);
			Mat result = my_Hog(go_or);
			if (i == 1) {//�ι�° ���� ���� �Է½� ����
				now = show_histogram("after_histogram", result, "after image");
				compare(prev, now, com, CMP_EQ);
				//cmp_eq�� ���ؼ� ��ġ�� ��� 255�� ��ġ���� ���� ��� 0���� �Ҵ��� �̹����� �����.
				get_persentage(com);//��ġ������ ���� ������ ������ �ִ� �̹����� ������� �ȼ������� ��ġ ������ �˾Ƴ���.
			}
			else prev=show_histogram("after_histogram", result, "after image");//ù ���� ���� �Է½� ����
		}
		if (waitKey(25) == 27)
			break;
	}
	return 0;
}

Mat  my_Hog(Mat src) {
	Mat inputImage = src;

	inputImage.convertTo(inputImage, CV_32F, 1.0 / 255, 0);

	GaussianBlur(inputImage, inputImage, Size(3, 3),3,3);//������ ���� ��ó��
	Mat grad_x(inputImage.size(), inputImage.type());//x�� ���� �̺� ��� ������ ����
	Mat grad_y(inputImage.size(), inputImage.type());//y�� ���� �̺� ����� ������ ����
	int width = inputImage.cols;
	int height = inputImage.rows;
	Mat magnitude(inputImage.size(), inputImage.type());
	Mat direction(inputImage.size(), inputImage.type());


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

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			magnitude.at<float>(i, j) = sqrt(pow(grad_x.at<float>(i, j), 2) + pow(grad_y.at<float>(i, j), 2));//�ű״�Ʃ��
			direction.at<float>(i, j) = fastAtan2(grad_y.at<float>(i, j), grad_x.at<float>(i, j));//��Ÿ��
		}
	}

	//����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (-15.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < -45.0f) {
				direction.at<float>(i, j) = 330.0f;
			}
			else if (-45.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < -75.0f)
			{
				direction.at<float>(i, j) = 300.0f;
			}
			else if (-75.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < -105.0f)
			{
				direction.at<float>(i, j) = 270.0f;
			}
			else if (-105.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < -135.0f)
			{
				direction.at<float>(i, j) = 240.0f;

			}
			else if (-135.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < -165.0f)
			{
				direction.at<float>(i, j) = 210.0f;

			}
			else if (-15.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < 15.0f)
			{
				direction.at<float>(i, j) = 0.0f;
			}
			else if (15.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < 45.0f)
			{
				direction.at<float>(i, j) = 30.0f;

			}
			else if (45.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < 75.0f)
			{
				direction.at<float>(i, j) = 60.0f;

			}
			else if (75.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < 105.0f)
			{
				direction.at<float>(i, j) = 90.0f;

			}
			else if (105.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < 135.0f)
			{
				direction.at<float>(i, j) = 120;

			}
			else if (135.0f <= direction.at<float>(i, j) && direction.at<float>(i, j) < 165.0f)
			{
				direction.at<float>(i, j) = 150;

			}
			else {

				direction.at<float>(i, j) = 180;
			}
		}
	}

	Mat direction_q = direction.clone();//���������� ȯ���� ��Ÿ���� ����
	direction *= ((1.f / 360.f) * (180.f / 255.f));//���������� ȯ��
	Mat _hsv[3], hsv, hsv8, to_result;
	_hsv[0] = direction;
	_hsv[1] = Mat::ones(direction.size(), CV_32F);
	_hsv[2] = magnitude;
	merge(_hsv, 3, hsv);
	hsv.convertTo(hsv8, CV_8U, 255.0);
	cvtColor(hsv8, to_result, COLOR_HSV2RGB);//HSV�� RGB�� ��ȯ
	namedWindow("to_result", WINDOW_NORMAL);
	resizeWindow("to_result", 300, 300);
	imshow("to_result", to_result);//��ȯ ��� �̹��� show
	return direction_q;//������ ȯ������ ��Ÿ���� ����
}