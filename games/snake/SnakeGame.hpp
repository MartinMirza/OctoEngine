#ifndef SnakeGame_hpp
#define SnakeGame_hpp

#include <utility>
#include "../../engine/Octo.h"
#include "Board.hpp"
#include "Snake.hpp"

class SnakeGame : public Octo::Game, public Octo::IObserver<BoardCollisionEvent>, public Octo::IObserver<Octo::KeyUpEvent> {
public:
    void Init() override;
    void Tick(float deltaTime) override;
    void Draw() override;
    void OnNotify(const BoardCollisionEvent& payload) override;
    void OnNotify(const Octo::KeyUpEvent& payload) override;
    void OnStopGame() override;
private:
    std::shared_ptr<Board> board;
    std::unique_ptr<Snake> snake;
};

#endif /* SnakeGame_hpp */
