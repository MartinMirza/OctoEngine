#include "SnakeGame.hpp"

//TODO move initialization from constructor to init to watch the initialization order
void SnakeGame::Init() {
    board = std::make_shared<Board>(80, 80);
    snake = std::make_unique<Snake>(Octo::Vec2Int(40, 40), 8, Octo::Vec2Int(1, 0), 10, *board);
    SUBJECT_ADD_OBSERVER(CollisionSubject, BoardCollisionEvent, this);
    SUBJECT_ADD_OBSERVER(Octo::InputSubject, Octo::KeyUpEvent, this);
}

void SnakeGame::Tick(float deltaTime) {
    board->ClearGrid();
    //board->UpdateBoardNoCollisions(Octo::Vec2Int(40, 40), 1);
    snake->Tick(deltaTime);
}

void SnakeGame::Draw() {
    board->Draw();
}

void SnakeGame::OnNotify(const BoardCollisionEvent& payload) {
}

void SnakeGame::OnNotify(const Octo::KeyUpEvent& payload) {
    spdlog::info("Key pressed");
}

void SnakeGame::OnStopGame() {
    SUBJECT_REMOVE_OBSERVER(CollisionSubject, BoardCollisionEvent, this);
    SUBJECT_REMOVE_OBSERVER(Octo::InputSubject, Octo::KeyUpEvent, this);
}
