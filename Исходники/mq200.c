void
mq200_init_brightness(struct mq200_softc *sc, int inattach)
{
	int val = -1;

	if (sc->sc_lcd_inited&BRIGHTNESS_INITED)
		return;

	VPRINTF("init_brightness\n");
	if (config_hook_call(CONFIG_HOOK_GET,
	    CONFIG_HOOK_BRIGHTNESS_MAX, &val) != -1) {
		/* we can get real brightness max */
		VPRINTF("init_brightness: real brightness max=%d\n", val);
		sc->sc_max_brightness = val;
		val = -1;
		if (config_hook_call(CONFIG_HOOK_GET,
		    CONFIG_HOOK_BRIGHTNESS, &val) != -1) {
			/* we can get real brightness */
			VPRINTF("init_brightness: real brightness=%d\n", val);
			sc->sc_brightness_save = sc->sc_brightness = val;
		} else {
			sc->sc_brightness_save =
			    sc->sc_brightness = sc->sc_max_brightness;
		}
		sc->sc_lcd_inited |= BRIGHTNESS_INITED;
	} else if (inattach) {
		/*
		   we cannot get real brightness in attach time
		   because brightness device not yet attached.
		   we will retry in !inattach.
		*/
		sc->sc_max_brightness = -1;
		sc->sc_brightness = -1;
		sc->sc_brightness_save = -1;
	} else {
		/* we cannot get real brightness */
		sc->sc_lcd_inited |= BRIGHTNESS_INITED;
	}

	return;
}