void addSub(Context_t  *context, char * text, unsigned long long int pts, unsigned long int milliDuration) {
    int count = 20;
    
    subtitle_printf(50, "index %d\n", writePointer);

    if(context && context->playback && !context->playback->isPlaying)
    {
        subtitle_err("1. aborting ->no playback\n");
        return;
    }
    
    if (text == NULL)
    {
        subtitle_err("null pointer passed\n");
        return;
    }

    if (pts == 0)
    {
        subtitle_err("pts 0\n");
        return;
    }

    if (milliDuration == 0)
    {
        subtitle_err("duration 0\n");
        return;
    }
    
    while (subPuffer[writePointer].text != NULL) {
        //List is full, wait till we got some free space

        if(context && context->playback && !context->playback->isPlaying)
        {
            subtitle_err("2. aborting ->no playback\n");
            return;
        }

/* konfetti: we dont want to block forever here. if no buffer
 * is available we start ring from the beginning and loose some stuff
 * which is acceptable!
 */
        subtitle_printf(10, "waiting on free buffer %d - %d (%d) ...\n", writePointer, readPointer, count);
        usleep(10000);
        count--;
        
        if (count == 0)
        {
            subtitle_err("abort waiting on buffer...\n");
            break;
        }
    }
    
    subtitle_printf(20, "from mkv: %s pts:%lld milliDuration:%lud\n",text,pts,milliDuration);

    getMutex(__LINE__);

    if (count == 0)
    {
        int i;
        subtitle_err("freeing not delivered data\n");
        
        //Reset all
        readPointer = 0;
        writePointer = 0;

        for (i = 0; i < PUFFERSIZE; i++) {
            if (subPuffer[i].text != NULL)
               free(subPuffer[i].text);
            subPuffer[i].text          = NULL;
            subPuffer[i].pts           = 0;
            subPuffer[i].milliDuration = 0;
        }
    }

    subPuffer[writePointer].text = strdup(text);
    subPuffer[writePointer].pts = pts;
    subPuffer[writePointer].milliDuration = milliDuration;

    writePointer++;
    
    if (writePointer == PUFFERSIZE)
        writePointer = 0;

    if (writePointer == readPointer)
    {
        /* this should not happen, and means that there is nor reader or
         * the reader has performance probs ;)
         * the recovery is done at startup of this function - but next time
         */
        subtitle_err("ups something went wrong. no more readers? \n");
    }

    releaseMutex(__LINE__);

    subtitle_printf(10, "<\n");
}