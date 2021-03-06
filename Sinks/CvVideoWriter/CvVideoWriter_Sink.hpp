/*!
 * \file CvVideoWriter_Sink.hpp
 * \brief
 * \author tkornuta
 * \date 11.03.2008
 */

#ifndef CVVIDEOWRITER_SINK_HPP_
#define CVVIDEOWRITER_SINK_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Props.hpp"
#include "Logger.hpp"
#include "Types/stream_OpenCV.hpp"

#include <cv.h>
#include <highgui.h>

/**
 * \defgroup CvVideoWriter CvVideoWriter
 * \ingroup Sinks
 *
 * Creates a window and displays the image
 *
 *
 *
 * \par Data streams:
 *
 * \streamin{in_img,cv::Mat}
 * Input image
 *
 *
 * \par Event handlers:
 *
 * \handler{onNewImage}
 * New image arrived
 *
 *
 * \par Properties:
 *
 * \prop{title,string,"video"}
 * Window caption
 *
 *
 * \see http://opencv.willowgarage.com/documentation/cpp/user_interface.html#namedWindow
 * \see http://opencv.willowgarage.com/documentation/cpp/user_interface.html#cv-imshow
 *
 *
 * \par Task configuration template:
 *
 * \code
 * <Components>
 *   <Window type="CvVideoWriter" thread="thread_name" group="group_name">
 *     <title>video</title>
 *   </Window>
 * </Components>
 *
 * <Events>
 *   <Event source="Component.Event" destination="Window.onNewImage"/>
 * </Events>
 *
 * <DataStreams>
 *   <Window>
 *     <in_img type="in" group="connection_name"/>
 *   </Window>
 * </DataStreams>
 * \endcode
 *
 * @{
 *
 * @}
 */

namespace Sinks {
namespace CvVideoWriter {

using namespace cv;

/*!
 * \brief CvVideoWriter properties
 *
 * WndProps contain window properties, such as title
 */
struct Props : public Base::Props {

	std::string filename;
	int fourcc;
	cv::Size size;
	double fps;


	/*!
	 * \copydoc Base::Props::load
	 */
	void load(const ptree & pt) {
		filename = pt.get("filename", "output.avi");
		fourcc = str2cc(pt.get("fourcc", "MJPG"));
		size = pt.get("size", cv::Size(640, 480));
		fps = pt.get("fps", 25.0);
	}

	/*!
	 * \copydoc Base::Props::save
	 */
	void save(ptree & pt) {
		pt.put("filename", filename);
		pt.put("fourcc", cc2str(fourcc));
		pt.put("size", size);
		pt.put("fps", fps);
	}

protected:
	int str2cc(const std::string & s) {
		if (s.length() != 4)
			return -1;

		return CV_FOURCC(s[0], s[1], s[2], s[3]);
	}

	std::string cc2str(int cc) {
		if (cc == CV_FOURCC('M','J','P','G'))
			return "MJPG";
		else
			return "MJPG";
	}
};

/*!
 * \class RGBtoHSV_Processor
 * \brief Example processor class.
 */
class CvVideoWriter_Sink: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	CvVideoWriter_Sink(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~CvVideoWriter_Sink();

	/*!
	 * Return window properties
	 */
	Base::Props * getProperties() {
		return &props;
	}

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Retrieves data from device.
	 */
	bool onStep();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();



	/*!
	 * Event handler function.
	 */
	void onNewImage();

	/// Event handler.
	Base::EventHandler<CvVideoWriter_Sink> h_onNewImage;


	/// Image to be drawn
	Base::DataStreamIn<Mat> in_img;


	/// Window properties
	Props props;

	/// Video writer
	cv::VideoWriter writer;
};

}//: namespace CvVideoWriter
}//: namespace Sinks


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("CvVideoWriter", Sinks::CvVideoWriter::CvVideoWriter_Sink, Common::Panel_Empty)

#endif /* CVVIDEOWRITER_SINK_HPP_ */

