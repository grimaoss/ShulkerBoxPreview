#pragma once
#include <stdio.h>

class HoverRenderer;

using RenderHoverBoxFn = void (*)(void* self, void* ctx, void* client, void* aabb, float someFloat);

RenderHoverBoxFn HoverRenderer_renderHoverBox_orig = nullptr;

void HoverRenderer_renderHoverBox_hook(void* self, void* ctx, void* client, void* aabb, float someFloat) {
    auto hover = reinterpret_cast<HoverRenderer*>(self);
    
        // printf("\n renderHoverBox hook fired!\n");

    HoverRenderer_renderHoverBox_orig(self, ctx, client, aabb, someFloat);
}