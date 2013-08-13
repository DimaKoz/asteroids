#ifndef _GWRLD_GAMEWORLD_HPP_
#define _GWRLD_GAMEWORLD_HPP_

#include "ActivityHandler.hpp"
#include "Asteroid.hpp"
#include "Background.hpp"
#include "Context.hpp"
#include "GraphicsService.hpp"
#include "InputService.hpp"
#include "Ship.hpp"
#include "Sound.hpp"
#include "SoundService.hpp"
#include "ServiceTime.hpp"
#include "Types.hpp"
#include "Shot.hpp"
#include "Collider.hpp"
#include "Debris.hpp"
#include "GameOver.hpp"
#include "GameStart.hpp"
#include "Digit.hpp"
#include "ScoreBoard.hpp"

#include <vector>

namespace gwrld {
class GameWorld: public gm_serv::ActivityHandler {
public:
	GameWorld(gm_serv::Context* pContext);
	~GameWorld();

protected:
	gm_serv::status onActivate();
	void onDeactivate();
	gm_serv::status onStep();

	void onStart();
	void onResume();
	void onPause();
	void onStop();
	void onDestroy();

	void onSaveState(void** pData, size_t* pSize);
	void onConfigurationChanged();
	void onLowMemory();

	void onCreateWindow();
	void onDestroyWindow();
	void onGainFocus();
	void onLostFocus();

private:
	void makeCollideDebris();
	void makeCollideAsteroids();
	void makeGameOver();

	void makeFirstLvl();

	void checkGameStatus();
	gm_serv::game_status getGameStatus();
	void setGameStatus(gm_serv::game_status pGameStatus);

private:
	gm_serv::Context* mContext;
	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::InputService* mInputService;
	gm_serv::SoundService* mSoundService;
	gm_serv::ServiceTime* mTimeService;

	Background mBackground;

	Ship mShip;
	GameOver mGameOver;
	GameStart mGameStart;

	//Digit mDigit;
	ScoreBoard mScoreBoard;

	std::vector<Asteroid*> mAsteroids;
	std::vector<Shot*> mShots;
	std::vector<Debris*> mDebris;

	std::vector<Asteroid*> mAsteroidsCollided;
	std::vector<Shot*> mShotsCollided;
	std::vector<Debris*> mDebrisCollided;

	gm_serv::game_status mStatusGame;

	gm_serv::Sound* mStartSound;

};
}
#endif
