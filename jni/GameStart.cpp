#include "GameStart.hpp"

namespace gwrld {

GameStart::GameStart(gm_serv::Context* pContext) :
		mInputService(pContext->mInputService), mGraphicsService(
				pContext->mGraphicsService), mTimeService(
				pContext->mTimeService), mLocation(), mAnimSpeed(0.0f), mIsGameStartEnded(
				false) {
	mSprite = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("start_game_.png"), 1024, 1024,
			&mLocation);
	setFlagIsNotDrawing(false);
}

GameStart::~GameStart() {
}

void GameStart::spawn() {
	const int32_t FRAME_1 = 0;
	const int32_t FRAME_NB = 1;
	mSprite->setAnimation(FRAME_1, FRAME_NB, mAnimSpeed, false);
	mLocation.setPosition(mGraphicsService->getWidth() / 2,
			mGraphicsService->getHeight() / 2);
}

void GameStart::setFlagIsNotDrawing(bool pFlag) {
	mSprite->setFlagIsNotDrawing(pFlag);
}

void GameStart::update() {
	if (mInputService->getHorizontalTouch() > 0.0f
			|| mInputService->getVerticalTouch() > 0.0f) {
		setFlagIsNotDrawing(true);
		mIsGameStartEnded = true;
	}
}

bool GameStart::gameStartIsFinish() {

	return mIsGameStartEnded;
}

} /* namespace gwrld */
