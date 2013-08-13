#ifndef INPUTHANDLER_HPP_
#define INPUTHANDLER_HPP_

#include <android/input.h>
#include <android/sensor.h>

namespace gm_serv {
class InputHandler {
public:
	virtual ~InputHandler() {
	}
	;

	virtual bool onTouchEvent(AInputEvent* pEvent) = 0;
	virtual bool onKeyboardEvent(AInputEvent* pEvent) = 0;
	virtual bool onTrackballEvent(AInputEvent* pEvent) = 0;
	virtual bool onAccelerometerEvent(ASensorEvent* pEvent) = 0;
};
}
#endif
