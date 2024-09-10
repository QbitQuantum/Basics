void gfx_font_adapter::translate_storage(void* storage, scalar x, scalar y)
{
    gfx_serialized_scanlines_adaptor_bin* sd = (gfx_serialized_scanlines_adaptor_bin*)storage;
    int ox = sd->x();
    int oy = sd->y();
    sd->setX(ox + SCALAR_TO_INT(Ceil(x)));
    sd->setY(oy + SCALAR_TO_INT(Ceil(y)));
}