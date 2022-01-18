#ifndef Display_h
#define Display_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

extern int Octo_windowWidth;
extern int Octo_windowHeight;
extern SDL_Window* Octo_window;
extern SDL_Renderer* Octo_renderer;
extern uint32_t* Octo_colorBuffer;
extern SDL_Texture* Octo_colorBufferTexture;

bool Octo_initializeWindow(bool fullscreen);
bool Octo_initializeFrameBuffer(void);
int getCBIndex(int x, int y);
bool Octo_drawPixel(int x, int y, uint32_t color);
void Octo_drawRectangle(int x, int y, int width, int height, uint32_t color);
void Octo_drawGrid(int multiple, uint32_t color);
void Octo_clearColorBuffer(uint32_t color);
void Octo_renderColorBuffer(void);
void Octo_destroyWindow(void);

#ifdef __cplusplus
}
#endif

#endif
