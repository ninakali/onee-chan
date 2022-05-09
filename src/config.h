#ifndef __CONFIG_H__
#define __CONFIG_H__

#define BUILD_STRING "Fake86 v0.13.10.2+"

//be sure to only define ONE of the CPU_* options at any given time, or
//you will likely get some unexpected/bad results!
//#define CPU_8086
#define CPU_186
//#define CPU_V20
//#define CPU_286

#if defined(CPU_8086)
	#define CPU_CLEAR_ZF_ON_MUL
	#define CPU_ALLOW_POP_CS
#else
	#define CPU_ALLOW_ILLEGAL_OP_EXCEPTION
	#define CPU_LIMIT_SHIFT_COUNT
#endif

#if defined(CPU_V20)
	#define CPU_NO_SALC
#endif

#if defined(CPU_286) || defined(CPU_386)
	#define CPU_286_STYLE_PUSH_SP
#else
	#define CPU_SET_HIGH_FLAGS
#endif

#define TIMING_INTERVAL 15


#endif
