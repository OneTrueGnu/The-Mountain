#ifndef Despicable_h
#define Despicable_h

#include <Lapidary.h>

typedef struct {
	f32 x;
	f32 y;
} Despicable_2DVector;

Despicable_2DVector Despicable_2DVector_sum(Despicable_2DVector, Despicable_2DVector);
void Despicable_2DVector_add(Despicable_2DVector* dst, Despicable_2DVector addend);

f32 Despicable_2DVector_getMagnitude(Despicable_2DVector);
i32 Despicable_2DVector_setMagnitude(Despicable_2DVector*, f32 new_magnitude);
i32 Despicable_2DVector_normalize(Despicable_2DVector*);

f32 Despicable_2DVector_getDirection(Despicable_2DVector);
void Despicable_2DVector_setDirection(Despicable_2DVector*, f32 new_direction);

void Despicable_2DVector_scale(Despicable_2DVector*, f32 scale_factor);

typedef struct {
	Despicable_2DVector center;
	f32 width;
	f32 height;
} Despicable_Rectangle;

#endif /* Despicable_h */
