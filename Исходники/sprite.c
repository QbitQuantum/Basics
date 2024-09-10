static void SetSpriteTimer(struct SPRITE *s, float secs, void (*f)(struct SPRITE *))
{
    /* set timer for this sprite */
    s->timeLeft = floorf(secs * 60);
    s->timerFunc = f;
}