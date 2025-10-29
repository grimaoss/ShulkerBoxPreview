#pragma once
#include <string>
#include <stdio.h>

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
     out.append("\n§6 This info appears under\n"); 
     out.append("\n§6 WeaponItem class \n"); 
    //   for some reason 1.16 pdb lacks weaponitem class 
    /// idk if WeaponItemCmp inherits from WeaponItem itself

}
