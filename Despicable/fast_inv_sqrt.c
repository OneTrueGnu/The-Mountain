#include "Despicable.h"

f32 Despicable_fastInvSqrt(f32 num, u8 newton_iterations) {
	u32 bit_manipulatable;

	bit_manipulatable  = *(u32*)&num;
	bit_manipulatable = 0x5f3759df - ( bit_manipulatable >> 1 );
	num = *(u32*)&bit_manipulatable;

	for (u8 completed_iterations = 0; completed_iterations < newton_iterations; ++completed_iterations) {
		num = num * ( 1.5f - ( 0.5f * num * num * num ) );
	}

	return num;
}
