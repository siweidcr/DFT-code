#ifndef __duff_h__
#define __duff_h__
/*
#define Duff_1(PARA_C, ...) (case 1: ##__VA_ARGS__;)
#define Duff_2(PARA_C, ...) (case 2: ##__VA_ARGS__;) Duff_1(PARA_C, ...)
#define Duff_3(PARA_C, ...) (case 3: ##__VA_ARGS__;) Duff_2(PARA_C, ...)
#define Duff_4(PARA_C, ...) (case 4: ##__VA_ARGS__;) Duff_3(PARA_C, ...)
#define Duff_5(PARA_C, ...) (case 5: ##__VA_ARGS__;) Duff_4(PARA_C, ...)
#define Duff_6(PARA_C, ...) (case 6: ##__VA_ARGS__;) Duff_5(PARA_C, ...)
#define Duff_7(PARA_C, ...) (case 7: ##__VA_ARGS__;) Duff_6(PARA_C, ...)

#define Duff(PARA_C, ...) Duff_##PARA_C(PARA_C, ...)
*/

// 定义不同数量的 Duff cases
#define Duff_1(...) case 1: __VA_ARGS__
#define Duff_2(...) case 2: __VA_ARGS__; Duff_1(__VA_ARGS__)
#define Duff_3(...) case 3: __VA_ARGS__; Duff_2(__VA_ARGS__)
#define Duff_4(...) case 4: __VA_ARGS__; Duff_3(__VA_ARGS__)
#define Duff_5(...) case 5: __VA_ARGS__; Duff_4(__VA_ARGS__)
#define Duff_6(...) case 6: __VA_ARGS__; Duff_5(__VA_ARGS__)
#define Duff_7(...) case 7: __VA_ARGS__; Duff_6(__VA_ARGS__)
#define Duff_8(...) case 8: __VA_ARGS__; Duff_7(__VA_ARGS__)
#define Duff_9(...) case 9: __VA_ARGS__; Duff_8(__VA_ARGS__)
#define Duff_10(...) case 10: __VA_ARGS__; Duff_9(__VA_ARGS__)
#define Duff_11(...) case 11: __VA_ARGS__; Duff_10(__VA_ARGS__)
#define Duff_12(...) case 12: __VA_ARGS__; Duff_11(__VA_ARGS__)
#define Duff_13(...) case 13: __VA_ARGS__; Duff_12(__VA_ARGS__)
#define Duff_14(...) case 14: __VA_ARGS__; Duff_13(__VA_ARGS__)
#define Duff_15(...) case 15: __VA_ARGS__; Duff_14(__VA_ARGS__)

// 通过参数选择合适的 Duff 宏
#define Duff(PARA_C, ...) Duff_##PARA_C(__VA_ARGS__)
#endif

