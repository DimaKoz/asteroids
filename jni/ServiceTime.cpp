#include "ServiceTime.hpp"
#include "Log.hpp"

#include <cstdlib>

namespace gm_serv {
ServiceTime::ServiceTime() :
		mElapsed(0.0f), mLastTime(0.0f) {
	srand(time(NULL));
}

void ServiceTime::reset() {
	Log::info("Resetting TimeService.");
	mElapsed = 0.0f;
	mLastTime = now();
}

void ServiceTime::update() {
	// Checks elapsed time since last frame. It is important to
	// work on double with current time to avoid losing accuracy
	// Then we can go back to float for elapsed time.
	double lCurrentTime = now();
	mElapsed = (lCurrentTime - mLastTime);
	mLastTime = lCurrentTime;
}

double ServiceTime::now() {
	// Retrieves current time with a monotonic clock to ensure
	// time goes forward and is not subject to system changes.
	timespec lTimeVal;
	clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
	return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
}

float ServiceTime::elapsed() {
	return mElapsed;
}
}
