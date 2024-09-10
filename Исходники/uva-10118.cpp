constexpr base_t POW(base_t base, expo_t expo)
{
    return (expo != 0 ) ? base * POW(base, expo -1) : 1;
}