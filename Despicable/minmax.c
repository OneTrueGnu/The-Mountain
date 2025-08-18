#include "Despicable.h"

f32 Despicable_min_f32(f32 a, f32 b) {
	return a < b ? a : b;
}
f32 Despicable_max_f32(f32 a, f32 b) {
	return a > b ? a : b;
}
void Despicable_clamp_f32(f32* clamped_value, f32 lower_bound, f32 upper_bound) {
	*clamped_value = Despicable_max_f32(Despicable_min_f32(upper_bound, *clamped_value), lower_bound);
}

f64 Despicable_min_f64(f64 a, f64 b) {
	return a < b ? a : b;
}
f64 Despicable_max_f64(f64 a, f64 b) {
	return a > b ? a : b;
}
void Despicable_clamp_f64(f64* clamped_value, f64 lower_bound, f64 upper_bound) {
	*clamped_value = Despicable_max_f64(Despicable_min_f64(upper_bound, *clamped_value), lower_bound);
}
