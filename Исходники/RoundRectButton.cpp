RoundRectTextButton::RoundRectTextButton(int x, int y, int w, int h, double colorH, String text, std::function<void(void)> handler)
    :LambdaButton(Shape(RoundRect(x, y, w, h, 5)), handler),
    rect_m(RoundRect(x, y, w, h, 5)),
    colorH_m(colorH),
    text_m(text),
    width_m(w),
    height_m(h)
{}