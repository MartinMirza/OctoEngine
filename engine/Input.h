#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <typeinfo>
#include "Observer.h"

namespace Octo
{

	struct KeyUpEvent
	{
		SDL_Keycode Keycode;
	};

	struct KeyDownEvent
	{
		SDL_Keycode Keycode;
	};

	class Input : public ObserverSubject<KeyDownEvent>, public ObserverSubject<KeyUpEvent>
	{
    public:
        Input(int keyDownEventPoolSize, int keyUpDownEventPoolSize);
	};

	extern Input InputSubject;
}

#endif
