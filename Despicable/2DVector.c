#include "Despicable.h"
#include <math.h>

Despicable_2DVector Despicable_2DVector_sum(Despicable_2DVector vector_a, Despicable_2DVector vector_b) {
	return (Despicable_2DVector){
		.x = vector_a.x + vector_b.x,
		.y = vector_a.y + vector_b.y,
	};
}

void Despicable_2DVector_add(Despicable_2DVector* dst, Despicable_2DVector addend) {
	*dst = Despicable_2DVector_sum(*dst, addend);
}

f32 Despicable_2DVector_getMagnitude(Despicable_2DVector vector) {
	return hypotf(vector.x, vector.y);
}
i32 Despicable_2DVector_setMagnitude(Despicable_2DVector* vector, f32 new_magnitude) {
	f32 old_magnitude = Despicable_2DVector_getMagnitude(*vector);
	if (old_magnitude == 0) {
		return 1;
	}
	Despicable_2DVector_scale(vector, new_magnitude/old_magnitude);
	return 0;
}
i32 Despicable_2DVector_normalize(Despicable_2DVector* vector) {
	return Despicable_2DVector_setMagnitude(vector, 1);
}

f32 Despicable_2DVector_getDirection(Despicable_2DVector vector) {
	return atan2f(vector.y, vector.x);
}
void Despicable_2DVector_setDirection(Despicable_2DVector* vector, f32 new_direction) {
	float startingMagnitude = Despicable_2DVector_getMagnitude(*vector);
	vector->x = cosf(new_direction) * startingMagnitude;
	vector->y = sinf(new_direction) * startingMagnitude;
}

void Despicable_2DVector_scale(Despicable_2DVector* vector, f32 scale_factor) {
	vector->x *= scale_factor;
	vector->y *= scale_factor;
}
