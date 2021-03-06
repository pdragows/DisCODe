/*!
 * \file CvColorConv_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>

#include "CvColorConv_Processor.hpp"
#include "Logger.hpp"

namespace Processors {
namespace CvColorConv {

CvColorConv_Processor::CvColorConv_Processor(const std::string & name) : Base::Component(name)
{
	LOG(TRACE) << "Hello CvThreshold_Processor\n";
}

CvColorConv_Processor::~CvColorConv_Processor()
{
	LOG(TRACE) << "Good bye CvThreshold_Processor\n";
}

bool CvColorConv_Processor::onInit()
{
	LOG(TRACE) << "CvThreshold_Processor::initialize\n";

	h_onNewImage.setup(this, &CvColorConv_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	return true;
}

bool CvColorConv_Processor::onFinish()
{
	LOG(TRACE) << "CvThreshold_Processor::finish\n";

	return true;
}

bool CvColorConv_Processor::onStep()
{
	LOG(TRACE) << "CvThreshold_Processor::step\n";
	return true;
}

bool CvColorConv_Processor::onStop()
{
	return true;
}

bool CvColorConv_Processor::onStart()
{
	return true;
}

void CvColorConv_Processor::onNewImage()
{
	LOG(TRACE) << "CvThreshold_Processor::onNewImage\n";
	try {
		cv::Mat img = in_img.read();
		cv::Mat out;
		cvtColor(img, out, props.type);
		out_img.write(out.clone());
		newImage->raise();
	} catch (...) {
		LOG(ERROR) << "CvThreshold::onNewImage failed\n";
	}
}

}//: namespace CvColorConv
}//: namespace Processors
