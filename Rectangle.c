#include "Despicable/Despicable.h"

void Despicable_Rectangle_calculateVertices(Despicable_Rectangle rectangle, f32* dst) {
	for (u32 index = 0; index < 8; ++index) {
		dst[index] = (index % 2 == 0) ?
			rectangle.center.x + (((index/2)%2 == 0)*2-1)*rectangle.width :
			rectangle.center.y + ((index < 4)*2-1)*rectangle.height;
	}
}
