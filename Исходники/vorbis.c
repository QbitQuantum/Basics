static float
float32_unpack(BitstreamReader *bs) {
    int mantissa = bs->read(bs, 21);
    int exponent = bs->read(bs, 10);
    int sign = bs->read(bs, 1);

    return ldexpf(sign ? -mantissa : mantissa,
                  exponent - 788);
}