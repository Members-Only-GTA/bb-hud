#define ABS(a)  (((a) < 0) ? (-(a)) : (a))
#define isNearlyEqualF(a, b, t) (fabs(a - b) <= t)
#define interpF(a, b, f) a = a + (f) * (b - a)
#define norm(value, min, max) (((value) < (min)) ? 0 : (((value) > (max)) ? 1 : (((value) - (min)) / ((max) - (min)))))
#define lerp(no, mi, ma) ( (no) * ((ma) - (mi)) + (mi) )

#define clamp(v, low, high) ((v)<(low) ? (low) : (v)>(high) ? (high) : (v))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define FLASH_ITEM(on, off) (CTimer::m_snTimeInMillisecondsPauseMode % on + off < on)

extern bool faststrcmp(const char* str1, const char* str2, int offset = 0);