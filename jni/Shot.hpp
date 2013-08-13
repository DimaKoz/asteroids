#ifndef _GWRLD_SHOT_HPP_
#define _GWRLD_SHOT_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "Types.hpp"
#include "Ship.hpp"
#include <cstddef>

namespace gwrld {
class Shot {
public:
	Shot(gm_serv::Context* pContext, Ship &pShip,
			const gm_serv::shot_type &pShotType,
			const gm_serv::shot_location &pShotLocation);

	void spawn();
	void update();

	float getPosY();
	float getPosX();

	void setIsFlying(bool pIsFlying);
	bool isFlying();

	void setSpawnCoordinates();
	void setShip(gwrld::Ship& pShip);
	static float time_life;

private:
	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::ServiceTime* mTimeService;

	gm_serv::GraphicsSprite* mSprite;
	gm_serv::Location mLocation;
	gm_serv::Location mLocationSpawn;

	gm_serv::shot_type mTypeShot;
	gm_serv::shot_location mLocationShot;

	float mSpeed;
	bool mIsFlying;
	Ship& mShip;

};
}
#endif
