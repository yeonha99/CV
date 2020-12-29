//12181833_정연희_HW2_1
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

void get_persentage(Mat comp) {//히스토그램의 일치율 계산 
	long  equal = 0;

	long  all = comp.rows * comp.cols;//전체픽셀수 계산
	for (int i = 0; i < comp.rows; i++) {//일치하는 픽셀수 계산
		for (int j = 0; j < comp.cols; j++) {
			if (comp.ptr<uchar>(i)[j] != 0) {//0이 아니라면 즉 일치 할 경우
				equal++;//일치수 증가
			}

		}
	}
	cout << "일치픽셀수 : " << equal << endl;
	cout << "전체픽셀수 : " << all << endl;
}

Mat show_histogram(std::string const& name, cv::Mat1b const& image, std::string const& name2) {
	
	int bins = 30;//30도 단위 간격으로 양자와 했기 때문에 bin의 간격읠 30으로 설정
	int histSize[] = { bins };
	
	float lranges[] = { 0, 330 };//0부터 360도까지의 각도 히스토그램 360과 0도는 동일하므로 이렇게 표현한다.
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
		int   const height = cvRound(binVal * hist_height / max_val);//정규화하여 적용 나타냄 즉 norm1로 표현
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
	Mat prev;//이전 관심영역의 히스토그램 저장
	Mat now;//현재 관심영역의 히스토그램 저장
	Mat com;//이전과 현재 관심영역의 히스토그램을 기반으로 픽셀단위 일치 정보 저장
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
			if (i == 1) {//두번째 관심 영역 입력시 실행
				now = show_histogram("after_histogram", result, "after image");
				compare(prev, now, com, CMP_EQ);
				//cmp_eq를 통해서 일치할 경우 255로 일치하지 않을 경우 0으로 할당한 이미지를 만든다.
				get_persentage(com);//일치정도에 대한 정보를 가지고 있는 이미지를 기반으로 픽셀단위의 일치 정도를 알아낸다.
			}
			else prev=show_histogram("after_histogram", result, "after image");//첫 관심 영역 입력시 실행
		}
		if (waitKey(25) == 27)
			break;
	}
	return 0;
}

Mat  my_Hog(Mat src) {
	Mat inputImage = src;

	inputImage.convertTo(inputImage, CV_32F, 1.0 / 255, 0);

	GaussianBlur(inputImage, inputImage, Size(3, 3),3,3);//노이즈 제거 전처리
	Mat grad_x(inputImage.size(), inputImage.type());//x에 대한 미분 결과 저장할 변수
	Mat grad_y(inputImage.size(), inputImage.type());//y에 대한 미분 결과를 저장할 변수
	int width = inputImage.cols;
	int height = inputImage.rows;
	Mat magnitude(inputImage.size(), inputImage.type());
	Mat direction(inputImage.size(), inputImage.type());


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

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			magnitude.at<float>(i, j) = sqrt(pow(grad_x.at<float>(i, j), 2) + pow(grad_y.at<float>(i, j), 2));//매그니튜드
			direction.at<float>(i, j) = fastAtan2(grad_y.at<float>(i, j), grad_x.at<float>(i, j));//세타값
		}
	}

	//양자화 과정
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

	Mat direction_q = direction.clone();//각도값으로 환산전 세타값을 저장
	direction *= ((1.f / 360.f) * (180.f / 255.f));//각도값으로 환산
	Mat _hsv[3], hsv, hsv8, to_result;
	_hsv[0] = direction;
	_hsv[1] = Mat::ones(direction.size(), CV_32F);
	_hsv[2] = magnitude;
	merge(_hsv, 3, hsv);
	hsv.convertTo(hsv8, CV_8U, 255.0);
	cvtColor(hsv8, to_result, COLOR_HSV2RGB);//HSV를 RGB로 변환
	namedWindow("to_result", WINDOW_NORMAL);
	resizeWindow("to_result", 300, 300);
	imshow("to_result", to_result);//변환 결과 이미지 show
	return direction_q;//각도값 환산전의 세타값을 리턴
}