#include <SDL.h>
#include <utility>
#include "Loop.h"
#include "Input.h"
#include "spdlog/spdlog.h"
#include "display/display.h"

using namespace Octo;

void Loop::Start(const WindowParams& params)
{
    IsRunning = true;
    SetupWindow(params);
    currentGame->Init();
    DoLoop();
}

void Loop::Stop()
{
    IsRunning = false;
}

void Loop::SetupWindow(const WindowParams& params)
{
    windowWidth = params.Width;
    windowHeight = params.Height;
    initializeWindow(params.SetFullScreen);
    initializeFrameBuffer();
}

void Loop::ProcessInput() const
{
    SDL_Event sdlEvent;
    //auto keyUpSubject = static_cast<ObserverSubject<KeyUpEvent>*>(&InputSubject);
    //auto keyDownSubject = static_cast<ObserverSubject<KeyDownEvent>*>(&InputSubject);

    while (SDL_PollEvent(&sdlEvent))
    {
        if (sdlEvent.type == SDL_KEYUP)
        { 
            KeyUpEvent e { sdlEvent.key.keysym.sym };
            SUBJECT_NOTIFY_OBSERVERS(InputSubject, KeyUpEvent, e);
        }

        if (sdlEvent.type == SDL_KEYDOWN)
        {
            KeyDownEvent e { sdlEvent.key.keysym.sym };
            SUBJECT_NOTIFY_OBSERVERS(InputSubject, KeyDownEvent, e);
        }
    }
}

void Loop::DoLoop()
{
    while (IsRunning == true)
    {
        ProcessInput();
        Tick();
        Draw();
    }
}

void Loop::Tick()
{
    float deltaTime = ((float)SDL_GetTicks() - tickstampFromLastFrame) / 1000.0f;
    tickstampFromLastFrame = SDL_GetTicks();

    spdlog::info(std::to_string(deltaTime));
    currentGame->Tick(deltaTime);
}

void Loop::Draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    clearColorBuffer(0x000000);

    currentGame->Draw();

    renderColorBuffer();
    SDL_RenderPresent(renderer);
}
 
