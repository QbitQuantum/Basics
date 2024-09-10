/*
 * Handle backward-word
 */
static void rl_key_backward_word (void)
{
    if (rl_ucspos > 0)
        rl_key_left ();
    if (rl_ucspos > 0 && !iswalnum (rl_ucs_at (&rl_ucs, rl_ucspos)))
        while (rl_ucspos > 0 && !iswalnum (rl_ucs_at (&rl_ucs, rl_ucspos)))
            rl_key_left ();
    while (rl_ucspos > 0 && iswalnum (rl_ucs_at (&rl_ucs, rl_ucspos)))
        rl_key_left ();
    if (!iswalnum (rl_ucs_at (&rl_ucs, rl_ucspos)))
        rl_key_right ();
}