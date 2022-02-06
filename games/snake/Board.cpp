#include "Board.hpp"
#include <memory>

BoardCollisionsSubject CollisionSubject;

BoardCollisionsSubject::BoardCollisionsSubject() : Octo::ObserverSubject<BoardCollisionEvent>(5){}

Board::Board(int width, int height)
:
width(width),
height(height),
gridLength(width * height),
cellSize(Octo_windowWidth / width, Octo_windowHeight / height) {
    
    for (int i = 0; i < gridLength; i++) {
        grid.push_back(std::make_unique<BoardCell>());
    }
}

Board::Board(const Board& source) {
    *this = Board(source.width, source.height);
}

Board& Board::operator =(const Board& source) {
    if (&source == this) {
        return *this;
    }
    
    return *this = Board(source.width, source.height);
}

int Board::GetWidth() const {
    return width;
}

int Board::GetHeight() const {
    return height;
}

const Octo::Vec2Int& Board::GetCellSize() const {
    return cellSize;
}

int Board::GetGridLength() const {
    return gridLength;
}

void Board::ClearGrid() {
    for (auto &cell : grid) {
        cell->Symbol = 0;
        cell->Color = emptyColor;
    }
}


void Board::SetCell(const Octo::Vec2Int& position, const BoardCell& boardCell) {
        int index = width * position.Y + position.X;
        if (gridLength > index && index > 0) {
            *grid[index] = boardCell;
        }
    
    if (position.X > width || position.X < 0 || position.Y > height || position.Y < 0) {
        BoardCollisionEvent e {position, boardCell.Symbol, -1};
        SUBJECT_NOTIFY_OBSERVERS(CollisionSubject, BoardCollisionEvent, e);
    }
    else if (int current = grid[position.Y * width + position.X]->Symbol != 0) {
        BoardCollisionEvent e {position, boardCell.Symbol, current};
        SUBJECT_NOTIFY_OBSERVERS(CollisionSubject, BoardCollisionEvent, e);
    }
}

void Board::Draw() const {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            uint32_t color = grid[y * width + x]->Color;
//            auto colorIterator = symbolToColorMap.find(value);
           // if (colorIterator != symbolToColorMap.end()) {
            Octo_drawRectangle(x * cellSize.X, y * cellSize.Y, cellSize.X, cellSize.Y, color);
                
        }
    }
}
