
#ifndef GAMESTART_H_
#define GAMESTART_H_

#include "Context.hpp"
#include "InputService.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "ServiceTime.hpp"
#include "Types.hpp"

namespace gwrld {

class GameStart {
public:
	GameStart(gm_serv::Context* pContext);
	~GameStart();

	void spawn();
	void update();

	bool gameStartIsFinish();

private:
	void setFlagIsNotDrawing(bool pFlag);
private:

	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::InputService* mInputService;
	gm_serv::ServiceTime* mTimeService;

	gm_serv::GraphicsSprite* mSprite;

	gm_serv::Location mLocation;

	float mAnimSpeed;

	bool mIsGameStartEnded;

};

} /* namespace gwrld */
#endif /* GAMEOVER_H_ */
