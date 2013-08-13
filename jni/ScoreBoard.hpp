#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "Types.hpp"
#include "Digit.hpp"

namespace gwrld {
class ScoreBoard {
public:
	ScoreBoard(gm_serv::Context* pContext);
	~ScoreBoard();

	void spawn();
	//void update();

	//float getPosY() {
	//	return mLocation.getY();
	//}

	//float getPosX() {
	//	return mLocation.getX();
	//}
	void setFlagIsNotDrawing(bool pFlag);

	void setCoordinates(float pX, float pY);
	void setRange(float pRange);
	void setScore(int32_t pNumber);
	int32_t getScore();
	//void setFlagIsNotDrawing(bool pFlag);
private:
	void updateDigits();

private:
	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::ServiceTime* mTimeService;
	std::vector<Digit*> mDigits;
	//std::vector<char* > mNameSprites;
	gm_serv::GraphicsSprite* mSprite;
	gm_serv::Location mLocation;
	//float mSpeed;
	int32_t mScore;
	float mFirstDigitCoordX;
	float mFirstDigitCoordY;
	float mRangeBetweenDigits;


};
}
#endif
