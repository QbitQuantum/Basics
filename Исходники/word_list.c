/**
 * Porównuje dwa stringi wchar_t zgodnie z zadanymi locale.
 * @return true wtw. argumenty są uporządkowane.
 * @param [in] l Pierwsza wartość.
 * @param [in] r Druga wartość.
 */
static
bool are_ordered(const wchar_t * const l, const wchar_t * const r)
{
    return wcscoll(l, r) <= 0;
}