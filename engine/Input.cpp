#include "Input.h"

namespace Octo
{
    template<>
    ObjectPool<ObserverNode<KeyDownEvent>> ObserverSubject<KeyDownEvent>::nodePool(20);
    template<>
    ObjectPool<ObserverNode<KeyUpEvent>> ObserverSubject<KeyUpEvent>::nodePool(20);
    Input InputSubject;
}
