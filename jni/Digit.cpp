#include "Digit.hpp"
#include "Log.hpp"

namespace gwrld {

Digit::Digit(gm_serv::Context* pContext) :
		mTimeService(pContext->mTimeService), mGraphicsService(
				pContext->mGraphicsService), mLocation(), mNumber(0) {
	std::vector<const char*> lNameTexture;
	lNameTexture.push_back("dig0_.png");
	lNameTexture.push_back("dig1_.png");
	lNameTexture.push_back("dig2_.png");
	lNameTexture.push_back("dig3_.png");
	lNameTexture.push_back("dig4_.png");
	lNameTexture.push_back("dig5_.png");
	lNameTexture.push_back("dig6_.png");
	lNameTexture.push_back("dig7_.png");
	lNameTexture.push_back("dig8_.png");
	lNameTexture.push_back("dig9_.png");
	std::vector<const char*>::iterator iNameTexture = lNameTexture.begin();
	for (; iNameTexture < lNameTexture.end(); ++iNameTexture) {
		mSprites.push_back(
				pContext->mGraphicsService->registerSprite(
						mGraphicsService->registerTexture(*iNameTexture), 64,
						32, &mLocation));
	}

	std::vector<gm_serv::GraphicsSprite*>::iterator iSprite = mSprites.begin();
	for (; iSprite < mSprites.end(); ++iSprite) {
		(*iSprite)->setFlagIsNotDrawing(true);
	}

	lNameTexture.clear();

}

void Digit::setNumber(int32_t pNumber) {
	if (pNumber < 0 || pNumber > 9) {
		//FIXME вывести в лог ошибку
		return;
	}
	mNumber = pNumber;
	setFlagIsNotDrawing(false);
}

void Digit::setFlagIsNotDrawing(bool pFlag) {
	std::vector<gm_serv::GraphicsSprite*>::iterator iSprite = mSprites.begin();
	if (pFlag) {
		for (; iSprite < mSprites.end(); ++iSprite) {
			(*iSprite)->setFlagIsNotDrawing(pFlag);
		}
	} else {
		for (; iSprite < mSprites.end(); ++iSprite) {
			(*iSprite)->setFlagIsNotDrawing((*iSprite) != mSprites.at(mNumber));
		}
	}
}

void Digit::setCoordinates(float pX, float pY) {
	mLocation.setPosition(pX, pY);
}

void Digit::spawn() {
	setNumber(mNumber);
	std::vector<gm_serv::GraphicsSprite*>::iterator iSprite = mSprites.begin();
	for (; iSprite < mSprites.end(); ++iSprite) {
		(*iSprite)->setAnimation(0, 1, 0.0f, false);
	}
}

}
