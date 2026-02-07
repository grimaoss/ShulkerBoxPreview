#include "itemstackbase.h"

ItemStackBase_ctor_t ItemStackBase_ctor = nullptr;
ItemStackBase_loadItem_t ItemStackBase_loadItem = nullptr;
ItemStackBase_getItem_t ItemStackBase_getItem = nullptr;
ItemStackBase_getDamageValue_t ItemStackBase_getDamageValue = nullptr;
ItemStackBase_getName_t ItemStackBase_getName = nullptr;