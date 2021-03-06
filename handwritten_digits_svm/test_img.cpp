// Standard library
#include <iostream>
#include <vector>
#include <string>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

// POSIX
#include <unistd.h>

/**
 * main
 **/ 
int main( int argc, char** argv )
{

	//
	// Load SVM classifier 
	cv::Ptr<cv::ml::SVM> svm = cv::ml::StatModel::load<cv::ml::SVM>("classifier.yml");


	// read image file (grayscale)
	cv::Mat imgMat = cv::imread("test.jpg", 0);

	// convert 2d to 1d	
	cv::Mat testMat = imgMat.clone().reshape(1,1);
	testMat.convertTo(testMat, CV_32F);

	// try to predict which number has been drawn
	try{
		int predicted = svm->predict(testMat);
		
		std::cout << std::endl  << "Recognizing following number -> " << predicted << std::endl << std::endl;
		
		std::string notifyCmd = "notify-send -t 1000 Recognized: " + std::to_string(predicted);
		system(notifyCmd.c_str());
		
	}catch(cv::Exception ex){
		
	}

}
