#pragma once
#include <cstddef>

using CompoundTag_getList_t = void* (*)(void* compound, const char* key, size_t len);
extern CompoundTag_getList_t CompoundTag_getList;

using CompoundTag_contains_t = bool (*)(void* compound, const char* key, size_t len);
extern CompoundTag_contains_t CompoundTag_contains;

using CompoundTag_getByte_t = unsigned char (*)(void*, const char*, size_t);
extern CompoundTag_getByte_t CompoundTag_getByte;
