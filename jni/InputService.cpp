#include "InputService.hpp"
#include "Log.hpp"

#include <android_native_app_glue.h>
#include <cmath>

namespace gm_serv {
InputService::InputService(android_app* pApplication, Sensor* pAccelerometer,
		const int32_t& pWidth, const int32_t& pHeight) :
		mApplication(pApplication), mHorizontal(0.0f), mVertical(0.0f), mHorizontalTouch(
				0.0f), mVerticalTouch(0.0f), mRefPoint(NULL), mWidth(pWidth), mHeight(
				pHeight), mMenuKey(false), mAccelerometer(pAccelerometer) {
}

float InputService::getHorizontal() {
	return mHorizontal;
}

float InputService::getVertical() {
	return mVertical;
}

float InputService::getHorizontalTouch() {
	return mHorizontalTouch;
}

float InputService::getVerticalTouch() {
	return mVerticalTouch;
}

void InputService::setRefPoint(Location* pTouchReference) {
	mRefPoint = pTouchReference;
}

status InputService::start() {
	Log::info("Starting InputService.");

	mHorizontal = 0.0f, mVertical = 0.0f;
	mMenuKey = false;
	if ((mWidth == 0) || (mHeight == 0)) {
		return STATUS_ERR;
	}

	return STATUS_OK;
}

status InputService::update() {
	// Activates or not sensors if search button is pressed.
	if (mMenuKey) {
		if (mAccelerometer->toggle() != STATUS_OK) {
			return STATUS_ERR;
		}
	}

	// Clears previous state.
	mMenuKey = false;
	return STATUS_OK;
}

void InputService::stop() {
	Log::info("Stopping InputService.");

	// It is important to disable sensors to save battery.
	mAccelerometer->disable();
}

bool InputService::onTouchEvent(AInputEvent* pEvent) {
#ifdef INPUTSERVICE_LOG_EVENTS

	Log::debug("AMotionEvent_getAction=%d", AMotionEvent_getAction(pEvent));
	Log::debug("AMotionEvent_getFlags=%d", AMotionEvent_getFlags(pEvent));
	Log::debug("AMotionEvent_getMetaState=%d", AMotionEvent_getMetaState(pEvent));
	Log::debug("AMotionEvent_getEdgeFlags=%d", AMotionEvent_getEdgeFlags(pEvent));
	Log::debug("AMotionEvent_getDownTime=%lld", AMotionEvent_getDownTime(pEvent));
	Log::debug("AMotionEvent_getEventTime=%lld", AMotionEvent_getEventTime(pEvent));
	Log::debug("AMotionEvent_getXOffset=%f", AMotionEvent_getXOffset(pEvent));
	Log::debug("AMotionEvent_getYOffset=%f", AMotionEvent_getYOffset(pEvent));
	Log::debug("AMotionEvent_getXPrecision=%f", AMotionEvent_getXPrecision(pEvent));
	Log::debug("AMotionEvent_getYPrecision=%f", AMotionEvent_getYPrecision(pEvent));
	Log::debug("AMotionEvent_getPointerCount=%d", AMotionEvent_getPointerCount(pEvent));
	Log::debug("AMotionEvent_getRawX=%f", AMotionEvent_getRawX(pEvent, 0));
	Log::debug("AMotionEvent_getRawY=%f", AMotionEvent_getRawY(pEvent, 0));
	Log::debug("AMotionEvent_getX=%f", AMotionEvent_getX(pEvent, 0));
	Log::debug("AMotionEvent_getY=%f", AMotionEvent_getY(pEvent, 0));
	Log::debug("AMotionEvent_getPressure=%f", AMotionEvent_getPressure(pEvent, 0));
	Log::debug("AMotionEvent_getSize=%f", AMotionEvent_getSize(pEvent, 0));
	Log::debug("AMotionEvent_getOrientation=%f", AMotionEvent_getOrientation(pEvent, 0));
	Log::debug("AMotionEvent_getTouchMajor=%f", AMotionEvent_getTouchMajor(pEvent, 0));
	Log::debug("AMotionEvent_getTouchMinor=%f", AMotionEvent_getTouchMinor(pEvent, 0));
#endif
	const float TOUCH_MAX_RANGE = 65.0f; // In pixels.

	if (mRefPoint != NULL) {
		if (AMotionEvent_getAction(pEvent) == AMOTION_EVENT_ACTION_MOVE) {
			// Needs a conversion to proper coordinates
			// (origin at bottom/left). Only lMoveY needs it.
			float lMoveX = AMotionEvent_getX(pEvent, 0) - mRefPoint->mPosX;
			float lMoveY = mHeight - AMotionEvent_getY(pEvent, 0)
					- mRefPoint->mPosY;
			float lMoveRange = sqrt((lMoveX * lMoveX) + (lMoveY * lMoveY));

			if (lMoveRange > TOUCH_MAX_RANGE) {
				float lCropFactor = TOUCH_MAX_RANGE / lMoveRange;
				lMoveX *= lCropFactor;
				lMoveY *= lCropFactor;
			}

			mHorizontal = lMoveX / TOUCH_MAX_RANGE;
			mVertical = lMoveY / TOUCH_MAX_RANGE;
		} else {
			mHorizontal = 0.0f;
			mVertical = 0.0f;
		}

		mHorizontalTouch = AMotionEvent_getX(pEvent, 0);
		mVerticalTouch = mHeight - AMotionEvent_getY(pEvent, 0);
	}
	return true;
}

bool InputService::onKeyboardEvent(AInputEvent* pEvent) {
#ifdef INPUTSERVICE_LOG_EVENTS
	Log::debug("AKeyEvent_getAction=%d", AKeyEvent_getAction(pEvent));
	Log::debug("AKeyEvent_getFlags=%d", AKeyEvent_getFlags(pEvent));
	Log::debug("AKeyEvent_getKeyCode=%d", AKeyEvent_getKeyCode(pEvent));
	Log::debug("AKeyEvent_getScanCode=%d", AKeyEvent_getScanCode(pEvent));
	Log::debug("AKeyEvent_getMetaState=%d", AKeyEvent_getMetaState(pEvent));
	Log::debug("AKeyEvent_getRepeatCount=%d", AKeyEvent_getRepeatCount(pEvent));
	Log::debug("AKeyEvent_getDownTime=%lld", AKeyEvent_getDownTime(pEvent));
	Log::debug("AKeyEvent_getEventTime=%lld", AKeyEvent_getEventTime(pEvent));
#endif
	const float ORTHOGONAL_MOVE = 1.0f;

	if (AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN) {
		switch (AKeyEvent_getKeyCode(pEvent)) {
		case AKEYCODE_DPAD_LEFT:
			mHorizontal = -ORTHOGONAL_MOVE;
			break;
		case AKEYCODE_DPAD_RIGHT:
			mHorizontal = ORTHOGONAL_MOVE;
			break;
		case AKEYCODE_DPAD_DOWN:
			mVertical = -ORTHOGONAL_MOVE;
			break;
		case AKEYCODE_DPAD_UP:
			mVertical = ORTHOGONAL_MOVE;
			break;
		case AKEYCODE_BACK:
			return false;
		case AKEYCODE_VOLUME_DOWN:
			return false;
		case AKEYCODE_VOLUME_UP:
			return false;

		}
	} else {
		switch (AKeyEvent_getKeyCode(pEvent)) {
		case AKEYCODE_DPAD_LEFT:
		case AKEYCODE_DPAD_RIGHT:
			mHorizontal = 0.0f;
			break;
		case AKEYCODE_DPAD_DOWN:
		case AKEYCODE_DPAD_UP:
			mVertical = 0.0f;
			break;
		case AKEYCODE_MENU:
			mMenuKey = true;
			break;
		case AKEYCODE_BACK:
			return false;
		}
	}
	return true;
}

bool InputService::onTrackballEvent(AInputEvent* pEvent) {
#ifdef INPUTSERVICE_LOG_EVENTS
	Log::debug("AMotionEvent_getAction=%d", AMotionEvent_getAction(pEvent));
	Log::debug("AMotionEvent_getFlags=%d", AMotionEvent_getFlags(pEvent));
	Log::debug("AMotionEvent_getMetaState=%d", AMotionEvent_getMetaState(pEvent));
	Log::debug("AMotionEvent_getEdgeFlags=%d", AMotionEvent_getEdgeFlags(pEvent));
	Log::debug("AMotionEvent_getDownTime=%lld", AMotionEvent_getDownTime(pEvent));
	Log::debug("AMotionEvent_getEventTime=%lld", AMotionEvent_getEventTime(pEvent));
	Log::debug("AMotionEvent_getXOffset=%f", AMotionEvent_getXOffset(pEvent));
	Log::debug("AMotionEvent_getYOffset=%f", AMotionEvent_getYOffset(pEvent));
	Log::debug("AMotionEvent_getXPrecision=%f", AMotionEvent_getXPrecision(pEvent));
	Log::debug("AMotionEvent_getYPrecision=%f", AMotionEvent_getYPrecision(pEvent));
	Log::debug("AMotionEvent_getPointerCount=%d", AMotionEvent_getPointerCount(pEvent));
	Log::debug("AMotionEvent_getRawX=%f", AMotionEvent_getRawX(pEvent, 0));
	Log::debug("AMotionEvent_getRawY=%f", AMotionEvent_getRawY(pEvent, 0));
	Log::debug("AMotionEvent_getX=%f", AMotionEvent_getX(pEvent, 0));
	Log::debug("AMotionEvent_getY=%f", AMotionEvent_getY(pEvent, 0));
	Log::debug("AMotionEvent_getPressure=%f", AMotionEvent_getPressure(pEvent, 0));
	Log::debug("AMotionEvent_getSize=%f", AMotionEvent_getSize(pEvent, 0));
	Log::debug("AMotionEvent_getOrientation=%f", AMotionEvent_getOrientation(pEvent, 0));
	Log::debug("AMotionEvent_getTouchMajor=%f", AMotionEvent_getTouchMajor(pEvent, 0));
	Log::debug("AMotionEvent_getTouchMinor=%f", AMotionEvent_getTouchMinor(pEvent, 0));
#endif
	const float ORTHOGONAL_MOVE = 1.0f;
	const float DIAGONAL_MOVE = 0.707f;
	const float THRESHOLD = (1 / 100.0f);

	if (AMotionEvent_getAction(pEvent) == AMOTION_EVENT_ACTION_MOVE) {
		float lDirectionX = AMotionEvent_getX(pEvent, 0);
		float lDirectionY = AMotionEvent_getY(pEvent, 0);
		float lHorizontal, lVertical;

		if (lDirectionX < -THRESHOLD) {
			if (lDirectionY < -THRESHOLD) {
				lHorizontal = -DIAGONAL_MOVE;
				lVertical = DIAGONAL_MOVE;
			} else if (lDirectionY > THRESHOLD) {
				lHorizontal = -DIAGONAL_MOVE;
				lVertical = -DIAGONAL_MOVE;
			} else {
				lHorizontal = -ORTHOGONAL_MOVE;
				lVertical = 0.0f;
			}
		} else if (lDirectionX > THRESHOLD) {
			if (lDirectionY < -THRESHOLD) {
				lHorizontal = DIAGONAL_MOVE;
				lVertical = DIAGONAL_MOVE;
			} else if (lDirectionY > THRESHOLD) {
				lHorizontal = DIAGONAL_MOVE;
				lVertical = -DIAGONAL_MOVE;
			} else {
				lHorizontal = ORTHOGONAL_MOVE;
				lVertical = 0.0f;
			}
		} else if (lDirectionY < -THRESHOLD) {
			lHorizontal = 0.0f;
			lVertical = ORTHOGONAL_MOVE;
		} else if (lDirectionY > THRESHOLD) {
			lHorizontal = 0.0f;
			lVertical = -ORTHOGONAL_MOVE;
		}

		// Ends movement if there is a counter movement.
		if ((lHorizontal < 0.0f) && (mHorizontal > 0.0f)) {
			mHorizontal = 0.0f;
		} else if ((lHorizontal > 0.0f) && (mHorizontal < 0.0f)) {
			mHorizontal = 0.0f;
		} else {
			mHorizontal = lHorizontal;
		}

		if ((lVertical < 0.0f) && (mVertical > 0.0f)) {
			mVertical = 0.0f;
		} else if ((lVertical > 0.0f) && (mVertical < 0.0f)) {
			mVertical = 0.0f;
		} else {
			mVertical = lVertical;
		}
	} else {
		mHorizontal = 0.0f;
		mVertical = 0.0f;
	}
	return true;
}

bool InputService::onAccelerometerEvent(ASensorEvent* pEvent) {
#ifdef INPUTSERVICE_LOG_EVENTS
	Log::debug("ASensorEvent=%d", pEvent->version);
	Log::debug("ASensorEvent=%d", pEvent->sensor);
	Log::debug("ASensorEvent=%lld", pEvent->timestamp);
	Log::debug("ASensorEvent=%d", pEvent->type);
	Log::debug("ASensorEvent=%f,%f,%f,%d", pEvent->acceleration.x, pEvent->acceleration.y, pEvent->acceleration.z, pEvent->acceleration.status);
#endif

	const float GRAVITY = ASENSOR_STANDARD_GRAVITY / 2.0f;
	const float MIN_X = -1.0f;
	const float MAX_X = 1.0f;
	const float MIN_Y = 0.0f;
	const float MAX_Y = 2.0f;
	const float CENTER_X = (MAX_X + MIN_X) / 2.0f;
	const float CENTER_Y = (MAX_Y + MIN_Y) / 2.0f;

	// Roll tilt.
	// Use y-axis instead for landscape oriented devices:
	// float lRawHorizontal = pEvent->vector.y / GRAVITY;
	float lRawHorizontal = pEvent->vector.x / GRAVITY;
	if (lRawHorizontal > MAX_X) {
		lRawHorizontal = MAX_X;
	} else if (lRawHorizontal < MIN_X) {
		lRawHorizontal = MIN_X;
	}
	mHorizontal = CENTER_X - lRawHorizontal;

	// Pitch tilt. Final value needs to be inversed.
	float lRawVertical = pEvent->vector.z / GRAVITY;
	if (lRawVertical > MAX_Y) {
		lRawVertical = MAX_Y;
	} else if (lRawVertical < MIN_Y) {
		lRawVertical = MIN_Y;
	}
	mVertical = lRawVertical - CENTER_Y;

	return true;
}
}
