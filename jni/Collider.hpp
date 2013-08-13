#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include "Types.hpp"
#include "Asteroid.hpp"
#include "Shot.hpp"
#include "Debris.hpp"
#include "vector"

namespace gwrld {

class Collider {
public:
	~Collider();

	//определяет стокновения
	//std::vector<Asteroid*> &pAsteroids - вектор астероидов
	//float pRangeAsteroid - радиус от центра астероида до его границы столкновения
	//const std::vector<Shot*> &pShots - вектор выстрелов
	//float pRangeShot - радиус от центра выстрела до его границы столкновения

	static void checkCollide(const std::vector<Asteroid*> &pAsteroids,
			const float pRangeAsteroid, const std::vector<Shot*> &pShots,
			const float pRangeShot,
			std::vector<Asteroid*> &pIsAsteroidsCollided,
			std::vector<Shot*> &pIsShotsCollided);

	static void checkCollide(const std::vector<Debris*> &pDebris,
			const float pRangeDebris, const std::vector<Shot*> &pShots,
			const float pRangeShot, std::vector<Debris*> &pIsDebrisCollided,
			std::vector<Shot*> &pIsShotsCollided);

	static bool shipIsCollided(const std::vector<Asteroid*> &pAsteroids,
			const float pRangeAsteroid, Ship &pShip, const float pRangeShip);

	static bool shipIsCollided(const std::vector<Debris*> &pDebris,
			const float pRangeDebris, Ship &pShip, const float pRangeShip);

private:
	Collider();

};
} /* namespace gwrld */
#endif /* COLLIDER_HPP_ */
