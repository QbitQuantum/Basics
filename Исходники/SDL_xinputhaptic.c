static int
SDL_XINPUT_HapticOpenFromUserIndex(SDL_Haptic *haptic, const Uint8 userid)
{
    char threadName[32];
    XINPUT_VIBRATION vibration = { 0, 0 };  /* stop any current vibration */
    XINPUTSETSTATE(userid, &vibration);

    haptic->supported = SDL_HAPTIC_LEFTRIGHT;

    haptic->neffects = 1;
    haptic->nplaying = 1;

    /* Prepare effects memory. */
    haptic->effects = (struct haptic_effect *)
        SDL_malloc(sizeof(struct haptic_effect) * haptic->neffects);
    if (haptic->effects == NULL) {
        return SDL_OutOfMemory();
    }
    /* Clear the memory */
    SDL_memset(haptic->effects, 0,
        sizeof(struct haptic_effect) * haptic->neffects);

    haptic->hwdata = (struct haptic_hwdata *) SDL_malloc(sizeof(*haptic->hwdata));
    if (haptic->hwdata == NULL) {
        SDL_free(haptic->effects);
        haptic->effects = NULL;
        return SDL_OutOfMemory();
    }
    SDL_memset(haptic->hwdata, 0, sizeof(*haptic->hwdata));

    haptic->hwdata->bXInputHaptic = 1;
    haptic->hwdata->userid = userid;

    haptic->hwdata->mutex = SDL_CreateMutex();
    if (haptic->hwdata->mutex == NULL) {
        SDL_free(haptic->effects);
        SDL_free(haptic->hwdata);
        haptic->effects = NULL;
        return SDL_SetError("Couldn't create XInput haptic mutex");
    }

    SDL_snprintf(threadName, sizeof(threadName), "SDLXInputDev%d", (int)userid);

#if defined(__WIN32__) && !defined(HAVE_LIBC)  /* !!! FIXME: this is nasty. */
#undef SDL_CreateThread
#if SDL_DYNAMIC_API
    haptic->hwdata->thread = SDL_CreateThread_REAL(SDL_RunXInputHaptic, threadName, haptic->hwdata, NULL, NULL);
#else
    haptic->hwdata->thread = SDL_CreateThread(SDL_RunXInputHaptic, threadName, haptic->hwdata, NULL, NULL);
#endif
#else
    haptic->hwdata->thread = SDL_CreateThread(SDL_RunXInputHaptic, threadName, haptic->hwdata);
#endif
    if (haptic->hwdata->thread == NULL) {
        SDL_DestroyMutex(haptic->hwdata->mutex);
        SDL_free(haptic->effects);
        SDL_free(haptic->hwdata);
        haptic->effects = NULL;
        return SDL_SetError("Couldn't create XInput haptic thread");
    }

    return 0;
}