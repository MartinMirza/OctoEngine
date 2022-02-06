//
//  main.cpp
//  OctoEngine
//
//  Created by Sorh Sorhoski on 16/01/2022.
//

#include <iostream>
#include "engine/Octo.h"
#include "games/snake/SnakeGame.hpp"
#include "spdlog/spdlog.h"


int main(int argc, const char * argv[]) {
    SnakeGame g;
    Octo::Loop loop(&g);
    Octo::WindowParams w;
    w.SetFullScreen = false;
    w.Height = 600;
    w.Width = 800;
    loop.Start(w);
    
    return 0;
}
