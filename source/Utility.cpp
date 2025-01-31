#include "BBHud.h"
#include "Utility.h"
#include "CSprite2d.h"

bool faststrcmp(const char* str1, const char* str2, int offset) {
    str1 += offset;
    str2 += offset;
    for (; *str1; str1++, str2++) {
        if (*str1 != *str2)
            return true;
    }
    return *str2 != '\0';
}