#ifndef Snake_hpp
#define Snake_hpp

#include <vector>
#include "../../engine/Octo.h"
#include "Board.hpp"

class Snake : protected Octo::IObserver<Octo::KeyUpEvent> {
public:
    Snake(const Octo::Vec2Int& headStartingPos, int startingLength, const Octo::Vec2Int& startingDirection, int speed, Board& board);
    void OnNotify(const Octo::KeyUpEvent& payload) override;
    void Tick(float deltaTime);
private:
    std::vector<Octo::Vec2Int> segments;
    Octo::Vec2Int direction;
    int speed;
    Board* board;
    const BoardCell headCell {OCTO_MAGENTA, 2};
    const BoardCell regularCell {OCTO_BLUE, 1};
};

#endif /* Snake_hpp */
