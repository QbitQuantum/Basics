/* Silvio Moioli: updated to use Unicode */
sbevent_t *
sbevent_init(void)
{
    sbevent_t *evt;

    evt = ckd_calloc(1, sizeof(*evt));
    evt->evt = CreateEventW(NULL, FALSE, FALSE, NULL);
    if (evt->evt == NULL) {
        ckd_free(evt);
        return NULL;
    }
    return evt;
}