#include "Collider.hpp"
#include "Log.hpp"

namespace gwrld {

Collider::Collider() {
}

Collider::~Collider() {
}

void Collider::checkCollide(const std::vector<Asteroid*> &pAsteroids,
		const float pRangeAsteroid, const std::vector<Shot*> &pShots,
		const float pRangeShot, std::vector<Asteroid*> &pIsAsteroidsCollided,
		std::vector<Shot*> &pIsShotsCollided) {
#ifdef _USE_EXTENDED_LOG_COLLIDER
	gm_serv::Log::info("check collide asteroids & shots.");
#endif

	float lRangeX, lRangeY;
	float lControlRange = pRangeShot + pRangeAsteroid;
	pIsAsteroidsCollided.clear();
	pIsShotsCollided.clear();

	std::vector<Shot*>::const_iterator iShot;
	std::vector<Asteroid*>::const_iterator iAsteroid = pAsteroids.begin();
	for (; iAsteroid < pAsteroids.end(); ++iAsteroid) {
#ifdef _USE_EXTENDED_LOG_COLLIDER
		gm_serv::Log::info("Asteroid PosX = %f", (*iAsteroid)->getPosX());
		gm_serv::Log::info("Asteroid PosY = %f", (*iAsteroid)->getPosY());
#endif

		iShot = pShots.begin();
		for (; iShot < pShots.end(); ++iShot) {
			lRangeX = (*iAsteroid)->getPosX() - (*iShot)->getPosX();
			if (lRangeX < 0) {
				lRangeX = -lRangeX;
			}
			lRangeY = (*iAsteroid)->getPosY() - (*iShot)->getPosY();
			if (lRangeY < 0) {
				lRangeY = -lRangeY;
			}
			if (lRangeX <= lControlRange && lRangeY <= lControlRange) {
				pIsShotsCollided.push_back(*iShot);
				pIsAsteroidsCollided.push_back(*iAsteroid);
			}
		}
	}
}

void Collider::checkCollide(const std::vector<Debris*> &pDebris,
		const float pRangeDebris, const std::vector<Shot*> &pShots,
		const float pRangeShot, std::vector<Debris*> &pIsDebrisCollided,
		std::vector<Shot*> &pIsShotsCollided) {
#ifdef _USE_EXTENDED_LOG_COLLIDER
	gm_serv::Log::info("check collide debris & shot");
#endif

	float lRangeX, lRangeY;
	float lControlRange = pRangeShot + pRangeDebris;
	pIsDebrisCollided.clear();
	pIsShotsCollided.clear();

	std::vector<Shot*>::const_iterator iShot;
	std::vector<Debris*>::const_iterator iDebris = pDebris.begin();
	for (; iDebris < pDebris.end(); ++iDebris) {
		if (!(*iDebris)->isFlying()) {
			continue;
		}
		iShot = pShots.begin();
#ifdef _USE_EXTENDED_LOG_COLLIDER
		gm_serv::Log::info("debris PosX = %f", (*iDebris)->getPosX());
		gm_serv::Log::info("debris PosY = %f", (*iDebris)->getPosY());
#endif
		for (; iShot < pShots.end(); ++iShot) {
			lRangeX = (*iDebris)->getPosX() - (*iShot)->getPosX();
			if (lRangeX < 0) {
				lRangeX = -lRangeX;
			}
			lRangeY = (*iDebris)->getPosY() - (*iShot)->getPosY();
			if (lRangeY < 0) {
				lRangeY = -lRangeY;
			}
			if (lRangeX <= lControlRange && lRangeY <= lControlRange) {
				pIsShotsCollided.push_back(*iShot);
				pIsDebrisCollided.push_back(*iDebris);
			}
		}

	}
}

bool Collider::shipIsCollided(const std::vector<Asteroid*> &pAsteroids,
		const float pRangeAsteroid, Ship &pShip, const float pRangeShip) {
#ifdef _USE_EXTENDED_LOG_COLLIDER
	gm_serv::Log::info("check collide asteroid & ship");
	gm_serv::Log::debug("ship PosX = %f", pShip.getCoordX());
	gm_serv::Log::debug("ship PosY = %f",pShip.getCoordY());
#endif

	float lRangeX, lRangeY;
	float lControlRange = pRangeAsteroid + pRangeShip;
	std::vector<Asteroid*>::const_iterator iAsteroid = pAsteroids.begin();
	for (; iAsteroid < pAsteroids.end(); ++iAsteroid) {
		lRangeX = (*iAsteroid)->getPosX() - pShip.getCoordX();
		if (lRangeX < 0) {
			lRangeX = -lRangeX;
		}
		lRangeY = (*iAsteroid)->getPosY() - pShip.getCoordY();
		if (lRangeY < 0) {
			lRangeY = -lRangeY;
		}

#ifdef _USE_EXTENDED_LOG_COLLIDER
		gm_serv::Log::debug("asteroid PosX = %f",(*iAsteroid)->getPosX());
		gm_serv::Log::debug("asteroid PosY = %f",(*iAsteroid)->getPosY());
		gm_serv::Log::debug("range X = %f",lRangeX);
		gm_serv::Log::debug("range Y = %f",lRangeY);
#endif

		if (lRangeX <= lControlRange && lRangeY <= lControlRange) {
#ifdef NDEBUG
			gm_serv::Log::info("Ship & asteroid collided .");
			gm_serv::Log::debug("ship PosX = %f", pShip.getCoordX());
			gm_serv::Log::debug("ship PosY = %f", pShip.getCoordY());
			gm_serv::Log::debug("asteroid PosX = %f", (*iAsteroid)->getPosX());
			gm_serv::Log::debug("asteroid PosY = %f", (*iAsteroid)->getPosY());
			gm_serv::Log::debug("range X = %f", lRangeX);
			gm_serv::Log::debug("range Y = %f", lRangeY);
#endif
			return true;
		}
	}
	return false;
}

bool Collider::shipIsCollided(const std::vector<Debris*> &pDebris,
		const float pRangeDebris, Ship &pShip, const float pRangeShip) {
#ifdef _USE_EXTENDED_LOG_COLLIDER
	gm_serv::Log::info("ship PosX = %f", pShip.getCoordX());
	gm_serv::Log::info("ship PosY = %f",pShip.getCoordY());
#endif

	float lRangeX, lRangeY;
	float lControlRange = pRangeDebris + pRangeShip;
	std::vector<Debris*>::const_iterator iDebris = pDebris.begin();
	for (; iDebris < pDebris.end(); ++iDebris) {
		if (!(*iDebris)->isFlying()) {
			continue;
		}
		lRangeX = (*iDebris)->getPosX() - pShip.getCoordX();
		if (lRangeX < 0) {
			lRangeX = -lRangeX;
		}
		lRangeY = (*iDebris)->getPosY() - pShip.getCoordY();
		if (lRangeY < 0) {
			lRangeY = -lRangeY;
		}

#ifdef _USE_EXTENDED_LOG_COLLIDER
		gm_serv::Log::info("debris PosX = %f",(*iDebris)->getPosX());
		gm_serv::Log::info("debris PosY = %f",(*iDebris)->getPosY());
		gm_serv::Log::info("range X = %f",lRangeX);
		gm_serv::Log::info("range Y = %f",lRangeY);
#endif

		if (lRangeX <= lControlRange && lRangeY <= lControlRange) {
#ifdef NDEBUG
			gm_serv::Log::info("Ship & debris collided .");
			gm_serv::Log::debug("ship PosX = %f", pShip.getCoordX());
			gm_serv::Log::debug("ship PosY = %f", pShip.getCoordY());
			gm_serv::Log::debug("debris PosX = %f", (*iDebris)->getPosX());
			gm_serv::Log::debug("debris PosY = %f", (*iDebris)->getPosY());
			gm_serv::Log::debug("range X = %f", lRangeX);
			gm_serv::Log::debug("range Y = %f", lRangeY);
#endif
			return true;
		}
	}
	return false;
}

} /* namespace gwrld */
