#ifndef _GWRLD_BACKGROUND_HPP_
#define _GWRLD_BACKGROUND_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsTileMap.hpp"
#include "Types.hpp"

namespace gwrld {
class Background {
public:
	Background(gm_serv::Context* pContext);

	void spawn();
	void update();

private:
	gm_serv::ServiceTime* mTimeService;
	gm_serv::GraphicsService* mGraphicsService;

	gm_serv::GraphicsTileMap* mTileMap;
	gm_serv::Location mLocation;
	float mAnimSpeed;
};
}
#endif
