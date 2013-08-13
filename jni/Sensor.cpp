#include "Sensor.hpp"
#include "EventLoop.hpp"
#include "Log.hpp"

namespace gm_serv {
Sensor::Sensor(EventLoop& pEventLoop, int32_t pSensorType) :
		mEventLoop(pEventLoop), mSensor(NULL), mSensorType(pSensorType) {
}

status Sensor::toggle() {
	return (mSensor != NULL) ? disable() : enable();
}

status Sensor::enable() {
	const char* lErr = "Error";
	try {
		if (mEventLoop.mEnabled) {
			mSensor = ASensorManager_getDefaultSensor(mEventLoop.mSensorManager,
					mSensorType);
			if (mSensor != NULL) {
				if (ASensorEventQueue_enableSensor(mEventLoop.mSensorEventQueue,
						mSensor) < 0) {
					throw lErr;
				}

				const char* lName = ASensor_getName(mSensor);
				const char* lVendor = ASensor_getVendor(mSensor);
				float lResolution = ASensor_getResolution(mSensor);
				int32_t lMinDelay = ASensor_getMinDelay(mSensor);
				if (ASensorEventQueue_setEventRate(mEventLoop.mSensorEventQueue,
						mSensor, lMinDelay) < 0) {
					throw lErr;
				}

				gm_serv::Log::info("Activating sensor:");
				gm_serv::Log::info("Name       : %s", lName);
				gm_serv::Log::info("Vendor     : %s", lVendor);
				gm_serv::Log::info("Resolution : %f", lResolution);
				gm_serv::Log::info("Min Delay  : %d", lMinDelay);
			} else {
				gm_serv::Log::error("No sensor type %d", mSensorType);
			}
		}
		return STATUS_OK;
	} catch (const char* Ch) {
		Log::error("Error while activating sensor.");
		disable();
		return STATUS_ERR;
	}
}

status Sensor::disable() {
	const char* lErr = "Error";
	try {
		if ((mEventLoop.mEnabled) && (mSensor != NULL)) {
			if (ASensorEventQueue_disableSensor(mEventLoop.mSensorEventQueue,
					mSensor) < 0) {
				throw lErr;
			}
			mSensor = NULL;
		}
		return STATUS_OK;
	} catch (const char* Ch) {
		Log::error("Error while deactivating sensor.");
		return STATUS_ERR;
	}
}
}
