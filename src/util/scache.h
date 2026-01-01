#pragma once
#include <cstddef>
#include <cstdint>

class ItemStackBase;

struct ItemStackBaseOpaque {
    alignas(16) std::byte data[0x300];
};

static inline ItemStackBase* asISB(ItemStackBaseOpaque& o) {
    return reinterpret_cast<ItemStackBase*>(o.data);
}

#define SHULKER_CACHE_SIZE 16

extern ItemStackBaseOpaque gShulkerCache[SHULKER_CACHE_SIZE][27];
extern bool gShulkerCacheInit[SHULKER_CACHE_SIZE][27];
