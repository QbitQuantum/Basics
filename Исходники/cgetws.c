wchar_t * __cdecl _cgetws (
        wchar_t *string)
{
        size_t sizeInWords;
        size_t sizeRead;
        errno_t err;

        _VALIDATE_CLEAR_OSSERR_RETURN((string != NULL), EINVAL, NULL);

        sizeInWords = (size_t)string[0];

        err = _cgetws_s(string + 2, sizeInWords, &sizeRead);

        if(err != 0)
        {
            return NULL;
        }

       string[1] = (wchar_t)sizeRead;

       return string + 2;
}