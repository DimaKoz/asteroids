#include "Shot.hpp"
#include "Log.hpp"

namespace gwrld {

float Shot::time_life = 0.0f;

Shot::Shot(gm_serv::Context* pContext, Ship &pShip,
		const gm_serv::shot_type &pShotType,
		const gm_serv::shot_location &pShotLocation) :
		mTimeService(pContext->mTimeService), mGraphicsService(
				pContext->mGraphicsService), mLocation(), mSpeed(0.0f),
				mShip(pShip), mTypeShot(pShotType), mLocationShot(
				pShotLocation) {
	if (mTypeShot == gm_serv::SMALL_SHOT) {
		mSprite = pContext->mGraphicsService->registerSprite(
				mGraphicsService->registerTexture("shot_2_.png"), 64, 16,
				&mLocation);

		mLocationSpawn.setPosition(mGraphicsService->getWidth() * 1 / 2,
				mGraphicsService->getHeight() * 1 / 2);
	} else {
		mSprite = pContext->mGraphicsService->registerSprite(
				mGraphicsService->registerTexture("shot3_1_.png"), 64, 32,
				&mLocation);

		mLocationSpawn.setPosition(mGraphicsService->getWidth() * 1 / 2,
				mGraphicsService->getHeight() * 1 / 2);

	}
	time_life = 0;
	setIsFlying(false);
}

void Shot::setSpawnCoordinates() {
	const float lOffset = 23.0f;
	float x, y;
	if (mLocationShot == gm_serv::LOCATION_CENTER) {
		x = mShip.getCoordX();
		y = mShip.getCoordY() + lOffset;
	} else if (mLocationShot == gm_serv::LOCATION_LEFT) {
		x = mShip.getCoordX() - lOffset;
		y = mShip.getCoordY() + lOffset;
	} else {
		x = mShip.getCoordX() + lOffset;
		y = mShip.getCoordY() + lOffset;
	}
	mLocationSpawn.setPosition(x, y);
}

void Shot::setShip(Ship& pShip) {
	mShip = pShip;
}

bool Shot::isFlying() {
	return mIsFlying;
}

void Shot::setIsFlying(bool pIsFlying) {
	mIsFlying = pIsFlying;
	mSprite->setFlagIsNotDrawing(!pIsFlying);
}

void Shot::spawn() {
	if (mShip.isDestroyed()) {
		return;
	}
	setSpawnCoordinates();
#ifdef _USE_EXTENDED_LOG_SHOT
	gm_serv::Log::info("spawn time_life = %f",time_life);
#endif
	time_life = 0;
	setIsFlying(true);
	if (mTypeShot == gm_serv::SMALL_SHOT) {
		mSpeed = 700.0f;
	} else {
		mSpeed = 500.0f;
	}

	const float MIN_ANIM_SPEED = 0.0f;

	float lPosX = mLocationSpawn.getX();
	float lPosY = mLocationSpawn.getY();

	mLocation.setPosition(lPosX, lPosY);

	float lAnimSpeed = MIN_ANIM_SPEED;
	mSprite->setAnimation(0, -1, lAnimSpeed, true);
}

void Shot::update() {
	time_life += mTimeService->elapsed();
#ifdef _USE_EXTENDED_LOG_SHOT
	gm_serv::Log::info("time_life = %f",time_life);
#endif
	mLocation.translate(0.0f, mTimeService->elapsed() * mSpeed);
	if (mLocation.mPosY >= mGraphicsService->getHeight()) {
		if (time_life > gm_serv::RANGE_SPAWN_SHOTS) {
			spawn();
		} else {
			setIsFlying(false);
		}

	}
}

float Shot::getPosY() {
	return mLocation.getY();
}

float Shot::getPosX() {
	return mLocation.getX();
}

}
