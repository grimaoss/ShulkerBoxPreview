#pragma once
#include "ui/minecraftuirendercontext.h"

static inline mce::Color getShulkerTint(char code){
    switch (code){
    case '0': return {0.45f, 0.42f, 0.40f, 1.0f}; // undyed
    case '1': return {0.78f, 0.76f, 0.74f, 1.0f}; // white
    case '2': return {0.55f, 0.53f, 0.52f, 1.0f}; // light gray
    case '3': return {0.32f, 0.31f, 0.30f, 1.0f}; // gray
    case '4': return {0.06f, 0.05f, 0.05f, 1.0f}; // black
    case '5': return {0.33f, 0.25f, 0.14f, 1.0f}; // brown
    case '6': return {0.55f, 0.20f, 0.18f, 1.0f}; // red
    case '7': return {0.70f, 0.42f, 0.18f, 1.0f}; // orange
    case '8': return {0.78f, 0.72f, 0.22f, 1.0f}; // yellow
    case '9': return {0.42f, 0.65f, 0.22f, 1.0f}; // lime
    case 'a': return {0.18f, 0.40f, 0.18f, 1.0f}; // green
    case 'b': return {0.18f, 0.55f, 0.55f, 1.0f}; // cyan
    case 'c': return {0.28f, 0.46f, 0.62f, 1.0f}; // light blue
    case 'd': return {0.18f, 0.24f, 0.58f, 1.0f}; // blue
    case 'e': return {0.45f, 0.26f, 0.60f, 1.0f}; // purple
    case 'f': return {0.65f, 0.34f, 0.58f, 1.0f}; // magenta
    case 'g': return {0.78f, 0.52f, 0.62f, 1.0f}; // pink
    }
    return {0.55f, 0.55f, 0.55f, 1.0f};
}
static inline char getShulkerColorCodeFromItemId(unsigned short id)
{
    switch (id){
    case 205:   return '0'; // undyed
    case 218:   return '1'; // white

    case 64923: return '7'; // orange
    case 64922: return 'f'; // magenta
    case 64921: return 'c'; // light blue
    case 64920: return '8'; // yellow
    case 64919: return '9'; // lime
    case 64918: return 'g'; // pink
    case 64917: return '3'; // gray
    case 64916: return '2'; // light gray
    case 64915: return 'b'; // cyan
    case 64914: return 'e'; // purple
    case 64913: return 'd'; // blue
    case 64912: return '5'; // brown
    case 64911: return 'a'; // green
    case 64910: return '6'; // red
    case 64909: return '4'; // black

    default:    return '0';
    }
}
