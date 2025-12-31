#include "shulkerrenderer.h"
#include "shulkerenderer/colors.h"

bool ShulkerRenderer::sHasPanelTex = false;
mce::TexturePtr ShulkerRenderer::sPanelTex{};
uiutil::NineSlice ShulkerRenderer::sPanelSlice(256.0f, 256.0f, 4.0f, 4.0f);

void ShulkerRenderer::setPanelTexture(mce::TexturePtr const& tex){
    sPanelTex = tex;
    sHasPanelTex = true;
}

void ShulkerRenderer::render(
    MinecraftUIRenderContext* ctx,
    float x,
    float y,
    int index,
    char colorCode
) {
    if (!ctx)
        return;

    //const
    constexpr int   COLS = 9;
    constexpr int   ROWS = 3;
    constexpr float SLOT = 18.0f;
    constexpr float DRAW = 17.5f;
    constexpr float PAD  = 3.0f; 
    constexpr float BEV  = 0.25f;

    const float gridW = COLS * SLOT;
    const float gridH = ROWS * SLOT;

    //
    mce::Color tint = getShulkerTint(colorCode);

    //colorpanel
    mce::Color panelFill {
        tint.r,
        tint.g,
        tint.b,
        0.95f
    };

    //slotclrs
    mce::Color slotBorder = tint;

    mce::Color slotFill {
        tint.r * 0.30f,
        tint.g * 0.30f,
        tint.b * 0.30f,
        1.0f
    };

    mce::Color highlight { 1.0f, 1.0f, 1.0f, 0.15f };
    mce::Color shadow    { 0.0f, 0.0f, 0.0f, 0.22f };

    //panelbg
    RectangleArea panel{};
    panel._x0 = x;
    panel._x1 = x + gridW + PAD * 2.0f;
    panel._y0 = y;
    panel._y1 = y + gridH + PAD * 2.0f;

    ctx->fillRectangle(panel, panelFill, panelFill.a);

    //tophighlight
    {
        RectangleArea r{};
        r._x0 = panel._x0;
        r._x1 = panel._x1;
        r._y0 = panel._y0;
        r._y1 = panel._y0 + BEV;
        ctx->fillRectangle(r, highlight, highlight.a);
    }

    //bottomshadow
    {
        RectangleArea r{};
        r._x0 = panel._x0;
        r._x1 = panel._x1;
        r._y0 = panel._y1 - BEV;
        r._y1 = panel._y1;
        ctx->fillRectangle(r, shadow, shadow.a);
    }

    //slotgrid
    float sx0 = x + PAD;
    float sy0 = y + PAD;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            float sx = sx0 + c * SLOT;
            float sy = sy0 + r * SLOT;

            RectangleArea slot{};
            slot._x0 = sx;
            slot._x1 = sx + DRAW;
            slot._y0 = sy;
            slot._y1 = sy + DRAW;

            ctx->fillRectangle(slot, slotBorder, slotBorder.a);

            RectangleArea inner{};
            inner._x0 = slot._x0 + BEV;
            inner._x1 = slot._x1 - BEV;
            inner._y0 = slot._y0 + BEV;
            inner._y1 = slot._y1 - BEV;

            ctx->fillRectangle(inner, slotFill, slotFill.a);

            //highlight
            {
                RectangleArea hl{};
                hl._x0 = inner._x0;
                hl._x1 = inner._x1;
                hl._y0 = inner._y0;
                hl._y1 = inner._y0 + BEV;
                ctx->fillRectangle(hl, highlight, highlight.a);
            }

            //shadow
            {
                RectangleArea sh{};
                sh._x0 = inner._x0;
                sh._x1 = inner._x1;
                sh._y0 = inner._y1 - BEV;
                sh._y1 = inner._y1;
                ctx->fillRectangle(sh, shadow, shadow.a);
            }
        }
    }
}
