//--------------------------------------------------------------------------
void bltBlendRect(Surface &dest, const iRect &r)
{
    if (GameConfig::interface_viewdrawbackgroundmode == VIEW_BACKGROUND_DARK_GRAY_BLEND) {
        dest.BltRoundRect(r, 10, Palette::darkGray256.getColorArray());
    } else if (GameConfig::interface_viewdrawbackgroundmode == VIEW_BACKGROUND_LIGHT_GRAY_BLEND) {
        dest.BltRoundRect(r, 10, Palette::gray256.getColorArray());
    } else if (GameConfig::interface_viewdrawbackgroundmode == VIEW_BACKGROUND_SOLID_BLACK) {
        dest.fillRect(r, Color::black);
    } else if (GameConfig::interface_viewdrawbackgroundmode == VIEW_BACKGROUND_TRANSPARENT) {}
}