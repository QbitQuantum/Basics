void DefaultWebThemeEngine::paintMenuList(WebCanvas* canvas, State state, const WebRect& rect) const
{
    cairo_save(canvas);
    setupBorder(canvas, state);
    cairo_rectangle(canvas, rect.x + 0.5, rect.y + 0.5, rect.width, rect.height);
    cairo_stroke_preserve(canvas);

    gradientFill(canvas, rect.y, rect.height, state == StatePressed);

    cairo_move_to(canvas, rect.x + rect.width - MENULIST_ARROW_SIZE - MENULIST_BORDER, rect.y + 1 + rect.height/2 - MENULIST_ARROW_SIZE/2);
    cairo_set_source_rgb(canvas, CHECK_COLOR, CHECK_COLOR, CHECK_COLOR);
    cairo_rel_line_to(canvas, MENULIST_ARROW_SIZE, 0);
    cairo_rel_line_to(canvas, -MENULIST_ARROW_SIZE/2, MENULIST_ARROW_SIZE);
    cairo_close_path(canvas);
    cairo_fill(canvas);

    cairo_restore(canvas);
}