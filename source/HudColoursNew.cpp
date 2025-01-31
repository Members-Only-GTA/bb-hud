#include "BBHud.h"
#include "HudColoursNew.h"
#include "Utility.h"

using namespace plugin;

CHudColoursNew HudColourNew;

void CHudColoursNew::ReadColorsFromFile() {
    std::ifstream file(PLUGIN_PATH((char*)"BBHud\\data\\hudcolor.dat"));

    if (file.is_open()) {
        int id = 0;
        for (std::string line; getline(file, line);) {
            char name[64];
            int r, g, b, a;

            if (line.empty() || line[0] == '#' || line[0] == ' ' || line[0] == '\t')
                continue;

            if (sscanf(line.c_str(), "%s %d %d %d %d", name, &r, &g, &b, &a) == 5) {
                CRGBA col = CRGBA(
                    static_cast<unsigned char>(r),
                    static_cast<unsigned char>(g),
                    static_cast<unsigned char>(b),
                    static_cast<unsigned char>(a)
                );

                strcpy(m_aColours[id].name, name);
                m_aColours[id].r = col.r;
                m_aColours[id].g = col.g;
                m_aColours[id].b = col.b;
                m_aColours[id].a = col.a;

                id++;
            }
        }
        file.close();
    }
}


CRGBA CHudColoursNew::GetRGB(int color, unsigned char alpha) {
    return CRGBA(m_aColours[color].r, m_aColours[color].g, m_aColours[color].b, alpha);
}

CRGBA CHudColoursNew::GetRGB(const char* name, unsigned char alpha) {
    for (int i = 0; i < 256; i++) {
        if (name[11] == HudColourNew.m_aColours[i].name[11] && faststrcmp(name, HudColourNew.m_aColours[i].name, 12) == 0) {
            return CRGBA(HudColourNew.GetRGBA(i).r, HudColourNew.GetRGBA(i).g, HudColourNew.GetRGBA(i).b, alpha);
        }
    }
}

CRGBA CHudColoursNew::GetRGBA(const char* name) {
    for (int i = 0; i < 256; i++) {
        if (name[11] == HudColourNew.m_aColours[i].name[11] && faststrcmp(name, HudColourNew.m_aColours[i].name, 12) == 0) {
            return HudColourNew.GetRGBA(i);
        }
    }
}

CRGBA CHudColoursNew::GetRGBA(int color) {
    return CRGBA(m_aColours[color].r, m_aColours[color].g, m_aColours[color].b, m_aColours[color].a);
}