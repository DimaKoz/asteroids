#ifndef SHIP_HPP_
#define SHIP_HPP_

#include "Context.hpp"
#include "InputService.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "ServiceTime.hpp"
#include "Types.hpp"
#include "vector"
#include "Asteroid.hpp"

namespace gwrld {
class Ship {
public:
	Ship(gm_serv::Context* pContext);

	void spawn();
	void update();
//        void checkCollide(std::vector<Asteroid*> pAsteroids);

	bool isDestroyed();

	void killMe();
	bool isKillAnimationEnded();

	float getCoordX();
	float getCoordY();

	void setFlagIsNotDrawing(bool pFlag);

private:
	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::InputService* mInputService;
	gm_serv::ServiceTime* mTimeService;

	gm_serv::GraphicsSprite* mSprite;
	gm_serv::GraphicsSprite* mSpriteJet;
	gm_serv::GraphicsSprite* mSpriteExplosion;

	gm_serv::Location mLocation;
	gm_serv::Location mLocationJet;
	gm_serv::Location mLocationExplosion;

	float mAnimSpeed;
	bool destroyed;
};
}
#endif
