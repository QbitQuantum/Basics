//=============================================================================
void Rectangle2::originIsCenter_()
{
    Vector2F dw = width_;
    Vector2F dh = up_();

    dw.multiply(-0.5);
    dh.multiply(-0.5);

    origin_.add(dw);
    origin_.add(dh);
}