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
    currentGame->OnStopGame();
    IsRunning = false;
}

void Loop::SetupWindow(const WindowParams& params)
{
    Octo_windowWidth = params.Width;
    Octo_windowHeight = params.Height;
    Octo_initializeWindow(params.SetFullScreen);
    Octo_initializeFrameBuffer();
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
            SUBJECT_NOTIFY_OBSERVERS(InputSubject, KeyUpEvent, std::move(e));
        }

        if (sdlEvent.type == SDL_KEYDOWN)
        {
            KeyDownEvent e { sdlEvent.key.keysym.sym };
            SUBJECT_NOTIFY_OBSERVERS(InputSubject, KeyDownEvent, std::move(e));
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

    //spdlog::info(std::to_string(deltaTime));
    currentGame->Tick(deltaTime);
}

void Loop::Draw()
{
    SDL_SetRenderDrawColor(Octo_renderer, 255, 0, 0, 255);
    SDL_RenderClear(Octo_renderer);
    Octo_clearColorBuffer(0x000000);

    currentGame->Draw();

    Octo_renderColorBuffer();
    SDL_RenderPresent(Octo_renderer);
}
 
