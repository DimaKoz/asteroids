#include "Ship.hpp"
#include "Log.hpp"

namespace gwrld {

const bool USE_ADVANCE_LOG = false;

Ship::Ship(gm_serv::Context* pContext) :
		mInputService(pContext->mInputService), mGraphicsService(
				pContext->mGraphicsService), mTimeService(
				pContext->mTimeService), mLocation(), mAnimSpeed(8.0f) {
	mSprite = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("ship_.png"), 64, 64, &mLocation);
	mSpriteJet = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("ship_.png"), 64, 64,
			&mLocationJet);
	mSpriteExplosion = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("boom_alfa_.png"), 256, 256,
			&mLocationExplosion);

	mInputService->setRefPoint(&mLocation);
	destroyed = false;
}

void Ship::spawn() {
	const int32_t FRAME_1 = 0;
	const int32_t FRAME_NB = 8;
	const int32_t FRAME_JET_1 = 8;
	const int32_t FRAME_JET_NB = 16;
	const int32_t FRAME_EXPLODE_1 = 1;
	const int32_t FRAME_EXPLODE_NB = 16;

	mSprite->setAnimation(FRAME_1, FRAME_NB, mAnimSpeed, true);
	mSpriteJet->setAnimation(FRAME_JET_1, FRAME_JET_NB, mAnimSpeed, true);
	mSpriteExplosion->setAnimation(FRAME_EXPLODE_1, FRAME_EXPLODE_NB,
			mAnimSpeed, false);
	//FIXME переделать на общую функцию для любого спрайта
	mSpriteExplosion->setFlagIsNotDrawing(true);

	mLocation.setPosition(mGraphicsService->getWidth() * 1 / 2,
			mGraphicsService->getHeight() * 1 / 4);
	mLocationJet.setPosition(mGraphicsService->getWidth() * 1 / 2,
			(mGraphicsService->getHeight() * 1 / 4) - 50);
	mLocationExplosion.setPosition(mLocation.getX(), mLocation.getY());
}

bool Ship::isDestroyed() {
	return destroyed;
}

void Ship::setFlagIsNotDrawing(bool pFlag) {

	if (pFlag) {
		mSprite->setFlagIsNotDrawing(pFlag);
		mSpriteJet->setFlagIsNotDrawing(pFlag);
		mSpriteExplosion->setFlagIsNotDrawing(pFlag);
	} else {
		mSprite->setFlagIsNotDrawing(destroyed);
		mSpriteJet->setFlagIsNotDrawing(destroyed);
		mSpriteExplosion->setFlagIsNotDrawing(!destroyed);
	}

}

void Ship::killMe() {

	destroyed = true;
	mSprite->setFlagIsNotDrawing(true);
	mSpriteJet->setFlagIsNotDrawing(true);
	mSpriteExplosion->setFlagIsNotDrawing(false);

}

bool Ship::isKillAnimationEnded() {
	return ((!mSpriteExplosion->getFlagIsNotDrawing())
			&& mSpriteExplosion->animationEnded());
}
void Ship::update() {
	const float SPEED_PERSEC = 400.0f;
	float lSpeed = SPEED_PERSEC * mTimeService->elapsed();
#ifdef _USE_EXTENDED_LOG_SHIP
	gm_serv::Log::info("Touch PosX = %f",mInputService->getHorizontalTouch());
	gm_serv::Log::info("Touch PosY = %f",mInputService->getVerticalTouch());
}
#endif

	//FIXME при отображении кнопки раскомментировать и переделать сравнение
	//нажатие на кнопку Fire
	// не перемещаем корабль
	//if (mInputService->getVerticalTouch() <128.0f &&
	//		mInputService->getVerticalTouch() < 128.0f) {
	//	return;
	//}

	// Moves the ship.
	mLocation.translate(mInputService->getHorizontal() * lSpeed,
			mInputService->getVertical() * lSpeed);
	mLocationJet.setPosition(mLocation.getX(), mLocation.getY() - 50.0f);
	mLocationExplosion.setPosition(mLocation.getX(), mLocation.getY());

}

float Ship::getCoordX() {
	return mLocation.getX();
}

float Ship::getCoordY() {
	return mLocation.getY();
}
}
