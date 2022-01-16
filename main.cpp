//
//  main.cpp
//  OctoEngine
//
//  Created by Sorh Sorhoski on 16/01/2022.
//

#include <iostream>
#include "engine/Octo.h"
#include "TestGame.h"

int main(int argc, const char * argv[]) {
    TestGame t;
    Octo::Loop loop(&t);
    Octo::WindowParams w;
    w.SetFullScreen = false;
    w.Height = 600;
    w.Width = 800;
    loop.Start(w);
    
    return 0;
}
