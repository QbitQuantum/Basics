void extern
adx_test (void)
{
    c = _addcarryx_u32 (c, x, y, sum);
    c = _addcarry_u32 (c, x, y, sum);
    c = _subborrow_u32 (c, x, y, sum);
}