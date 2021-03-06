/*!
 * \file CvThreshold_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>

#include "CvThreshold_Processor.hpp"
#include "Logger.hpp"

namespace Processors {
namespace CvThreshold {

CvThreshold_Processor::CvThreshold_Processor(const std::string & name) : Base::Component(name)
{
	LOG(TRACE) << "Hello CvThreshold_Processor\n";
}

CvThreshold_Processor::~CvThreshold_Processor()
{
	LOG(TRACE) << "Good bye CvThreshold_Processor\n";
}

bool CvThreshold_Processor::onInit()
{
	LOG(TRACE) << "CvThreshold_Processor::initialize\n";

	h_onNewImage.setup(this, &CvThreshold_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	return true;
}

bool CvThreshold_Processor::onFinish()
{
	LOG(TRACE) << "CvThreshold_Processor::finish\n";

	return true;
}

bool CvThreshold_Processor::onStep()
{
	LOG(TRACE) << "CvThreshold_Processor::step\n";
	return true;
}

bool CvThreshold_Processor::onStop()
{
	return true;
}

bool CvThreshold_Processor::onStart()
{
	return true;
}

void CvThreshold_Processor::onNewImage()
{
	LOG(TRACE) << "CvThreshold_Processor::onNewImage\n";
	try {
		cv::Mat img = in_img.read();
		cv::Mat out = img.clone();
		cv::threshold(img, out, props.thresh, props.maxval, props.type);
		out_img.write(out);
		newImage->raise();
	} catch (...) {
		LOG(ERROR) << "CvThreshold::onNewImage failed\n";
	}
}

}//: namespace CvThreshold
}//: namespace Processors
