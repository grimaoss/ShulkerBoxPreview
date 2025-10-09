#pragma once
#include "itemstackbase.h"
#include <string>
#include <stdio.h>


class ShulkerBoxBlockItem;
class Level;

// ptr type
using Shulker_appendHover_t = void (*)(void *self, void *stack, void *level, std::string &out, bool flag);

// orig
Shulker_appendHover_t ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

// hook append
void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem *self,
    void *stack,
    void *level,
    std::string &out,
    bool flag)
{
    if (ShulkerBoxBlockItem_appendFormattedHovertext_orig)
        ShulkerBoxBlockItem_appendFormattedHovertext_orig(self, stack, level, out, flag);
        printf("\n\nHook gets called");
        out.append("\n§6Preview Goes Here");
}
