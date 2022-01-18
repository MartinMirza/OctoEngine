#ifndef Snake_hpp
#define Snake_hpp

#include <vector>
#include "../../engine/Octo.h"
#include "Board.hpp"

class Snake : protected Octo::IObserver<Octo::KeyUpEvent> {
public:
    Snake(const Octo::Vec2Int& headStartingPos, int startingLength, const Octo::Vec2Int& startingDirection, int speed, Board& board);
    Snake(const Snake& other);
    Snake& operator=(const Snake& other);
    void OnNotify(const Octo::KeyUpEvent& payload) override;
    void Tick(float deltaTime);
private:
    std::vector<Octo::Vec2Int> segments;
    Octo::Vec2Int direction;
    int speed;
    Board* board;
    const uint32_t headSegmentColor = OCTO_CYAN;
    const uint32_t regularSegmentColor = OCTO_BLUE;
    const int headSymbol = 1;
    const int regularSegmentSymbol = 2;
};

#endif /* Snake_hpp */
