#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#include "Types.hpp"

#include <android/sensor.h>

namespace gm_serv {
class EventLoop;

class Sensor {
public:
	Sensor(EventLoop& pEventLoop, int32_t pSensorType);

	status toggle();
	status enable();
	status disable();

private:
	EventLoop& mEventLoop;
	const ASensor* mSensor;
	int32_t mSensorType;
};
}
#endif
