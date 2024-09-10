void PlatformScrollbar::paintTrack(GraphicsContext* context, const IntRect& rect, bool start, const IntRect& damageRect) const
{
    IntRect paintRect = hasButtons() ? trackRepaintRect(rect, m_orientation, controlSize()) : rect;
    
    if (!damageRect.intersects(paintRect))
        return;

    context->save();
    context->drawRect(rect);
    context->fillRect(rect, Color::darkGray);
    context->restore();
}