#include "ScoreBoard.hpp"
#include "Log.hpp"

namespace gwrld {

ScoreBoard::ScoreBoard(gm_serv::Context* pContext) :
		mTimeService(pContext->mTimeService), mGraphicsService(
				pContext->mGraphicsService), mLocation(), mScore(0), mFirstDigitCoordX(
				0.0f), mFirstDigitCoordY(0.0f), mRangeBetweenDigits(0.0f) {
	mSprite = pContext->mGraphicsService->registerSprite(
			mGraphicsService->registerTexture("scoreboard_.png"), 128, 256,
			&mLocation);
	// Creates Digits.
	for (int i = 0; i < 5; ++i) {
		mDigits.push_back(new Digit(pContext));
	}
}
ScoreBoard::~ScoreBoard() {
	std::vector<Digit*>::iterator iDigits = mDigits.begin();
	for (; iDigits < mDigits.end(); ++iDigits) {
		delete *iDigits;
	}
	mDigits.clear();

}

void ScoreBoard::setScore(int32_t pNumber) {
	if (pNumber > gm_serv::SCORE_MAX) {
		mScore = 0;
	}
	mScore = pNumber;
	updateDigits();
}

void ScoreBoard::updateDigits() {
	int lSpDigit[5];
	for (int32_t i = 0, m = 1; i < 5; ++i, m *= 10) {
		lSpDigit[i] = (mScore / m) % 10;
		//gm_serv::Log::debug("%d- %d",i, lSpDigit[i]);
		mDigits.at(i)->setNumber(lSpDigit[i]);
	}
}

void ScoreBoard::setFlagIsNotDrawing(bool pFlag) {
	mSprite->setFlagIsNotDrawing(pFlag);
	std::vector<Digit*>::iterator iDigits = mDigits.begin();
	for (; iDigits < mDigits.end(); ++iDigits) {
		(*iDigits)->setFlagIsNotDrawing(pFlag);
	}

}

int32_t ScoreBoard::getScore() {
	return mScore;
}

void ScoreBoard::spawn() {
	updateDigits();
	mLocation.setPosition(mGraphicsService->getWidth() * 1 / 4,
			mGraphicsService->getHeight() * 9 / 10);
	mSprite->setAnimation(0, 1, 0.0f, false);

	std::vector<Digit*>::iterator iDigits = mDigits.begin();
	float lOffset = 0.0f;
	for (; iDigits < mDigits.end(); ++iDigits) {

		(*iDigits)->setFlagIsNotDrawing(false);
		(*iDigits)->setCoordinates(
				mGraphicsService->getWidth() * 4 / 13 - lOffset,
				mGraphicsService->getHeight() * 9 / 10);
		(*iDigits)->spawn();
		lOffset += 30.0f;

	}
}
}
