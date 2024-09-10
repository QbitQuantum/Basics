void mix()
{
    // omp-ing this yields a 10% speed increase; not much, but it's something
    g_wav.resize(g_maxChannelLen);
    #pragma omp parallel for
    for(int i = 0; i < g_maxChannelLen; ++i) {
        float sum(0.f);
        for(size_t j = 0; j < JAKMUSE_NUMCHANNELS; ++j) {
            if(g_channels[j].size() <= i) continue;
            sum += g_channels[j][i];
        }
        g_wav[i] = ((short)(tanhf(sum) * 0x7FFF));
    }
}