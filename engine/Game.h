#ifndef GAME_H
#define GAME_H

namespace Octo 
{
	class Game 
	{
	public:
		virtual void Init() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void Draw() = 0;
        virtual void OnStopGame() = 0;
	};
}

#endif
