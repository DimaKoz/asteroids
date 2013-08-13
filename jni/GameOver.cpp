
#include "GameOver.hpp"

namespace gwrld {

GameOver::GameOver(gm_serv::Context* pContext) :
		mInputService(pContext->mInputService), mGraphicsService(
				pContext->mGraphicsService), mTimeService(
				pContext->mTimeService), mLocation(), mAnimSpeed(0.0f), mIsGameOverMaked(
				false) {
	mSprite = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("game_over1_.png"),
			128, 512, &mLocation);
	setFlagIsNotDrawing(true);
}

GameOver::~GameOver() {
}

void GameOver::spawn() {
	const int32_t FRAME_1 = 0;
	const int32_t FRAME_NB = 1;
	mSprite->setAnimation(FRAME_1, FRAME_NB, mAnimSpeed, false);
	mLocation.setPosition(mGraphicsService->getWidth() / 2,
			mGraphicsService->getHeight() / 2);
}

void GameOver::setFlagIsNotDrawing(bool pFlag) {
	mSprite->setFlagIsNotDrawing(pFlag);
}
void GameOver::setGameOverMaked(bool pFlag) {
	mIsGameOverMaked = pFlag;
}

bool GameOver::isGameOverMaked() {
	return mIsGameOverMaked;
}

} /* namespace gwrld */
