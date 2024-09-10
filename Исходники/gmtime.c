/******************************************************************************
 * \name _gmtime32
 * \brief
 * \param ptime Pointer to a variable of type __time32_t containing the time.
 */
struct tm *
_gmtime32(const __time32_t * ptime)
{
    __time64_t time64;

    if (!ptime)
        return NULL;
    time64 = *ptime;
    return _gmtime64(&time64);
}