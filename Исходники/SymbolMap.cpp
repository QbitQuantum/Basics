//need improvement
static u32 hasher(u32 last, u32 value)
{
    return _rotl(last,3) ^ value;
}