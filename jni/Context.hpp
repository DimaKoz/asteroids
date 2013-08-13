#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include "Types.hpp"

namespace gm_serv {
class GraphicsService;
class InputService;
class SoundService;
class ServiceTime;

struct Context {
	GraphicsService* mGraphicsService;
	InputService* mInputService;
	SoundService* mSoundService;
	ServiceTime* mTimeService;
};
}
#endif
