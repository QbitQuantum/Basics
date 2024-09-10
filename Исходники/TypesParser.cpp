SWFMatrix
readSWFMatrix(SWFStream& in)
{
    in.align();

    in.ensureBits(1);
    const bool has_scale = in.read_bit(); 

    std::int32_t sx = 65536;
    std::int32_t sy = 65536;
    if (has_scale) {
        in.ensureBits(5);
        const std::uint8_t scale_nbits = in.read_uint(5);
        if (scale_nbits) {
            in.ensureBits(scale_nbits * 2);
            sx = in.read_sint(scale_nbits);
            sy = in.read_sint(scale_nbits);
        }
    }

    in.ensureBits(1);
    const bool has_rotate = in.read_bit();
    std::int32_t shx = 0;
    std::int32_t shy = 0;
    if (has_rotate) {
        in.ensureBits(5);
        unsigned int rotate_nbits = in.read_uint(5);
        if (rotate_nbits) {
            in.ensureBits(rotate_nbits * 2);
            shx = in.read_sint(rotate_nbits);
            shy = in.read_sint(rotate_nbits);
        }
    }

    in.ensureBits(5);
    const std::uint8_t translate_nbits = in.read_uint(5);
    std::int32_t tx = 0;
    std::int32_t ty = 0;
    if (translate_nbits) {
        in.ensureBits(translate_nbits * 2);
        tx = in.read_sint(translate_nbits);
        ty = in.read_sint(translate_nbits);
    }
    return SWFMatrix(sx, shx, shy, sy, tx, ty);
}