/*!
 * \file ExecTimer.cpp
 * \brief Declaration of an example class,
 * responsible for image processing.
 * - methods definitions
 * \author tkornuta
 * \date 11.03.2008
 */

#include <memory>
#include <string>
#include <iostream>

#include "ExecTimer.hpp"

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Processors {
namespace ExecTimer {

ExecTimer::ExecTimer(const std::string & name) : Base::Component(name) {
	LOG(TRACE)<<"Hello ExecTimer\n";

	loops = 0;
	total = 0.0;
}

ExecTimer::~ExecTimer() {
	LOG(TRACE)<<"Good bye ExecTimer\n";
}

bool ExecTimer::onInit() {
	LOG(TRACE) << "ExecTimer::initialize\n";

	h_onStartExec.setup(this, &ExecTimer::onStartExec);
	registerHandler("onStartExec", &h_onStartExec);

	h_onStopExec.setup(this, &ExecTimer::onStopExec);
	registerHandler("onStopExec", &h_onStopExec);

	stopped = registerEvent("stopped");
	started = registerEvent("started");

	return true;
}

bool ExecTimer::onFinish() {
	LOG(TRACE) << "ExecTimer::finish\n";

	double spl = total / loops;
	double lps = 1.0 / spl;
	LOG(NOTICE) << "ExecTimer " << name() << ": " << loops << " in " << total << "s. ("
			<< spl << " spl = " << lps << " lps)";

	return true;
}

bool ExecTimer::onStep()
{
	LOG(TRACE)<<"ExecTimer::step\n";
	return true;
}

bool ExecTimer::onStop()
{
	LOG(TRACE)<<"ExecTimer::stop\n";
	return true;
}

bool ExecTimer::onStart()
{
	LOG(TRACE)<<"ExecTimer::start\n";
	return true;
}

void ExecTimer::onStartExec() {
	timer.restart();
	started->raise();
}

void ExecTimer::onStopExec() {
	total += timer.elapsed();
	++loops;

	stopped->raise();
}


}//: namespace ExecTimer
}//: namespace Processors
