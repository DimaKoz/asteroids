#include "GameWorld.hpp"
#include "Log.hpp"

namespace gwrld {
GameWorld::GameWorld(gm_serv::Context* pContext) :
		mContext(pContext), mGraphicsService(pContext->mGraphicsService), mInputService(
				pContext->mInputService), mSoundService(
				pContext->mSoundService), mTimeService(pContext->mTimeService), mBackground(
				pContext), mShip(pContext), mAsteroids(),  mGameOver(
				pContext), mGameStart(pContext)
			,mScoreBoard(pContext), mStatusGame(
				gm_serv::GAME_START), mStartSound(
				mSoundService->registerSound("start.pcm")) {
	gm_serv::Log::info("Creating GameWorld");

	// Creates debris.
	for (int i = 0; i < 100; ++i) {
		mDebris.push_back(new Debris(pContext));
	}

	// Creates asteroids.
	for (int i = 0; i < 3; ++i) {
		mAsteroids.push_back(new Asteroid(pContext));
	}

	for (int i = 0; i < 6; ++i) {
		if (i == 0) {
			mShots.push_back(
					new Shot(pContext, mShip, gm_serv::NORMAL_SHOT,
							gm_serv::LOCATION_LEFT));
		} else if (i == 1) {
			mShots.push_back(
					new Shot(pContext, mShip, gm_serv::NORMAL_SHOT,
							gm_serv::LOCATION_RIGHT));
		} else {
			mShots.push_back(
					new Shot(pContext, mShip, gm_serv::SMALL_SHOT,
							gm_serv::LOCATION_CENTER));
		}
	}

}

GameWorld::~GameWorld() {

	mAsteroidsCollided.clear();
	mShotsCollided.clear();
	mDebrisCollided.clear();

	std::vector<Asteroid*>::iterator iAsteroid = mAsteroids.begin();
	for (; iAsteroid < mAsteroids.end(); ++iAsteroid) {
		delete *iAsteroid;
	}
	mAsteroids.clear();

	std::vector<Shot*>::iterator iShot = mShots.begin();
	for (; iShot < mShots.end(); ++iShot) {
		delete *iShot;
	}
	mShots.clear();

	std::vector<Debris*>::iterator iDebris = mDebris.begin();
	for (; iDebris < mDebris.end(); ++iDebris) {
		delete *iDebris;
	}
	mDebris.clear();

}

gm_serv::status GameWorld::onActivate() {
	gm_serv::Log::info("Activating GameWorld");
	// Starts services.
	if (mGraphicsService->start() != gm_serv::STATUS_OK) {
		return gm_serv::STATUS_ERR;
	}
	if (mInputService->start() != gm_serv::STATUS_OK) {
		return gm_serv::STATUS_ERR;
	}
	if (mSoundService->start() != gm_serv::STATUS_OK) {
		return gm_serv::STATUS_ERR;
	}

	if (getGameStatus() == gm_serv::GAME_OVER_MAKED) {
		gm_serv::Log::info("Activating GameWorld - GAME_OVER_MAKED");
		mGameOver.spawn();
		mTimeService->reset();
		return gm_serv::STATUS_OK;
	}
	if (getGameStatus() == gm_serv::GAME_START) {
		gm_serv::Log::info("Activating GameWorld - GAME_START");
		mGameStart.spawn();
		mTimeService->reset();
		return gm_serv::STATUS_OK;
	}

	if (getGameStatus() == gm_serv::GAME_FIRST_LVL_CONTINUE) {
		gm_serv::Log::info("Activating GameWorld - GAME_FIRST_LVL_CONTINUE");
		makeFirstLvl();
		mTimeService->reset();
		return gm_serv::STATUS_OK;
	}

	mTimeService->reset();
	return gm_serv::STATUS_OK;

}

void GameWorld::onDeactivate() {
	gm_serv::Log::info("Deactivating GameWorld");
	mGraphicsService->stop();
	mInputService->stop();
	mSoundService->stop();
}

gm_serv::status GameWorld::onStep() {

	mTimeService->update();
	checkGameStatus();
	if (getGameStatus() == gm_serv::GAME_START) {
		mGameStart.update();
	}

	if (getGameStatus() == gm_serv::GAME_FIRST_LVL_STARTING) {

		makeFirstLvl();

	}
	if (getGameStatus() == gm_serv::GAME_FIRST_LVL_CONTINUE
			|| getGameStatus() == gm_serv::GAME_OVER_STARTED) {
		// Updates entities.
		mBackground.update();

		std::vector<Asteroid*>::iterator iAsteroid = mAsteroids.begin();
		for (; iAsteroid < mAsteroids.end(); ++iAsteroid) {
			(*iAsteroid)->update();
		}

		std::vector<Debris*>::iterator iDebris = mDebris.begin();
		for (; iDebris < mDebris.end(); ++iDebris) {
			if ((*iDebris)->isFlying()) {
				(*iDebris)->update();
			}
		}

		std::vector<Shot*>::iterator iShot = mShots.begin();
		for (; iShot < mShots.end(); ++iShot) {
			if ((*iShot)->isFlying()) {
				(*iShot)->update();
			}
			if (getGameStatus() != gm_serv::GAME_OVER_STARTED
					&& ((*iShot)->time_life > gm_serv::RANGE_SPAWN_SHOTS)
					&& !(*iShot)->isFlying()) {
				(*iShot)->spawn();
			}
		}
		mShip.update();

		if (gwrld::Collider::shipIsCollided(mAsteroids, 15.0f, mShip, 30.0f)) {
			mShip.killMe();
			setGameStatus(gm_serv::GAME_OVER_STARTED);
		}
		if (gwrld::Collider::shipIsCollided(mDebris, 5.0f, mShip, 30.0f)) {
			mShip.killMe();
			setGameStatus(gm_serv::GAME_OVER_STARTED);
		}
		makeCollideAsteroids();
		makeCollideDebris();

	}
	checkGameStatus();
	// Updates services.
	if (getGameStatus() != gm_serv::GAME_OVER_MAKED) {
		if (mGraphicsService->update(getGameStatus()) != gm_serv::STATUS_OK) {
			return gm_serv::STATUS_ERR;
		}
	} else {
		if (mGraphicsService->update(getGameStatus()) != gm_serv::STATUS_OK) {
			return gm_serv::STATUS_ERR;
		}
	}
	if (mInputService->update() != gm_serv::STATUS_OK) {
		return gm_serv::STATUS_ERR;
	}
	return gm_serv::STATUS_OK;
}

void GameWorld::makeCollideAsteroids() {

	const int32_t MIN_SPAWN_DEBRIS = 3;

	gwrld::Collider::checkCollide(mAsteroids, 25.0f, mShots, 5.0f,
			mAsteroidsCollided, mShotsCollided);

	std::vector<Shot*>::iterator iShotCollided = mShotsCollided.begin();
	for (; iShotCollided < mShotsCollided.end(); ++iShotCollided) {

		(*iShotCollided)->spawn();
	}
	std::vector<Asteroid*>::iterator iAsteroidCollided =
			mAsteroidsCollided.begin();
	for (; iAsteroidCollided < mAsteroidsCollided.end(); ++iAsteroidCollided) {
		std::vector<Debris*>::iterator iDebris = mDebris.begin();
		int32_t lMaxSpawnDebris = RAND(MIN_SPAWN_DEBRIS) + MIN_SPAWN_DEBRIS;
		int32_t lCountSpawn = 0;
		for (; iDebris < mDebris.end(); ++iDebris) {
			if (!(*iDebris)->isFlying()) {
				if (lCountSpawn > lMaxSpawnDebris) {
					break;
				}
				++lCountSpawn;

				(*iDebris)->setParentLocations((*iAsteroidCollided)->getPosX(),
						(*iAsteroidCollided)->getPosY());
				(*iDebris)->spawn();

			}
		}
		(*iAsteroidCollided)->spawn();
		int32_t lScore = mScoreBoard.getScore();
		mScoreBoard.setScore(++lScore);
	}
}

void GameWorld::makeCollideDebris() {
	gwrld::Collider::checkCollide(mDebris, 15.0f, mShots, 5.0f, mDebrisCollided,
			mShotsCollided);
	std::vector<Shot*>::iterator iShotCollided = mShotsCollided.begin();
	for (; iShotCollided < mShotsCollided.end(); ++iShotCollided) {
		(*iShotCollided)->spawn();
	}
	std::vector<Debris*>::iterator iDebrisCollided = mDebrisCollided.begin();
	for (; iDebrisCollided < mDebrisCollided.end(); ++iDebrisCollided) {
		(*iDebrisCollided)->killMe();
		int32_t lScore = mScoreBoard.getScore();
		mScoreBoard.setScore(++lScore);
	}
}

void GameWorld::makeGameOver() {

	gm_serv::Log::debug("making game over.");
	mGameOver.spawn();
	mGameOver.setFlagIsNotDrawing(false);
	mShip.setFlagIsNotDrawing(true);
	mScoreBoard.setFlagIsNotDrawing(true);

	std::vector<Debris*>::iterator iDebris = mDebris.begin();
	for (; iDebris < mDebris.end(); ++iDebris) {
		(*iDebris)->killMe();
	}
	std::vector<Shot*>::iterator iShot = mShots.begin();
	for (; iShot < mShots.end(); ++iShot) {
		(*iShot)->setIsFlying(false);
	}

	std::vector<Asteroid*>::iterator iAsteroid = mAsteroids.begin();
	for (; iAsteroid < mAsteroids.end(); ++iAsteroid) {
		(*iAsteroid)->setFlagIsNotDrawing(true);
	}
	mSoundService->stopBGM();
	mSoundService->playBGM("bgm_game_over.mp3");
}

void GameWorld::makeFirstLvl() {
	gm_serv::Log::info("Activating GameWorld - First lvl.");

	// Starts background music.
	mSoundService->playBGM("bgm.mp3");
	//mSoundService->playSound(mStartSound);
	// Initializes game objects.

	mScoreBoard.spawn();
	mBackground.spawn();
	mShip.spawn();
	std::vector<Asteroid*>::iterator iAsteroid = mAsteroids.begin();
	for (; iAsteroid < mAsteroids.end(); ++iAsteroid) {
		(*iAsteroid)->spawn();
	}
	mShots[0]->spawn();
	std::vector<Shot*>::iterator iShot = mShots.begin();
	for (; iShot < mShots.end(); ++iShot) {
		(*iShot)->setShip(mShip);
	}

	setGameStatus(gm_serv::GAME_FIRST_LVL_CONTINUE);

}

void GameWorld::checkGameStatus() {

	if (getGameStatus() == gm_serv::GAME_START
			&& mGameStart.gameStartIsFinish()) {
		setGameStatus(gm_serv::GAME_FIRST_LVL_STARTING);
		return;
	}
	if (getGameStatus() == gm_serv::GAME_OVER_STARTED
			&& mShip.isKillAnimationEnded()) {
		makeGameOver();
		setGameStatus(gm_serv::GAME_OVER_MAKED);
		return;
	}
}

gm_serv::game_status GameWorld::getGameStatus() {
	return mStatusGame;
}

void GameWorld::setGameStatus(gm_serv::game_status pGameStatus) {
	mStatusGame = pGameStatus;
}

void GameWorld::onStart() {
	gm_serv::Log::info("onStart");
}

void GameWorld::onResume() {
	gm_serv::Log::info("onResume");
}

void GameWorld::onPause() {
	gm_serv::Log::info("onPause");
}

void GameWorld::onStop() {
	gm_serv::Log::info("onStop");
}

void GameWorld::onDestroy() {
	gm_serv::Log::info("onDestroy");
}

void GameWorld::onSaveState(void** pData, size_t* pSize) {
	gm_serv::Log::info("onSaveInstanceState");
}

void GameWorld::onConfigurationChanged() {
	gm_serv::Log::info("onConfigurationChanged");
}

void GameWorld::onLowMemory() {
	gm_serv::Log::info("onLowMemory");
}

void GameWorld::onCreateWindow() {
	gm_serv::Log::info("onCreateWindow");
}

void GameWorld::onDestroyWindow() {
	gm_serv::Log::info("onDestroyWindow");
}

void GameWorld::onGainFocus() {
	gm_serv::Log::info("onGainFocus");
}

void GameWorld::onLostFocus() {
	gm_serv::Log::info("onLostFocus");
}
}
