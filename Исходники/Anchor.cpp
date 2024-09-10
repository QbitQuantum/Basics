void Anchor::draw(const Cairo::RefPtr<Cairo::Context>& context) const
{
        context->save();
        context->move_to(mX,mY);
        context->set_source_rgb(0., 1., 0.);
        context->rectangle(mX, mY, ANCHOR_WIDTH, ANCHOR_HEIGHT);
        context->fill();
        context->restore();
}