//
//  TestGame.cpp
//  OctoEngine
//
//  Created by Sorh Sorhoski on 16/01/2022.
//

#include "TestGame.h"
#include "spdlog/spdlog.h"

void TestGame::Init() {
    SUBJECT_ADD_OBSERVER(Octo::InputSubject, Octo::KeyUpEvent, this);
    direction = Octo::Vec2<int>(1, 0);
    head = Octo::Vec2<int>(1, 1);
    size = Octo::Vec2<int>(100, 100);
}

void TestGame::Tick(float deltaTime) {
    //head.X += direction.X * deltaTime * speed;
    //head.Y += direction.Y * deltaTime * speed;
    if (head.X >= windowWidth - size.X || head.X <= 0) {
        direction *= -1;
    }
    
    Octo::Vec2Int translation = direction * (deltaTime * speed);
    head += translation;
    spdlog::info("HeadPos: " + std::to_string(head.X));
}

void TestGame::Draw() {
    drawRectangle(head.X, head.Y, size.X, size.Y, 0xFFFF00FF);
}

void TestGame::OnNotify(const Octo::KeyUpEvent& payload) {
    if (payload.Keycode == SDLK_SPACE) {
        spdlog::info("Its working");
    }
}

