void WaveInData(WPARAM wParam, LPARAM lParam)
{
    // Create buffers for processing the audio data

    static double buffer[SAMPLES];
    static complex x[STEP];
    static double xa[RANGE];

    static double K = 2.0 * M_PI / (double)SAMPLE_RATE;

    // Initialise data structs

    if (spectrum.data == NULL)
    {
	spectrum.data = xa;
	spectrum.length = RANGE;
    }

    // Copy the input data

    memmove(buffer, buffer + STEP, (SAMPLES - STEP) * sizeof(double));

    short *data = (short *)((WAVEHDR *)lParam)->lpData;

    for (int i = 0; i < STEP; i++)
	buffer[SAMPLES - STEP + i] = (double)data[i];

    // Give the buffer back

    waveInAddBuffer(audio.hwi, (WAVEHDR *)lParam, sizeof(WAVEHDR));

    // Maximum data value

    static double dmax;

    if (dmax < 4096.0)
	dmax = 4096.0;

    // Calculate normalising value

    double norm = dmax;
    dmax = 0.0;

    // Copy data to FFT input arrays

    for (int i = 0; i < STEP; i++)
    {
	// Find the magnitude

	if (dmax < fabs(buffer[i]))
	    dmax = fabs(buffer[i]);

	// Calculate the window

	double window =
	    0.5 - 0.5 * cos(2.0 * M_PI *
			    i / STEP);

	// Normalise and window the input data

	x[i].r = (double)buffer[i] / norm * window;
    }

    // do FFT

    fftr(x, STEP);

    // Process FFT output

    for (int i = 1; i < RANGE; i++)
    {
	double real = x[i].r;
	double imag = x[i].i;

	xa[i] = hypot(real, imag);
    }

    // Do cross correlation

    double imag = 0.0;
    double real = 0.0;

    for (int i = 0; i < SAMPLES; i++)
    {
	double window =
	    (0.5 - 0.5 * cos(2.0 * M_PI * i / SAMPLES));

	imag += (buffer[i] / 32768.0) * window * sin(i * display.f * K);

	real += (buffer[i] / 32768.0) * window * cos(i * display.f * K);
    }

    double level = hypot(real, imag);

    level = level / (SAMPLES / (4.0 * sqrt(2.0)));

    meter.l = level / pow(10.0, 0.15);

    double dB = log10(level) * 20.0;

    if (dB < -80.0)
	dB = -80.0;

    static long timer;

    // Update display

    if ((timer % 4) == 0)
	InvalidateRgn(spectrum.hwnd, NULL, TRUE);

    if ((timer % 16) == 0)
    {
	    display.l = dB;
	    InvalidateRgn(display.hwnd, NULL, TRUE);
    }

    timer++;
}