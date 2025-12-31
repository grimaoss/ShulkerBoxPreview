#pragma once
#include "item/itemstackbase.h"
#include "shulkerenderer/colors.h"
#include "util/xhelper.h"
#include "util/scache.h"
#include <string>

class ShulkerBoxBlockItem;

using Shulker_appendHover_t = void (*)(void*, ItemStackBase*, void*, std::string&, bool);

inline Shulker_appendHover_t ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

inline void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem* self,
    ItemStackBase* stack,
    void* level,
    std::string& out,
    bool flag)
{
    if (ShulkerBoxBlockItem_appendFormattedHovertext_orig)
        ShulkerBoxBlockItem_appendFormattedHovertext_orig(
            self, stack, level, out, flag);
    size_t pos = out.find('\n');
    if (pos != std::string::npos)
        out.erase(pos);

    if (!stack || !stack->mUserData)
        return;

    if (!CompoundTag_getList ||
        !ListTag_get ||
        !ListTag_size ||
        !ItemStackBase_loadItem)
        return;

    static int sIndex = 0;
    int index = sIndex++ % SHULKER_CACHE_SIZE;

    for (int i = 0; i < 27; ++i)
        gShulkerCacheInit[index][i] = false;

    void* list = CompoundTag_getList(stack->mUserData, "Items", 5);
    if (!list)
        return;

    int size = ListTag_size(list);

    for (int i = 0; i < size && i < 27; ++i) {
        void* tag = ListTag_get(list, i);
        if (!tag)
            continue;

        ItemStackBase* dst = asISB(gShulkerCache[index][i]);
        ItemStackBase_loadItem(dst, tag);
        gShulkerCacheInit[index][i] = true;
    }

    static const char hexmap[] = "0123456789abcdef";
    char hi = hexmap[(index >> 4) & 0xF];
    char lo = hexmap[index & 0xF];

    out.insert(0, "\xC2\xA7");
    out.insert(2, 1, hi);
    out.insert(3, "\xC2\xA7");
    out.insert(5, 1, lo);

    if (!ItemStackBase_getItem || !Item_getId)
        return;

    void* rootItem = ItemStackBase_getItem(stack);
    if (!rootItem)
        return;

    char color = getShulkerColorCodeFromItemId(Item_getId(rootItem));

    out += "\n§7Press §eH§7 to toggle preview";
    out += "\xC2\xA7#";
    out.push_back(color);
    out += "\xC2\xA7v";
}
