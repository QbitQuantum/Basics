double get_secs(void) {
    struct timespec ts;
    /* C11. Use this so we can get completely rid of SDL to benchmark the CPU. */
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + (1e-9 * ts.tv_nsec);
    /*return SDL_GetTicks() / 1000.0;*/
}