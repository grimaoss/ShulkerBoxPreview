#pragma once
#include <string>
#include <stdio.h>

class HoverRenderer;

using RenderHoverBoxFn = void (*)(void *self, void *ctx, void *client, void *aabb, float someFloat);
RenderHoverBoxFn HoverRenderer_renderHoverBox_orig = nullptr;

void HoverRenderer_renderHoverBox_hook(void *self, void *ctx, void *client, void *aabb, float someFloat)
{
    auto text = reinterpret_cast<std::string *>((uintptr_t)self + 0x10); // mfilteredContent

    if (text && text->find("Shulker Box") != std::string::npos)
    {
        printf("renderHoverBox: shulker detected!\n");
    }

    HoverRenderer_renderHoverBox_orig(self, ctx, client, aabb, someFloat);
}