inline
void compress_and_draw_bitmap_update( const RDPBitmapData & bitmap_data, const Bitmap & bmp
                                    , uint8_t target_bpp, RDPGraphicDevice & gd) {
    StaticOutStream<65535> bmp_stream;
    bmp.compress(target_bpp, bmp_stream);

    RDPBitmapData target_bitmap_data = bitmap_data;

    target_bitmap_data.bits_per_pixel = bmp.bpp();
    target_bitmap_data.flags          = BITMAP_COMPRESSION | NO_BITMAP_COMPRESSION_HDR;
    target_bitmap_data.bitmap_length  = bmp_stream.get_offset();

    gd.draw(target_bitmap_data, bmp_stream.get_data(), bmp_stream.get_offset(), bmp);
}