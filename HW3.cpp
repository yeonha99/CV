#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

Mat myRansac_homography(vector< Point2f > obj, vector< Point2f > scene) {
	int index1;
	int index2;
	int index3;
	int index4;

	int best;
	int count = 0;
	float thresh = 13;
	Mat H(Size(3, 3), CV_32F);
	vector< Point2f >inliner_max1;
	vector< Point2f >inliner_max2;
	for (int i = 0; i < obj.size(); i++) {
		//cout << "rand" << endl;
		index1 = rand() % obj.size();
		/*	cout << index1 << endl;*/
		index2 = rand() % obj.size();
		index3 = rand() % obj.size();
		index4 = rand() % obj.size();
		//cout << "rand" << endl;

		vector< Point2f > inliner1;
		vector< Point2f > inliner2;
		vector< Point2f > select1;
		vector< Point2f > select2;
		select1.push_back(obj[index1]);
		select1.push_back(obj[index2]);
		select1.push_back(obj[index3]);
		select1.push_back(obj[index4]);
		select2.push_back(scene[index1]);
		select2.push_back(scene[index2]);
		select2.push_back(scene[index3]);
		select2.push_back(scene[index4]);

		float a, b, c, d, e, f, g, h;
		/*  cout << "find_homography" << endl;*/
		a = -(select1[0].x * select1[0].y * select1[1].y * select2[2].x - select1[0].x * select1[0].y * select1[2].y * select2[1].x - select1[0].x * select1[0].y * select1[1].y * select2[3].x + select1[0].x * select1[0].y * select1[3].y * select2[1].x - select1[1].x * select1[0].y * select1[1].y * select2[2].x + select1[1].x * select1[1].y * select1[2].y * select2[0].x + select1[0].x * select1[0].y * select1[2].y * select2[3].x - select1[0].x * select1[0].y * select1[3].y * select2[2].x + select1[1].x * select1[0].y * select1[1].y * select2[3].x - select1[1].x * select1[1].y * select1[3].y * select2[0].x + select1[2].x * select1[0].y * select1[2].y * select2[1].x - select1[2].x * select1[1].y * select1[2].y * select2[0].x
			- select1[1].x * select1[1].y * select1[2].y * select2[3].x + select1[1].x * select1[1].y * select1[3].y * select2[2].x - select1[2].x * select1[0].y * select1[2].y * select2[3].x + select1[2].x * select1[2].y * select1[3].y * select2[0].x - select1[3].x * select1[0].y * select1[3].y * select2[1].x + select1[3].x * select1[1].y * select1[3].y * select2[0].x + select1[2].x * select1[1].y * select1[2].y * select2[3].x - select1[2].x * select1[2].y * select1[3].y * select2[1].x + select1[3].x * select1[0].y * select1[3].y * select2[2].x - select1[3].x * select1[2].y * select1[3].y * select2[0].x - select1[3].x * select1[1].y * select1[3].y * select2[2].x + select1[3].x * select1[2].y * select1[3].y * select2[1].x)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		b = (select1[0].x * select1[1].x * select1[0].y * select2[2].x - select1[0].x * select1[2].x * select1[0].y * select2[1].x - select1[0].x * select1[1].x * select1[0].y * select2[3].x - select1[0].x * select1[1].x * select1[1].y * select2[2].x + select1[0].x * select1[3].x * select1[0].y * select2[1].x + select1[1].x * select1[2].x * select1[1].y * select2[0].x + select1[0].x * select1[1].x * select1[1].y * select2[3].x + select1[0].x * select1[2].x * select1[0].y * select2[3].x + select1[0].x * select1[2].x * select1[2].y * select2[1].x - select1[0].x * select1[3].x * select1[0].y * select2[2].x - select1[1].x * select1[2].x * select1[2].y * select2[0].x - select1[1].x * select1[3].x * select1[1].y * select2[0].x
			- select1[0].x * select1[2].x * select1[2].y * select2[3].x - select1[0].x * select1[3].x * select1[3].y * select2[1].x - select1[1].x * select1[2].x * select1[1].y * select2[3].x + select1[1].x * select1[3].x * select1[1].y * select2[2].x + select1[1].x * select1[3].x * select1[3].y * select2[0].x + select1[2].x * select1[3].x * select1[2].y * select2[0].x + select1[0].x * select1[3].x * select1[3].y * select2[2].x + select1[1].x * select1[2].x * select1[2].y * select2[3].x - select1[2].x * select1[3].x * select1[2].y * select2[1].x - select1[2].x * select1[3].x * select1[3].y * select2[0].x - select1[1].x * select1[3].x * select1[3].y * select2[2].x + select1[2].x * select1[3].x * select1[3].y * select2[1].x)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		c = (select1[0].x * select1[1].y * select2[2].x - select1[0].x * select1[2].y * select2[1].x - select1[1].x * select1[0].y * select2[2].x + select1[1].x * select1[2].y * select2[0].x + select1[2].x * select1[0].y * select2[1].x - select1[2].x * select1[1].y * select2[0].x - select1[0].x * select1[1].y * select2[3].x + select1[0].x * select1[3].y * select2[1].x + select1[1].x * select1[0].y * select2[3].x - select1[1].x * select1[3].y * select2[0].x - select1[3].x * select1[0].y * select2[1].x + select1[3].x * select1[1].y * select2[0].x
			+ select1[0].x * select1[2].y * select2[3].x - select1[0].x * select1[3].y * select2[2].x - select1[2].x * select1[0].y * select2[3].x + select1[2].x * select1[3].y * select2[0].x + select1[3].x * select1[0].y * select2[2].x - select1[3].x * select1[2].y * select2[0].x - select1[1].x * select1[2].y * select2[3].x + select1[1].x * select1[3].y * select2[2].x + select1[2].x * select1[1].y * select2[3].x - select1[2].x * select1[3].y * select2[1].x - select1[3].x * select1[1].y * select2[2].x + select1[3].x * select1[2].y * select2[1].x)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		d = (select1[0].x * select1[1].x * select1[0].y * select1[2].y * select2[3].x - select1[0].x * select1[1].x * select1[0].y * select1[3].y * select2[2].x - select1[0].x * select1[2].x * select1[0].y * select1[1].y * select2[3].x + select1[0].x * select1[2].x * select1[0].y * select1[3].y * select2[1].x + select1[0].x * select1[3].x * select1[0].y * select1[1].y * select2[2].x - select1[0].x * select1[3].x * select1[0].y * select1[2].y * select2[1].x - select1[0].x * select1[1].x * select1[1].y * select1[2].y * select2[3].x + select1[0].x * select1[1].x * select1[1].y * select1[3].y * select2[2].x + select1[1].x * select1[2].x * select1[0].y * select1[1].y * select2[3].x - select1[1].x * select1[2].x * select1[1].y * select1[3].y * select2[0].x - select1[1].x * select1[3].x * select1[0].y * select1[1].y * select2[2].x + select1[1].x * select1[3].x * select1[1].y * select1[2].y * select2[0].x
			+ select1[0].x * select1[2].x * select1[1].y * select1[2].y * select2[3].x - select1[0].x * select1[2].x * select1[2].y * select1[3].y * select2[1].x - select1[1].x * select1[2].x * select1[0].y * select1[2].y * select2[3].x + select1[1].x * select1[2].x * select1[2].y * select1[3].y * select2[0].x + select1[2].x * select1[3].x * select1[0].y * select1[2].y * select2[1].x - select1[2].x * select1[3].x * select1[1].y * select1[2].y * select2[0].x - select1[0].x * select1[3].x * select1[1].y * select1[3].y * select2[2].x + select1[0].x * select1[3].x * select1[2].y * select1[3].y * select2[1].x + select1[1].x * select1[3].x * select1[0].y * select1[3].y * select2[2].x - select1[1].x * select1[3].x * select1[2].y * select1[3].y * select2[0].x - select1[2].x * select1[3].x * select1[0].y * select1[3].y * select2[1].x + select1[2].x * select1[3].x * select1[1].y * select1[3].y * select2[0].x)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		e = -(select1[0].x * select1[0].y * select1[1].y * select2[2].y - select1[0].x * select1[0].y * select1[2].y * select2[1].y - select1[0].x * select1[0].y * select1[1].y * select2[3].y + select1[0].x * select1[0].y * select1[3].y * select2[1].y - select1[1].x * select1[0].y * select1[1].y * select2[2].y + select1[1].x * select1[1].y * select1[2].y * select2[0].y + select1[0].x * select1[0].y * select1[2].y * select2[3].y - select1[0].x * select1[0].y * select1[3].y * select2[2].y + select1[1].x * select1[0].y * select1[1].y * select2[3].y - select1[1].x * select1[1].y * select1[3].y * select2[0].y + select1[2].x * select1[0].y * select1[2].y * select2[1].y - select1[2].x * select1[1].y * select1[2].y * select2[0].y
			- select1[1].x * select1[1].y * select1[2].y * select2[3].y + select1[1].x * select1[1].y * select1[3].y * select2[2].y - select1[2].x * select1[0].y * select1[2].y * select2[3].y + select1[2].x * select1[2].y * select1[3].y * select2[0].y - select1[3].x * select1[0].y * select1[3].y * select2[1].y + select1[3].x * select1[1].y * select1[3].y * select2[0].y + select1[2].x * select1[1].y * select1[2].y * select2[3].y - select1[2].x * select1[2].y * select1[3].y * select2[1].y + select1[3].x * select1[0].y * select1[3].y * select2[2].y - select1[3].x * select1[2].y * select1[3].y * select2[0].y - select1[3].x * select1[1].y * select1[3].y * select2[2].y + select1[3].x * select1[2].y * select1[3].y * select2[1].y)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		f = (select1[0].x * select1[1].x * select1[0].y * select2[2].y - select1[0].x * select1[2].x * select1[0].y * select2[1].y - select1[0].x * select1[1].x * select1[0].y * select2[3].y - select1[0].x * select1[1].x * select1[1].y * select2[2].y + select1[0].x * select1[3].x * select1[0].y * select2[1].y + select1[1].x * select1[2].x * select1[1].y * select2[0].y + select1[0].x * select1[1].x * select1[1].y * select2[3].y + select1[0].x * select1[2].x * select1[0].y * select2[3].y + select1[0].x * select1[2].x * select1[2].y * select2[1].y - select1[0].x * select1[3].x * select1[0].y * select2[2].y - select1[1].x * select1[2].x * select1[2].y * select2[0].y - select1[1].x * select1[3].x * select1[1].y * select2[0].y
			- select1[0].x * select1[2].x * select1[2].y * select2[3].y - select1[0].x * select1[3].x * select1[3].y * select2[1].y - select1[1].x * select1[2].x * select1[1].y * select2[3].y + select1[1].x * select1[3].x * select1[1].y * select2[2].y + select1[1].x * select1[3].x * select1[3].y * select2[0].y + select1[2].x * select1[3].x * select1[2].y * select2[0].y + select1[0].x * select1[3].x * select1[3].y * select2[2].y + select1[1].x * select1[2].x * select1[2].y * select2[3].y - select1[2].x * select1[3].x * select1[2].y * select2[1].y - select1[2].x * select1[3].x * select1[3].y * select2[0].y - select1[1].x * select1[3].x * select1[3].y * select2[2].y + select1[2].x * select1[3].x * select1[3].y * select2[1].y)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		g = (select1[0].x * select1[1].y * select2[2].y - select1[0].x * select1[2].y * select2[1].y - select1[1].x * select1[0].y * select2[2].y + select1[1].x * select1[2].y * select2[0].y + select1[2].x * select1[0].y * select2[1].y - select1[2].x * select1[1].y * select2[0].y - select1[0].x * select1[1].y * select2[3].y + select1[0].x * select1[3].y * select2[1].y + select1[1].x * select1[0].y * select2[3].y - select1[1].x * select1[3].y * select2[0].y - select1[3].x * select1[0].y * select2[1].y + select1[3].x * select1[1].y * select2[0].y
			+ select1[0].x * select1[2].y * select2[3].y - select1[0].x * select1[3].y * select2[2].y - select1[2].x * select1[0].y * select2[3].y + select1[2].x * select1[3].y * select2[0].y + select1[3].x * select1[0].y * select2[2].y - select1[3].x * select1[2].y * select2[0].y - select1[1].x * select1[2].y * select2[3].y + select1[1].x * select1[3].y * select2[2].y + select1[2].x * select1[1].y * select2[3].y - select1[2].x * select1[3].y * select2[1].y - select1[3].x * select1[1].y * select2[2].y + select1[3].x * select1[2].y * select2[1].y)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);

		h = (select1[0].x * select1[1].x * select1[0].y * select1[2].y * select2[3].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y * select2[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y * select2[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y * select2[1].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y * select2[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y * select2[1].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y * select2[3].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y * select2[2].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y * select2[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y * select2[0].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y * select2[2].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y * select2[0].y
			+ select1[0].x * select1[2].x * select1[1].y * select1[2].y * select2[3].y - select1[0].x * select1[2].x * select1[2].y * select1[3].y * select2[1].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y * select2[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y * select2[0].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y * select2[1].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y * select2[0].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y * select2[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y * select2[1].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y * select2[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y * select2[0].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y * select2[1].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y * select2[0].y)
			/ (select1[0].x * select1[1].x * select1[0].y * select1[2].y - select1[0].x * select1[2].x * select1[0].y * select1[1].y - select1[0].x * select1[1].x * select1[0].y * select1[3].y - select1[0].x * select1[1].x * select1[1].y * select1[2].y + select1[0].x * select1[3].x * select1[0].y * select1[1].y + select1[1].x * select1[2].x * select1[0].y * select1[1].y + select1[0].x * select1[1].x * select1[1].y * select1[3].y + select1[0].x * select1[2].x * select1[0].y * select1[3].y + select1[0].x * select1[2].x * select1[1].y * select1[2].y - select1[0].x * select1[3].x * select1[0].y * select1[2].y - select1[1].x * select1[2].x * select1[0].y * select1[2].y - select1[1].x * select1[3].x * select1[0].y * select1[1].y
				- select1[0].x * select1[2].x * select1[2].y * select1[3].y - select1[0].x * select1[3].x * select1[1].y * select1[3].y - select1[1].x * select1[2].x * select1[1].y * select1[3].y + select1[1].x * select1[3].x * select1[0].y * select1[3].y + select1[1].x * select1[3].x * select1[1].y * select1[2].y + select1[2].x * select1[3].x * select1[0].y * select1[2].y + select1[0].x * select1[3].x * select1[2].y * select1[3].y + select1[1].x * select1[2].x * select1[2].y * select1[3].y - select1[2].x * select1[3].x * select1[0].y * select1[3].y - select1[2].x * select1[3].x * select1[1].y * select1[2].y - select1[1].x * select1[3].x * select1[2].y * select1[3].y + select1[2].x * select1[3].x * select1[1].y * select1[3].y);
		
		for (int i = 0; i < obj.size(); i++) {

			float warped_x = a * obj[i].x + b * obj[i].y + c * scene[i].x * scene[i].y + d;
			float warped_y = e * obj[i].x + f * obj[i].y + g * scene[i].x * scene[i].y + h;
			float dist = sqrt((warped_x - scene[i].x) * (warped_x - scene[i].x) +
				(warped_y - scene[i].y) * (warped_y - scene[i].y));
			if (dist < thresh) {
				inliner1.push_back(obj[i]);
				inliner2.push_back(scene[i]);
		
			}
		}


		if (inliner1.size() > inliner_max1.size()) {
			inliner_max1 = inliner1;
			inliner_max2 = inliner2;


		}
		else if (inliner_max1.empty()) {
			inliner_max1 = inliner1;
			inliner_max2 = inliner2;
		}
	}
	int inliners_num = inliner_max1.size();
	Mat A(Size(8, inliners_num*2 ), CV_32F);

	Mat b(Size(1, inliners_num*2), CV_32F);

	int r = 0;
	for (int i = 0; i < inliners_num ; i++) {
		
		A.at<float>(r, 0) = inliner_max2[i].x;
		A.at<float>(r, 1) = inliner_max2[i].y;
		A.at<float>(r, 2) = 1;
		A.at<float>(r, 3) = 0;
		A.at<float>(r, 4) = 0;
		A.at<float>(r, 5) = 0;
		A.at<float>(r, 6) = -(inliner_max2[i].x* inliner_max1[i].x);
		A.at<float>(r, 7) = -(inliner_max2[i].y * inliner_max1[i].x);
		b.at<float>(r, 0) = inliner_max1[i].x;
		r++;
		A.at<float>(r, 0) = 0;
		A.at<float>(r, 1) = 0;
		A.at<float>(r, 2) = 0;
		A.at<float>(r, 3) = inliner_max2[i].x;
		A.at<float>(r, 4) = inliner_max2[i].y;
		A.at<float>(r, 5) = 1;
		A.at<float>(r, 6) = -(inliner_max2[i].x * inliner_max1[i].y);
		A.at<float>(r, 7) = -(inliner_max2[i].y * inliner_max1[i].y);
		b.at<float>(r, 0) = inliner_max1[i].y;
		r++;
	
	}
	//cout << A << endl;
	//cout << b << endl;
	Mat x_result=(A.t()* A).inv()* A.t()* b;

	//cout << x_result << endl;
	H.at<float>(0, 0) = x_result.at<float>(0, 0);
	H.at<float>(0, 1) = x_result.at<float>(1, 0);
	H.at<float>(0, 2) = x_result.at<float>(2, 0);
	H.at<float>(1, 0) = x_result.at<float>(3, 0);
	H.at<float>(1, 1) = x_result.at<float>(4, 0);
	H.at<float>(1, 2) = x_result.at<float>(5, 0);
	H.at<float>(2, 0) = x_result.at<float>(6, 0);
	H.at<float>(2, 1) = x_result.at<float>(7, 0);
	H.at<float>(2, 2) = 1;
	cout << H << endl;



	return H;
}
void warp(Mat input, Mat output, Mat H) {
	resize(input, input, Size(1200, 600));
	Mat sol(Size(1, 3), CV_32F);
	Mat xy1(Size(1,3), CV_32F);
	Mat xy1_inv(Size(1, 3), CV_32F);
	xy1.at<float>(2, 0) = 1;
	int row_b;
	int col_b;
	int row;
	int col;

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			xy1.at<float>(0, 0) = i;
			xy1.at<float>(1, 0) = j;
			sol = H * xy1;
			row_b = int(sol.at<float>(0, 0)/ sol.at<float>(2, 0));
			col_b = int(sol.at<float>(1, 0)/ sol.at<float>(2, 0));
			//forward warp 과정
			if (0 < row_b && row_b < output.rows) {
				if (0 < col_b && col_b < output.cols) {
					output.at<Vec3b>(row_b, col_b) = input.at<Vec3b>(i, j);

				}
			}
		}
	}
	imshow("forward", output);
	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			xy1.at<float>(0, 0) = i;
			xy1.at<float>(1, 0) = j;
			xy1_inv = H.inv() * xy1;
			row = int(xy1_inv.at<float>(0, 0) / xy1_inv.at<float>(2, 0));
			col = int(xy1_inv.at<float>(1, 0) / xy1_inv.at<float>(2, 0));
			//inverse warp 과정
			if (0 < row && row < input.rows) {
				if (0 < col && col < input.cols) {
					output.at<Vec3b>(i, j) = input.at<Vec3b>(row, col);

				}
			}
		}
	}
	imshow("inverse", output);
}
int main() {
	Mat image1 = imread("img1.jpg", 1);
	Mat image2 = imread("img2.jpg", 1);

	resize(image2, image2, Size(600,600));
	resize(image1, image1, Size(600, 600));
	Mat gray1;
	Mat gray2;
	std::vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	cvtColor(image1, gray1, COLOR_RGB2GRAY);
	cvtColor(image2, gray2, COLOR_RGB2GRAY);

	Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
	sift->detectAndCompute(gray1, Mat(), keypoints1, descriptors1);
	sift->detectAndCompute(gray2, Mat(), keypoints2, descriptors2);

	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
	const float ratio_thresh = 0.7f;//원래 0.7이였음
	std::vector<DMatch> good_matches;
	
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
	
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	//-- Draw matches
	Mat img_matches;
	drawMatches(image1, keypoints1, image2, keypoints2, good_matches, img_matches, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//-- Show detected matches

	vector< Point2f > obj;
	vector< Point2f > scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//--Get the keypoints from the good matches
		obj.push_back(keypoints1[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}


	Mat H = myRansac_homography(obj, scene);



	Mat result(Size(image1.cols + image2.cols, image1.rows +image2.cols), CV_8UC3);

	
	warp(image2, result, H);

	std::vector<cv::Point> resultnonBlackList;
	resultnonBlackList.reserve(result.rows * result.cols);
	for (int j = 0; j < result.rows; ++j)
		for (int i = 0; i < result.cols; ++i)
		{
		
			if (result.at<cv::Vec3b>(j, i) != cv::Vec3b(205, 205, 205))
			{
				resultnonBlackList.push_back(cv::Point(i, j));
			}
		}

	
	Rect bbre = boundingRect(resultnonBlackList);
	
	Mat cut = result(bbre);
	imshow("result", cut);

	Mat half(cut, Rect(0, 0, 600, 600));
	image1.copyTo(half);

	imshow("half", half);

	std::vector<cv::Point> nonBlackList;
	nonBlackList.reserve(cut.rows * cut.cols);
	for (int j = 0; j < cut.rows; ++j)
		for (int i = 0; i < cut.cols; ++i)
		{
			
			// if not black: add to the list
			if (cut.at<cv::Vec3b>(j, i) != cv::Vec3b(205, 205, 205))
			{
				nonBlackList.push_back(cv::Point(i, j));

			}
		}

	
	Rect bb = cv::boundingRect(nonBlackList);


	//
	imshow("cut", cut(bb));
	imwrite("./cut.jpg", cut(bb));
	imshow("Good Matches", img_matches);
	waitKey();
	return 0;
}