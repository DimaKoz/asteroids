
#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "Context.hpp"
#include "InputService.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "ServiceTime.hpp"
#include "Types.hpp"

namespace gwrld {

class GameOver {
public:
	GameOver(gm_serv::Context* pContext);
	~GameOver();

	void spawn();

	void setFlagIsNotDrawing(bool pFlag);
	void setGameOverMaked(bool pFlag);
	bool isGameOverMaked();

private:

	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::InputService* mInputService;
	gm_serv::ServiceTime* mTimeService;

	gm_serv::GraphicsSprite* mSprite;

	gm_serv::Location mLocation;

	float mAnimSpeed;

	bool mIsGameOverMaked;

};

} /* namespace gwrld */
#endif /* GAMEOVER_H_ */
