#include "Despicable.h"

void Despicable_2DVector_calculateVertices_intoVectors(Despicable_Rectangle rectangle, Despicable_2DVector* dst) {
	Despicable_Rectangle_calculateVertices_intoFloats(rectangle, (f32*)dst);
}
void Despicable_Rectangle_calculateVertices_intoFloats(Despicable_Rectangle rectangle, f32* dst) {
	const f32 top = rectangle.center.y - rectangle.height/2;
	const f32 left = rectangle.center.x - rectangle.width/2;
	const f32 bottom = rectangle.center.y + rectangle.height/2;
	const f32 right = rectangle.center.x + rectangle.width/2;

	dst[0] = left;	dst[1] = top;
	dst[2] = right;	dst[3] = top;
	dst[4] = left;	dst[5] = bottom;
	dst[6] = right;	dst[7] = bottom;
}

