void IAGSEngine::DrawText (int32 x, int32 y, int32 font, int32 color, char *text) 
{
    Common::Graphics *g = GetVirtualScreenGraphics();
    g->SetTextColor(color);
    draw_and_invalidate_text(g, x, y, font, text);
}