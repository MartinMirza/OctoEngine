#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* colorBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;
int windowWidth = 1920;
int windowHeight = 1080;


bool initializeWindow(bool fullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    
    if (fullScreen == true) {
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        windowWidth = displayMode.w;
        windowHeight = displayMode.h;
    }

    // Create a SDL Window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }
    
    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }
    
    return true;
}

bool initializeFrameBuffer(void) {
    
    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    
    if (!colorBuffer) {
        fprintf(stderr, "Cannot allocate frame buffer");
        return false;
    }
    
    colorBufferTexture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           windowWidth,
                                           windowHeight);

    return true;
}

int getCBIndex(int x, int y) {
    return y * windowWidth + x;
}

bool drawPixel(int x, int y, uint32_t color) {
    if (x > 0 && x <= windowWidth && y > 0 && y <= windowHeight) {
        colorBuffer[getCBIndex(x, y)] = color;
        return true;
    }
    return false;
}

void drawRectangle(int x, int y, int width, int height, uint32_t color) {
    for (int ix = x; ix < x + width; ix++) {
        for (int iy = y; iy < y + height; iy++) {
            drawPixel(ix, iy, color);
        }
    }
}

void drawGrid(int multiple, uint32_t color) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            if (y % multiple == 0 || x % multiple == 0) {
                colorBuffer[getCBIndex(x, y)] = color;
            }
        }
    }
}

void clearColorBuffer(uint32_t color) {
    memset(colorBuffer, 0x00000000, windowWidth * windowHeight);
//    for (int i = 0; i < windowWidth * windowHeight; i++) {
//        colorBuffer[i] = color;
//    }
}

void renderColorBuffer(void) {
    SDL_UpdateTexture(colorBufferTexture,
                      NULL,
                      colorBuffer,
                      windowWidth * sizeof(uint32_t));
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void destroyWindow(void) {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(colorBufferTexture);
    SDL_Quit();
}
