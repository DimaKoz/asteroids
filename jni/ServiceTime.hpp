#ifndef _GM_SERV_SERVICETIME_HPP_
#define _GM_SERV_SERVICETIME_HPP_

#include "Types.hpp"

#include <time.h>

namespace gm_serv {
class ServiceTime {
public:
	ServiceTime();

	void reset();
	void update();

	double now();
	float elapsed();

private:
	float mElapsed;
	double mLastTime;
};
}

#endif
