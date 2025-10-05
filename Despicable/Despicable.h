#ifndef Despicable_h
#define Despicable_h

#include <Lapidary.h>

f32 Despicable_min_f32(f32, f32);
f32 Despicable_max_f32(f32, f32);
void Despicable_clamp_f32(f32* clamped_value, f32 lower_bound, f32 upper_bound);

f64 Despicable_min_f64(f64, f64);
f64 Despicable_max_f64(f64, f64);
void Despicable_clamp_f64(f64* clamped_value, f64 lower_bound, f64 upper_bound);

typedef struct {
	union {
		f32 x;
		f32 u;
	};
	union {
		f32 y;
		f32 v;
	};
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

/*
 * The size of `dst` must be large enough to hold 4 `Despicable_2DVector`s
 */
void Despicable_Rectangle_calculateVertices_intoVectors(Despicable_Rectangle, Despicable_2DVector* dst);

/*
 * The size of `dst` must be large enough to hold 8 32-bit floats.
 */
void Despicable_Rectangle_calculateVertices_intoFloats(Despicable_Rectangle, f32* dst);

#endif /* Despicable_h */
