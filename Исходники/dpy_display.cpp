void dpy_display_t::printTime(uint8_t hour, uint8_t min, uint8_t sec)
{
    char lcdString[8+1];
#ifdef DEBUG
    int noChars =
#endif
    sprintf(lcdString, "%02u:%02u:%02u", hour, min, sec);
    ASSERT(noChars < (int)sizeof(lcdString));

    /* Get access to the display, or wait until anybody else has finished respectively. A
       timeout has been defined which should never elapse, but who knows. In case it
       should, we simply deny printing. */
    if(acquireMutex())
    {
        /* "16-sizeof" means to display right aligned. */
        setCursor(/* col */ 16-(sizeof(lcdString)-1), /* row */ 0);
        print(lcdString);

        /* And release the mutex as soon as possible after writing to the underlaying class has
           been done. */
        releaseMutex();
    }
} /* End of dpy_display_t::printTime */