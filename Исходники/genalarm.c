int main(void)
{
    int i;
    FILE *fp;

    generate_alarm_sound();

    for (i = 0; i < alarm_len; i++) {
	fputc(alarm_sound[i] & 0xFF, stdout);
	fputc((alarm_sound[i] >> 8) & 0xFF, stdout);
    }

    /*
     * Diagnostic output as a .wav.
     */
    if ((fp = fopen("build/almsnd.wav", "wb")) != NULL) {
	char header[256], *p = header;
	int j;

#define PUT(n, value) do { \
    int i; \
    for (i=0; i<(n); i++) { \
	*p++ = (((unsigned)value) >> (i*8)) & 0xFF; \
    } \
} while (0)
#define PUTS(s) do { \
    int i; \
    for (i=0; i<sizeof(s)-1; i++) { \
	*p++ = s[i]; \
    } \
} while (0)

	PUTS("RIFF");
	PUT(4, alarm_len * 2 + 36);
	PUTS("WAVE");
	PUTS("fmt ");
	PUT(4, 0x10);
	PUT(2, 1);		       /* PCM */
	PUT(2, 1);		       /* channels */
	PUT(4, alarm_freq);	       /* sample rate */
	PUT(4, alarm_freq * 2);	       /* data rate */
	PUT(2, 2);		       /* bytes per frame */
	PUT(2, 16);		       /* bits per sample */
	PUTS("data");
	PUT(4, alarm_len * 2);
	fwrite(header, 1, p - header, fp);

	for (j = 0; j < alarm_len; j++) {
	    p = header;
	    PUT(2, alarm_sound[j]);
	    fwrite(header, 1, p - header, fp);
	}

	fclose(fp);
    }

    return 0;
}