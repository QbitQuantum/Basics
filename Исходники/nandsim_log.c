void
nandsim_log(struct nandsim_chip *chip, int level, const char *fmt, ...)
{
	char hdr[TIME_STR_SIZE];
	char tmp[NANDSIM_ENTRY_SIZE];
	struct nandsim_softc *sc;
	struct timeval currtime;
	va_list ap;
	int hdr_len, len, rest;

	if (nandsim_log_output == NANDSIM_OUTPUT_NONE)
		return;

	if (chip == NULL)
		return;

	sc = chip->sc;
	if (!sc->alq && nandsim_log_output == NANDSIM_OUTPUT_FILE)
		return;

	if (level <= nandsim_log_level) {
		microtime(&currtime);
		hdr_len = sprintf(hdr, "%08jd.%08li [chip:%d, ctrl:%d]: ",
		    (intmax_t)currtime.tv_sec, currtime.tv_usec,
		    chip->chip_num, chip->ctrl_num);

		switch(nandsim_log_output) {
		case NANDSIM_OUTPUT_CONSOLE:
			printf("%s", hdr);
			va_start(ap, fmt);
			vprintf(fmt, ap);
			va_end(ap);
			break;
		case NANDSIM_OUTPUT_RAM:
			va_start(ap, fmt);
			len = vsnprintf(tmp, NANDSIM_ENTRY_SIZE - 1, fmt, ap);
			tmp[NANDSIM_ENTRY_SIZE - 1] = 0;
			va_end(ap);

			rest = log_size - sc->log_idx - 1;
			if (rest >= hdr_len) {
				bcopy(hdr, &sc->log_buff[sc->log_idx],
				    hdr_len);
				sc->log_idx += hdr_len;
				sc->log_buff[sc->log_idx] = 0;
			} else {
				bcopy(hdr, &sc->log_buff[sc->log_idx], rest);
				bcopy(&hdr[rest], sc->log_buff,
				    hdr_len - rest);
				sc->log_idx = hdr_len - rest;
				sc->log_buff[sc->log_idx] = 0;
			}

			rest = log_size - sc->log_idx - 1;
			if (rest >= len) {
				bcopy(tmp, &sc->log_buff[sc->log_idx], len);
				sc->log_idx += len;
				sc->log_buff[sc->log_idx] = 0;
			} else {
				bcopy(tmp, &sc->log_buff[sc->log_idx], rest);
				bcopy(&tmp[rest], sc->log_buff, len - rest);
				sc->log_idx = len - rest;
				sc->log_buff[sc->log_idx] = 0;
			}

			break;

		case NANDSIM_OUTPUT_FILE:
			va_start(ap, fmt);
			len = vsnprintf(tmp, NANDSIM_ENTRY_SIZE - 1, fmt, ap);
			tmp[NANDSIM_ENTRY_SIZE - 1] = 0;
			va_end(ap);

			rest = NANDSIM_ENTRY_SIZE - str_index;
			if (rest >= hdr_len) {
				strcat(string, hdr);
				str_index += hdr_len;
			} else {
				strlcat(string, hdr, NANDSIM_ENTRY_SIZE + 1);
				alq_write(sc->alq, (void *) string,
				    ALQ_NOWAIT);
				strcpy(string, &hdr[rest]);
				str_index = hdr_len - rest;
			}
			rest = NANDSIM_ENTRY_SIZE - str_index;
			if (rest >= len) {
				strcat(string, tmp);
				str_index += len;
			} else {
				strlcat(string, tmp, NANDSIM_ENTRY_SIZE + 1);
				alq_write(sc->alq, (void *) string,
				    ALQ_NOWAIT);
				strcpy(string, &tmp[rest]);
				str_index = len - rest;
			}
			break;
		default:
			break;
		}
	}
}