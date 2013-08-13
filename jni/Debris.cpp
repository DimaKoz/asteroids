#include "Debris.hpp"
#include "Log.hpp"
#include <random>
#include <ctime>
#include <functional>

namespace gwrld {

Debris::Debris(gm_serv::Context* pContext) :
		mTimeService(pContext->mTimeService), mGraphicsService(
				pContext->mGraphicsService), mLocation(), mParentLocation(), mSpeed(
				0.0f), mFlagIsFlying(false) {
#ifdef _USE_EXTENDED_LOG_DEBRIS
	gm_serv::Log::info("Debris started register sprite");
#endif
	mSprite = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("debris_ice_.png"), 32, 32,
			&mLocation);
	mSprite->setFlagIsNotDrawing(true);
}

void Debris::spawn() {

#ifdef _USE_EXTENDED_LOG_DEBRIS
	gm_serv::Log::info("Debris spawn");
#endif
	setIsFlying(true);

#ifdef _USE_EXTENDED_LOG_DEBRIS
	gm_serv::Log::info("Debris parent X %f Y %f",mParentLocation.getX(),mParentLocation.getY());
#endif

	const float MIN_SPEED = 20.0f;
	const float MIN_ANIM_SPEED = 8.0f, ANIM_SPEED_RANGE = 16.0f;

	// strong setting LOCAL_OFFSET <> 0.0f
	const float LOCAL_OFFSET = 30.0f;

	mSpeed = -RAND(MIN_SPEED) - MIN_SPEED;
	int32_t lMinPosX = getMinCoord(mParentLocation.getX(), LOCAL_OFFSET,
			mGraphicsService->getWidth());
	int32_t lMaxPosX = getMaxCoord(mParentLocation.getX(), LOCAL_OFFSET,
			mGraphicsService->getWidth());
#ifdef _USE_EXTENDED_LOG_DEBRIS
	gm_serv::Log::info("Debris lMinPosX %d lMaxPosX %d",lMinPosX,lMaxPosX);
#endif

	int32_t lMinPosY = getMinCoord(mParentLocation.getY(), LOCAL_OFFSET,
			mGraphicsService->getHeight());
	int32_t lMaxPosY = getMaxCoord(mParentLocation.getY(), LOCAL_OFFSET,
			mGraphicsService->getHeight());
#ifdef _USE_EXTENDED_LOG_DEBRIS
	gm_serv::Log::info("Debris lMinPosY %d lMaxPosY %d",lMinPosY,lMaxPosY);
#endif

	float lPosX, lPosY;

	lPosX = RAND_MIN_RANGE(lMinPosX,lMaxPosX-lMinPosX);
	lPosY = RAND_MIN_RANGE(lMinPosY,lMaxPosY-lMinPosY);

#ifdef _USE_EXTENDED_LOG_DEBRIS
	gm_serv::Log::info("Debris lPosX %f lPosY %f",lPosX,lPosY);
#endif

	mLocation.setPosition(lPosX, lPosY);

	float lAnimSpeed = MIN_ANIM_SPEED + RAND(ANIM_SPEED_RANGE);
	mSprite->setAnimation(8, -1, lAnimSpeed, true);

}

//get minimal coordinate for spawn
int32_t Debris::getMinCoord(const float &pSourceCoord, const float &pOffset,
		const float &pMaxValue) {
	int32_t lResult;
	if (pSourceCoord - pOffset <= 0.0f) {
		lResult = 0;
	} else if (pSourceCoord - pOffset >= pMaxValue) {
		lResult = pMaxValue - pOffset;
	} else {
		lResult = pSourceCoord - pOffset;
	}
	return lResult;
}

//get maximal coordinate for spawn
int32_t Debris::getMaxCoord(const float &pSourceCoord, const float &pOffset,
		const float &pMaxValue) {
	int32_t lResult;
	if (pSourceCoord + pOffset <= 0.0f) {
		lResult = 0;
	} else if (pSourceCoord + pOffset >= pMaxValue) {
		lResult = pMaxValue;
	} else {
		lResult = pSourceCoord + pOffset;
	}
	return lResult;
}

void Debris::update() {
	mLocation.translate(0.0f, mTimeService->elapsed() * mSpeed);
	if (mLocation.mPosY <= 0) {
		setIsFlying(false);
	}
}

void Debris::setIsFlying(bool pFlagIsFlying) {
	mFlagIsFlying = pFlagIsFlying;
	mSprite->setFlagIsNotDrawing(!pFlagIsFlying);
}

void Debris::killMe() {
	setIsFlying(false);
}

bool Debris::isFlying() {
	return mFlagIsFlying;
}

void Debris::setParentLocations(float pCoordX, float pCoordY) {
	mParentLocation.setPosition(pCoordX, pCoordY);
}
}
