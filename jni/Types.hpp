#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <stdint.h>
#include <cstdlib>

namespace gm_serv {
typedef int32_t status;

const status STATUS_OK 		= 0;
const status STATUS_ERR 	= -1;
const status STATUS_EXIT 	= -2;

typedef int32_t shot_type;

const shot_type SMALL_SHOT 		= 0;
const shot_type NORMAL_SHOT 	= 1;

typedef int32_t shot_location;

const shot_location LOCATION_LEFT 		= 0;
const shot_location LOCATION_RIGHT 		= 1;
const shot_location LOCATION_CENTER 	= 3;

const float RANGE_SPAWN_SHOTS 			= 0.3f;

const int32_t SCORE_MAX = 99999;

typedef int32_t game_status;

const game_status GAME_START 				= 0;
const game_status GAME_FIRST_LVL_STARTING 	= 1;
const game_status GAME_FIRST_LVL_CONTINUE 	= 2;
const game_status GAME_OVER_STARTED 		= 3;
const game_status GAME_OVER_MAKED 			= 4;

struct Location {
	Location() :
			mPosX(0.0f), mPosY(0.0f) {
	}
	;

	void setPosition(float pPosX, float pPosY) {
		mPosX = pPosX;
		mPosY = pPosY;
	}

	float getY() {
		return mPosY;
	}

	float getX() {
		return mPosX;
	}

	void translate(float pAmountX, float pAmountY) {
		mPosX += pAmountX;
		mPosY += pAmountY;
	}

	float mPosX;
	float mPosY;
};
}

// Generates a random value in the range [O, pMax].
#define RAND(pMax) (float(pMax) * float(rand()) / float(RAND_MAX))

// Generates a random value in the range [pMin, pMin+pRange].
#define RAND_MIN_RANGE(pMin, pRange) (float(pRange) * float(rand()) / float(RAND_MAX) + float(pMin))

#endif
