#ifndef LOOP_H
#define LOOP_H

#include <SDL.h>
#include "Observer.h"
#include "Input.h"
#include "Game.h"

namespace Octo 
{
	struct WindowParams
	{
		int Width = 800;
		int Height = 600;
		bool SetFullScreen;
	};

	class Loop 
	{
	public:
		Loop(Game* game) : currentGame(game), 
			IsRunning(false), 
			tickstampFromLastFrame(0) {};
		~Loop() = default;
		bool IsRunning;
		void Start(const WindowParams& params);
		void Stop();
	private:
		int tickstampFromLastFrame;
		Game* currentGame;
		void SetupWindow(const WindowParams& params);
		void ProcessInput() const;
		void DoLoop();
		void Tick();
		void Draw();
	};
}

#endif
