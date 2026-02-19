#pragma once

using ListTag_get_t = void* (*)(void* list, int index);
extern ListTag_get_t ListTag_get;

using ListTag_size_t = int (*)(void*);
extern ListTag_size_t ListTag_size;
