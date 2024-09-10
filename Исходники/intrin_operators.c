//note: эти операции сдвигают слова по 64 бита
KTYPE inline lsh(const KTYPE &a, const int &b)
{
        KTYPE result;
        result = _mm_slli_epi64(a, b);
        return result;
}