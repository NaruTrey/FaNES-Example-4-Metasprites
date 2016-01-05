#include "FaNES.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

static uchar i, pad, spriteID, touch;

static uchar catX[2];
static uchar catY[2];
static const uchar catW[2] = {24, 24};
static const uchar catH[2] = {48, 64};

const uchar metaCat1[] = {
//  0,  0,  0x30,   1,
    8,  0,  0x31,   1,
    16, 0,  0x32,   1,
    0,  8,  0x40,   1,
    8,  8,  0x41,   1,
    16, 8,  0x42,   1,
    0,  16, 0x50,   1,
    8,  16, 0x51,   1,
    16, 16, 0x52,   1,
    0,  24, 0x60,   1,
    8,  24, 0x61,   1,
    16, 24, 0x62,   1,
    0,  32, 0x70,   1,
    8,  32, 0x71,   1,
    16, 32, 0x72,   1,
    0,  40, 0x80,   1,
    8,  40, 0x81,   1,
    16, 40, 0x82,   1,
    METASPRITE_END
};

const uchar metaCat2[] = {
    0,  0,  0x33,   1,
    8,  0,  0x34,   1,
    16, 0,  0x35,   1,
    0,  8,  0x43,   1,
    8,  8,  0x44,   1,
    16, 8,  0x45,   1,
    0,  16, 0x53,   1,
    8,  16, 0x54,   1,
    16, 16, 0x55,   1,
    0,  24, 0x63,   1,
    8,  24, 0x64,   1,
    16, 24, 0x65,   1,
    0,  32, 0x73,   1,
    8,  32, 0x74,   1,
    16, 32, 0x75,   1,
    0,  40, 0x83,   1,
    8,  40, 0x84,   1,
    16, 40, 0x85,   1,
    0,  48, 0x93,   1,
    8,  48, 0x94,   1,
    16, 48, 0x95,   1,
//  0,  56, 0xA3,   1,
    8,  56, 0xA4,   1,
    16, 56, 0xA5,   1,
    METASPRITE_END
};

void main(void) {
    setBankSprites(SPRITES_BANK_B);
    catX[0] = 52;
    catY[0] = 100;
    catX[1] = 180;
    catY[1] = 100;
    spriteID = 0;
    for(i = 0; i < 2; ++i) {
        spriteID = newMetasprite(catX[i], catY[i], spriteID, !i ? metaCat1 : metaCat2);
    }
    setPaletteColor(PALETTE_BACKGROUND_1 + 0, 0x0F);
    onGraphics();
    while(TRUE) {
        i = _frameCounter & 1 ? 0x30 : 0x2A;
        setPaletteColor(21, touch ? i : 0x06);
        setPaletteColor(22, touch ? i : 0x28);
        setPaletteColor(23, touch ? i : 0x30);
        spriteID = 0;
        for(i = 0; i < 2; ++i) {
            pad = padPool(i);
            if (pad & PAD_BUTTON_LEFT && catX[i] > 0)
                catX[i] -= 2;
            if (pad & PAD_BUTTON_RIGHT && catX[i] < SCREEN_WIDTH - catW[i])
                catX[i] += 2;
            if (pad & PAD_BUTTON_UP && (catY[i] > 0))
                catY[i] -= 2;
            if (pad & PAD_BUTTON_DOWN && catY[i] < SCREEN_HEIGHT - catH[i])
                catY[i] += 2;
            spriteID = setMetaspritePosition(catX[i], catY[i], spriteID, !i ? metaCat1 : metaCat2);
        }
        touch = (catX[0] + catW[0] < catX[1] ||
            catX[0] >= catX[1] + catW[1] ||
            catY[0] + catH[0] < catY[1] ||
            catY[0] >= catY[1] + catH[1]) ? FALSE : TRUE;
        waitFrame();
    }
}
