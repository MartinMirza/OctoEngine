#include "display.h"

SDL_Window* Octo_window = NULL;
SDL_Renderer* Octo_renderer = NULL;
uint32_t* Octo_colorBuffer = NULL;
SDL_Texture* Octo_colorBufferTexture = NULL;
int Octo_windowWidth = 1920;
int Octo_windowHeight = 1080;

bool Octo_initializeWindow(bool fullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    
    if (fullScreen == true) {
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        Octo_windowWidth = displayMode.w;
        Octo_windowHeight = displayMode.h;
    }

    // Create a SDL Window
    Octo_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Octo_windowWidth,
        Octo_windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!Octo_window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }
    
    // Create a SDL renderer
    Octo_renderer = SDL_CreateRenderer(Octo_window, -1, 0);
    if (!Octo_renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }
    
    return true;
}

bool Octo_initializeFrameBuffer(void) {
    
    Octo_colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * Octo_windowWidth * Octo_windowHeight);
    
    if (!Octo_colorBuffer) {
        fprintf(stderr, "Cannot allocate frame buffer");
        return false;
    }
    
    Octo_colorBufferTexture = SDL_CreateTexture(Octo_renderer,
                                           SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           Octo_windowWidth,
                                           Octo_windowHeight);

    return true;
}

int getCBIndex(int x, int y) {
    return y * Octo_windowWidth + x;
}

bool Octo_drawPixel(int x, int y, uint32_t color) {
    if (x > 0 && x <= Octo_windowWidth && y > 0 && y <= Octo_windowHeight) {
        Octo_colorBuffer[getCBIndex(x, y)] = color;
        return true;
    }
    return false;
}

void Octo_drawRectangle(int x, int y, int width, int height, uint32_t color) {
    for (int ix = x; ix < x + width; ix++) {
        for (int iy = y; iy < y + height; iy++) {
            Octo_colorBuffer[getCBIndex(ix, iy)] = color;
        }
    }
}

void Octo_drawGrid(int multiple, uint32_t color) {
    for (int y = 0; y < Octo_windowHeight; y++) {
        for (int x = 0; x < Octo_windowWidth; x++) {
            if (y % multiple == 0 || x % multiple == 0) {
                Octo_drawPixel(x, y, color);
            }
        }
    }
}

void Octo_clearColorBuffer(uint32_t color) {
    memset(Octo_colorBuffer, 0x00000000, Octo_windowWidth * Octo_windowHeight);
//    for (int i = 0; i < windowWidth * windowHeight; i++) {
//        colorBuffer[i] = color;
//    }
}

void Octo_renderColorBuffer(void) {
    SDL_UpdateTexture(Octo_colorBufferTexture,
                      NULL,
                      Octo_colorBuffer,
                      Octo_windowWidth * sizeof(uint32_t));
    SDL_RenderCopy(Octo_renderer, Octo_colorBufferTexture, NULL, NULL);
}

void Octo_destroyWindow(void) {
    free(Octo_colorBuffer);
    SDL_DestroyRenderer(Octo_renderer);
    SDL_DestroyWindow(Octo_window);
    SDL_DestroyTexture(Octo_colorBufferTexture);
    SDL_Quit();
}
