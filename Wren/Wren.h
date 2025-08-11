#ifndef Wren_h
#define Wren_h

#include <Despicable.h>
#include <Lapidary.h>
#include <SDL3/SDL.h>

typedef struct {
	u8 red;
	u8 green;
	u8 blue;
} Wren_RGBColor;

typedef struct {
	Despicable_Rectangle* rectangle;
	Wren_RGBColor color;
} Wren_GraphicsObject;

void Wren_GraphicsObject_render(Wren_GraphicsObject, SDL_Renderer*);

#endif /* Wren_h */
