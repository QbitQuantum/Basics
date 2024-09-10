static void spacewar_sound_w(running_machine &machine, UINT8 sound_val, UINT8 bits_changed)
{
    samples_device *samples = machine.device<samples_device>("samples");

    /* Explosion - rising edge */
    if (SOUNDVAL_RISING_EDGE(0x01))
        samples->start(0, (machine.rand() & 1) ? 0 : 6);

    /* Fire sound - rising edge */
    if (SOUNDVAL_RISING_EDGE(0x02))
        samples->start(1, (machine.rand() & 1) ? 1 : 7);

    /* Player 1 thrust - 0=on, 1=off */
    if (SOUNDVAL_FALLING_EDGE(0x04))
        samples->start(3, 3, true);
    if (SOUNDVAL_RISING_EDGE(0x04))
        samples->stop(3);

    /* Player 2 thrust - 0=on, 1-off */
    if (SOUNDVAL_FALLING_EDGE(0x08))
        samples->start(4, 4, true);
    if (SOUNDVAL_RISING_EDGE(0x08))
        samples->stop(4);

    /* Mute - 0=off, 1=on */
    if (SOUNDVAL_FALLING_EDGE(0x10))
        samples->start(2, 2, true);	/* play idle sound */
    if (SOUNDVAL_RISING_EDGE(0x10))
    {
        int i;

        /* turn off all but the idle sound */
        for (i = 0; i < 5; i++)
            if (i != 2)
                samples->stop(i);

        /* Pop when board is shut off */
        samples->start(2, 5);
    }
}