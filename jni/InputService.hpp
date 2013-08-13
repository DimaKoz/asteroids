#ifndef INPUTSERVICE_HPP_
#define INPUTSERVICE_HPP_

#include "Context.hpp"
#include "InputHandler.hpp"
#include "Sensor.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>

namespace gm_serv {
class InputService: public InputHandler {
public:
	InputService(android_app* pApplication, Sensor* pAccelerometer,
			const int32_t& pWidth, const int32_t& pHeight);

	float getHorizontal();
	float getHorizontalTouch();

	float getVertical();
	float getVerticalTouch();

	void setRefPoint(Location* pTouchReference);

	status start();
	status update();
	void stop();

public:
	bool onTouchEvent(AInputEvent* pEvent);
	bool onKeyboardEvent(AInputEvent* pEvent);
	bool onTrackballEvent(AInputEvent* pEvent);
	bool onAccelerometerEvent(ASensorEvent* pEvent);

private:
	android_app* mApplication;

	// Input values.
	float mHorizontal, mVertical;

	// Input values abs.
	float mHorizontalTouch, mVerticalTouch;

	// Reference point to evaluate touch distance.
	Location* mRefPoint;
	const int32_t& mWidth, &mHeight;

	// Keys.
	bool mMenuKey;

	// Sensors.
	Sensor* mAccelerometer;
};
}
#endif
