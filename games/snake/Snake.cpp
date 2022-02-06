#include "Snake.hpp"

Snake::Snake(const Octo::Vec2Int& headStartingPos, int startingLength, const Octo::Vec2Int& startingDirection, int speed, Board& board)
    :
board(&board),
direction(startingDirection),
segments(std::vector<Octo::Vec2Int>()),
speed(speed) {
    
    segments.push_back(Octo::Vec2Int(headStartingPos));
    for (int i = 1; i < startingLength; i++) {
        segments.push_back(Octo::Vec2Int(headStartingPos + direction * i));
    }
    SUBJECT_ADD_OBSERVER(Octo::InputSubject, Octo::KeyUpEvent, this);
};

void Snake::OnNotify(const Octo::KeyUpEvent &payload) {
    switch (payload.Keycode) {
        case SDLK_UP:
            direction = { 0, -1 };
            spdlog::info("Up key pressed");
            break;
        case SDLK_DOWN:
            direction = { 0, 1 };
            spdlog::info("Down key pressed");
            break;
        case SDLK_RIGHT:
            direction = { 1, 0 };
            spdlog::info("Right key pressed");
            break;
        case SDLK_LEFT:
            direction = { -1, 0 };
            spdlog::info("Left key pressed");
        default:
            break;
    }
}

void Snake::Tick(float deltaTime) {
    //head
    Octo::Vec2Int step = direction * deltaTime * speed;
    segments[0] += step;
    Octo::Vec2Int nextPosition = segments[0];
    board->SetCell(segments[0], headCell);
        
    for (int i = 1; i < segments.size(); i++) {
        Octo::Vec2Int temp = segments[i];
        segments[i] = nextPosition;
        nextPosition = temp;
        board->SetCell(segments[i], regularCell);
    }
}
