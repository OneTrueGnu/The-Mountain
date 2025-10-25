#ifndef Lapidary_h
#define Lapidary_h
 
#include <stdint.h>

#if defined(__clang__)

#pragma clang diagnostic error "-Wimplicit-function-declaration"
#pragma clang diagnostic error "-Wreturn-stack-address"
#pragma clang diagnostic error "-Wimplicit-int"

#endif

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

typedef int8_t		i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

typedef float 		f32;
typedef double		f64;

typedef unsigned char	ubyte;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;

#endif /* Lapidary_h */
