#ifndef _ASTEROID_HPP_
#define _ASTEROID_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "Types.hpp"

namespace gwrld {
class Asteroid {
public:
	Asteroid(gm_serv::Context* pContext);

	void spawn();
	void update();

	float getPosY() {
		return mLocation.getY();
	}

	float getPosX() {
		return mLocation.getX();
	}

	void setFlagIsNotDrawing(bool pFlag);

private:

	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::ServiceTime* mTimeService;

	gm_serv::GraphicsSprite* mSprite;
	gm_serv::Location mLocation;
	float mSpeed;

};
}
#endif
