#ifndef _GWRLD_DEBRIS_HPP_
#define _GWRLD_DEBRIS_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "Types.hpp"

namespace gwrld {
class Debris {
public:
	Debris(gm_serv::Context* pContext);

	void spawn();
	void update();
	void setParentLocations(float pCoordX, float pCoordY);

	float getPosY() {
		return mLocation.getY();
	}

	float getPosX() {
		return mLocation.getX();
	}

	bool isFlying();

	void killMe();

private:

	void setIsFlying(bool pFlagIsFlying);
	int32_t getMinCoord(const float &pSourceCoord, const float &pOffset,
			const float &pMaxValue);
	int32_t getMaxCoord(const float &pSourceCoord, const float &pOffset,
			const float &pMaxValue);

	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::ServiceTime* mTimeService;

	gm_serv::GraphicsSprite* mSprite;
	gm_serv::Location mLocation;

	gm_serv::Location mParentLocation;
	float mSpeed;

	bool mFlagIsFlying;

};
}
#endif
