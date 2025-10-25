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

#define u8enum(enumtype) u8
#define u16enum(enumtype) u16
#define u32enum(enumtype) u32
#define u64enum(enumtype) u64

#define bitfield8 u8
#define bitfield16 u16
#define bitfield32 u32
#define bitfield64 u64

#define enumbitfield8(enumtype) u8
#define enumbitfield16(enumtype) u16
#define enumbitfield32(enumtype) u32
#define enumbitfield64(enumtype) u64

#endif /* Lapidary_h */
