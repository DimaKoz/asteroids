#ifndef _DIGIT_HPP_
#define _DIGIT_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsSprite.hpp"
#include "Types.hpp"
#include <vector>

namespace gwrld {
class Digit {
public:
	Digit(gm_serv::Context* pContext);

	void spawn();
	void setCoordinates(float pX, float pY);
	void setNumber(int32_t pNumber);
	void setFlagIsNotDrawing(bool pFlag);

private:
	gm_serv::GraphicsService* mGraphicsService;
	gm_serv::ServiceTime* mTimeService;
	std::vector<gm_serv::GraphicsSprite*> mSprites;
	gm_serv::Location mLocation;
	int32_t mNumber;

};
}
#endif
