#ifndef Board_hpp
#define Board_hpp

#include <utility>
#include <vector>
#include "../../engine/Octo.h"

struct BoardCell {
    u_int32_t Color = OCTO_BLACK;
    int Symbol = 0;
};

struct BoardCollisionEvent {
    Octo::Vec2Int Cell;
    int Collider1;
    int Collider2;
};

class BoardCollisionsSubject : public Octo::ObserverSubject<BoardCollisionEvent> {
    
public:
    BoardCollisionsSubject();
};

class Board {
public:
    Board(int width, int height);
    Board(const Board& source);
    Board& operator =(const Board& source);
    int GetWidth() const;
    int GetHeight() const;
    const Octo::Vec2Int& GetCellSize() const;
    int GetGridLength() const;
    void ClearGrid();
    void SetCell(const Octo::Vec2Int& position, const BoardCell& cell);
    void Draw() const;
private:
    std::vector<std::unique_ptr<BoardCell>> grid;
    int gridLength;
    Octo::Vec2Int cellSize;
    int width;
    int height;
    const uint32_t emptyColor = OCTO_BLACK;
};

extern BoardCollisionsSubject CollisionSubject;

#endif /* Board_hpp */
