const void *StatefulMemset_r(MemcpyState *state, const uint8_t val,
                             uint64_t len)
{
    if (state->overrun)
        return NULL;
    if (len > state->remaining_len) {
        state->overrun = 1;
        return NULL;
    }
    Memset(state->remaining_buf, val, len);
    state->remaining_buf += len;
    state->remaining_len -= len;
    return state; /* Must return something non-NULL. */
}