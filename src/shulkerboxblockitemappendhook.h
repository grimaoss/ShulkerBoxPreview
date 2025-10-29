#pragma once
#include "itemstackbase.h"
#include <string>
#include <stdio.h>

class ShulkerBoxBlockItem;
class Level;

using Shulker_appendHover_t =
    void (*)(void *self, ItemStackBase *stack, void *level, std::string &out, bool flag);

Shulker_appendHover_t ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem *self,
    ItemStackBase *stack,
    void *level,
    std::string &out,
    bool flag)
{
    if (ShulkerBoxBlockItem_appendFormattedHovertext_orig)
        ShulkerBoxBlockItem_appendFormattedHovertext_orig(self, stack, level, out, flag);

    auto item = reinterpret_cast<ItemStackBase *>(stack);
    if (item && item->mUserData)
        out.append("\n§6Contains Items\n");
    else
        out.append("\n§7Empty Shulker Box\n");

}
