//
//  TestGame.h
//  OctoEngine
//
//  Created by Sorh Sorhoski on 16/01/2022.
//

#ifndef TestGame_h
#define TestGame_h

#include "engine/Octo.h"


class TestGame : public Octo::Game, public Octo::IObserver<Octo::KeyUpEvent>
{
public:
    void Init() override;
    void Tick(float deltaTime) override;
    void Draw() override;
    void OnNotify(const Octo::KeyUpEvent& payload) override;
private:
    Octo::Vec2Int head;
    Octo::Vec2Int direction;
    Octo::Vec2Int size;
    float speed = 100;
};

#endif /* TestGame_h */
