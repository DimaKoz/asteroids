#include "Context.hpp"
#include "GameWorld.hpp"
#include "EventLoop.hpp"
#include "GraphicsService.hpp"
#include "InputService.hpp"
#include "Sensor.hpp"
#include "SoundService.hpp"
#include "ServiceTime.hpp"
#include "Log.hpp"

void android_main(android_app* pApplication) {
	gm_serv::EventLoop lEventLoop(pApplication);
	gm_serv::Sensor lAccelerometer(lEventLoop, ASENSOR_TYPE_ACCELEROMETER);

	// Creates services.
	gm_serv::ServiceTime lTimeService;
	gm_serv::GraphicsService lGraphicsService(pApplication, &lTimeService);
	gm_serv::InputService lInputService(pApplication, &lAccelerometer,
			lGraphicsService.getWidth(), lGraphicsService.getHeight());
	gm_serv::SoundService lSoundService(pApplication);

	// Fills the context.
	gm_serv::Context lContext = { &lGraphicsService, &lInputService,
			&lSoundService, &lTimeService };

	// Starts the game loop.
	gwrld::GameWorld lGameWorld(&lContext);
	lEventLoop.run(&lGameWorld, &lInputService);
}
