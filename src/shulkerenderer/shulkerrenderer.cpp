#include "shulkerrenderer.h"
#include <cstdio>

namespace {
constexpr int kColumns = 9;
constexpr int kRows = 3;
constexpr float kSlotStride = 18.0f;
constexpr float kSlotDrawSize = 17.5f;
constexpr float kPanelPadding = 6.0f;
constexpr float kCountTextHeight = 6.0f;

const HashedString kFlushMaterial("ui_flush");
const NinesliceHelper kPanelNineSlice(16.0f, 16.0f, 4.0f, 4.0f);

struct CachedUiTextures {
    bool loaded = false;
    mce::TexturePtr panel;
    mce::TexturePtr slot;
};

inline bool hasTexture(const mce::TexturePtr& texture) {
    return static_cast<bool>(texture.mClientTexture);
}

CachedUiTextures& getUiTextures(MinecraftUIRenderContext& ctx) {
    static CachedUiTextures textures;
    if (!textures.loaded) {
        textures.panel = ctx.getTexture(
            ResourceLocation("textures/ui/dialog_background_opaque", ResourceFileSystem::UserPackage),
            false
        );
        textures.slot = ctx.getTexture(
            ResourceLocation("textures/ui/item_cell", ResourceFileSystem::UserPackage),
            false
        );
        textures.loaded = true;
    }
    return textures;
}

void drawPanelTexture(MinecraftUIRenderContext& ctx, const CachedUiTextures& textures, const RectangleArea& panel) {
    if (!hasTexture(textures.panel))
        return;

    kPanelNineSlice.draw(ctx, panel, textures.panel.getClientTexture());
}

void drawSlotTexture(MinecraftUIRenderContext& ctx, const CachedUiTextures& textures, const RectangleArea& slotRect) {
    if (!hasTexture(textures.slot))
        return;

    const glm::vec2 pos{slotRect._x0, slotRect._y0};
    const glm::vec2 size{slotRect._x1 - slotRect._x0, slotRect._y1 - slotRect._y0};
    const glm::vec2 uv{0.0f, 0.0f};
    const glm::vec2 uvSize{1.0f, 1.0f};
    ctx.drawImage(textures.slot.getClientTexture(), pos, size, uv, uvSize, false);
}

void drawStackCountText(
    Font& font,
    float slotX,
    float slotY,
    const char* text,
    const TextMeasureData& measureData,
    const CaretMeasureData& caretData
) {
    const float textWidth = ActiveUIContext->getLineLength(font, text, measureData.fontSize, false);
    const float anchorX = slotX + kSlotDrawSize - 0.5f;
    const float anchorY = slotY + kSlotDrawSize - 1.5f;

    const RectangleArea shadowRect{
        anchorX - textWidth + 1.0f,
        anchorX + 1.0f,
        anchorY - kCountTextHeight + 1.0f,
        anchorY + 1.0f
    };

    const RectangleArea textRect{
        anchorX - textWidth,
        anchorX,
        anchorY - kCountTextHeight,
        anchorY
    };

    ActiveUIContext->drawText(
        font,
        shadowRect,
        text,
        mce::Color{0.0f, 0.0f, 0.0f, 0.75f},
        ui::TextAlignment::Right,
        1.0f,
        measureData,
        caretData
    );

    ActiveUIContext->drawText(
        font,
        textRect,
        text,
        mce::Color{1.0f, 1.0f, 1.0f, 1.0f},
        ui::TextAlignment::Right,
        1.0f,
        measureData,
        caretData
    );
}
} // namespace

void ShulkerRenderer::render(
    MinecraftUIRenderContext* ctx,
    float x,
    float y,
    int index,
    char colorCode
) {
    if (!ctx || !ActiveUIContext || !ActiveUIFont)
        return;

    const mce::Color tint = getShulkerTint(colorCode);
    const CachedUiTextures& textures = getUiTextures(*ctx);

    const RectangleArea panelRect{
        x,
        x + kColumns * kSlotStride + kPanelPadding * 2.0f,
        y,
        y + kRows * kSlotStride + kPanelPadding * 2.0f
    };

    drawPanelTexture(*ctx, textures, panelRect);
    ctx->flushImages(tint, 1.0f, kFlushMaterial);

    const float slotOriginX = x + kPanelPadding;
    const float slotOriginY = y + kPanelPadding;

    Font& font = *ActiveUIFont;

    TextMeasureData measureData{};
    measureData.fontSize = 1.0f;
    measureData.renderShadow = false;

    CaretMeasureData caretData{};
    caretData.position = 0;
    caretData.shouldRender = false;

    for (int row = 0; row < kRows; ++row) {
        for (int column = 0; column < kColumns; ++column) {
            const int slotIndex = row * kColumns + column;
            ShulkerSlotCache& slotCache = ShulkerCache[index][slotIndex];

            const float slotX = slotOriginX + column * kSlotStride;
            const float slotY = slotOriginY + row * kSlotStride;

            const RectangleArea slotRect{
                slotX,
                slotX + kSlotDrawSize,
                slotY,
                slotY + kSlotDrawSize
            };
            drawSlotTexture(*ctx, textures, slotRect);

            if (!slotCache.valid || slotCache.count <= 1)
                continue;

            char countText[8];
            std::snprintf(countText, sizeof(countText), "%u", slotCache.count);
            drawStackCountText(font, slotX, slotY, countText, measureData, caretData);
        }
    }

    ctx->flushImages(tint, 1.0f, kFlushMaterial);
    ctx->flushText(0.0f, std::nullopt);
}

