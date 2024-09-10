/*--------------------------------------------------------------------------*/
static int playsound(wchar_t *wcFilename)
{
#ifdef _MSC_VER
    if (wcFilename)
    {
        /* Stop Playing*/
        PlaySoundW(NULL, NULL, SND_PURGE);
        PlaySoundW(wcFilename, NULL, SND_ASYNC | SND_FILENAME);
    }
#endif
    return 0;
}