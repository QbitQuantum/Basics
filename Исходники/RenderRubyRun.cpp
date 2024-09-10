RenderRubyBase* RenderRubyRun::createRubyBase() const
{
    RenderRubyBase* rb = new (renderArena()) RenderRubyBase(document() /* anonymous */);
    RefPtr<RenderStyle> newStyle = RenderStyle::createAnonymousStyleWithDisplay(style(), BLOCK);
    newStyle->setTextAlign(CENTER); // FIXME: use WEBKIT_CENTER?
    rb->setStyle(newStyle.release());
    return rb;
}