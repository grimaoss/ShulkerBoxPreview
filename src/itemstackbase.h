#pragma once
#include <string>

class CompoundTag;
class Block;

class ItemStackBase {
public:
    void* vtable;            // 0x0
    void* mItem;             // 0x8
    CompoundTag* mUserData;  // 0x10
    const Block* mBlock;     // 0x18
    unsigned short mAuxValue; // 0x20
    unsigned char mCount;    // 0x22
    bool mValid;             // 0x23
    bool mShowPickup;        // 0x24
    // 0x28 -> placeon hash
    // 0x48 -> destroy hash
    // 0x58 -> block entity data

    // std::string toDebugString();
};
