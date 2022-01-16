#ifndef Display_h
#define Display_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

extern int windowWidth;
extern int windowHeight;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* colorBuffer;
extern SDL_Texture* colorBufferTexture;

bool initializeWindow(bool fullscreen);
bool initializeFrameBuffer(void);
int getCBIndex(int x, int y);
bool drawPixel(int x, int y, uint32_t color);
void drawRectangle(int x, int y, int width, int height, uint32_t color);
void drawGrid(int multiple, uint32_t color);
void clearColorBuffer(uint32_t color);
void renderColorBuffer(void);
void destroyWindow(void);

#ifdef __cplusplus
}
#endif

#endif
