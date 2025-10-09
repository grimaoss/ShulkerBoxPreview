#pragma once
#include <string>
#include <stdio.h>
#include "itemhooks.h"

class WeaponItem;


using Weapon_appendHover_t =
    void (*)(void* self, void* stack, void* level, std::string& out, bool flag);

Weapon_appendHover_t WeaponItem_appendFormattedHovertext_orig = nullptr;

void WeaponItem_appendFormattedHovertext_hook(
    void* self,
    void* stack,
    void* level,
    std::string& out,
    bool flag)
{
    if (WeaponItem_appendFormattedHovertext_orig) {
        WeaponItem_appendFormattedHovertext_orig(self, stack, level, out, flag);
    } 
     out.append("\n§6Info goes here"); 
}
