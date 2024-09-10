int
ReplayGainReader_init(replaygain_ReplayGainReader *self,
                      PyObject *args, PyObject *kwds) {
    self->pcmreader = NULL;
    self->channels = array_ia_new();
    self->white_noise = NULL;
    self->audiotools_pcm = NULL;

    double replaygain;
    double peak;

    if (!PyArg_ParseTuple(args, "O&dd",
                          pcmreader_converter, &(self->pcmreader),
                          &(replaygain),
                          &(peak)))
        return -1;

    if ((self->white_noise = open_dither()) == NULL)
        return -1;

    if ((self->audiotools_pcm = open_audiotools_pcm()) == NULL)
        return -1;

    self->multiplier = powl(10.0l, replaygain / 20.0l);
    if (self->multiplier > 1.0l)
        self->multiplier = 1.0l / peak;

    return 0;
}