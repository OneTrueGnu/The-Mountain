#include <SDL3/SDL.h>

#include "Wren.h"

static SDL_FRect Wren_GraphicsObject_toSDLFrect(Wren_GraphicsObject graphics_object) {
	return (SDL_FRect){
		.x = graphics_object.rectangle->center.x - graphics_object.rectangle->width/2,
		.y = graphics_object.rectangle->center.y - graphics_object.rectangle->height/2,
		.w = graphics_object.rectangle->width,
		.h = graphics_object.rectangle->height,
	};
}

void Wren_GraphicsObject_render(Wren_GraphicsObject graphics_object, SDL_Renderer* sdl_renderer) {
}
