void GraphicalItem::drawRoundedRectangle(
    const Cairo::RefPtr<Cairo::Context>& context,
    int x, int y,
    int width, int height,
    double aspect,
    double corner_radius,
    double red, double green, double blue)
{
    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    context->begin_new_sub_path();
    context->arc(x + width - radius, y + radius, radius,
        -90 * degrees, 0 * degrees);
    context->arc(x + width - radius, y + height - radius,
        radius, 0 * degrees, 90 * degrees);
    context->arc(x + radius, y + height - radius, radius,
        90 * degrees, 180 * degrees);
    context->arc(x + radius, y + radius, radius,
        180 * degrees, 270 * degrees);
    context->close_path();

    context->set_source_rgb(red, green, blue);
    context->fill_preserve();
    setColor(Settings::settings().getForegroundColor(), context);
    context->stroke();
}