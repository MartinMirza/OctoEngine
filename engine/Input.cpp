#include "Input.h"

namespace Octo
{
//    SUBJECT_TYPE_DEF(KeyDownEvent, 20);
//    SUBJECT_TYPE_DEF(KeyUpEvent, 20);
//
    Input InputSubject(20, 20);

    Input::Input(int keyDownEventPoolSize, int keyUpDownEventPoolSize): ObserverSubject<KeyDownEvent>(keyDownEventPoolSize), ObserverSubject<KeyUpEvent>(keyUpDownEventPoolSize)
    {
    }
}
