static ALvoid ALautowahState_process(ALautowahState *state, ALuint SamplesToDo, const ALfloat *SamplesIn, ALfloat (*SamplesOut)[BUFFERSIZE])
{
    ALuint it, kt;
    ALuint base;

    for(base = 0;base < SamplesToDo;)
    {
        ALfloat temps[64];
        ALuint td = minu(SamplesToDo-base, 64);
        ALfloat gain = state->GainCtrl;

        for(it = 0;it < td;it++)
        {
            ALfloat smp = SamplesIn[it+base];
            ALfloat alpha, w0;
            ALfloat amplitude;
            ALfloat cutoff;

            /* Similar to compressor, we get the current amplitude of the
             * incoming signal, and attack or release to reach it. */
            amplitude = fabsf(smp);
            if(amplitude > gain)
                gain = minf(gain+state->AttackRate, amplitude);
            else if(amplitude < gain)
                gain = maxf(gain-state->ReleaseRate, amplitude);
            gain = maxf(gain, GAIN_SILENCE_THRESHOLD);

            /* FIXME: What range does the filter cover? */
            cutoff = lerp(20.0f, 20000.0f, minf(gain/state->PeakGain, 1.0f));

            /* The code below is like calling ALfilterState_setParams with
             * ALfilterType_LowPass. However, instead of passing a bandwidth,
             * we use the resonance property for Q. This also inlines the call.
             */
            w0 = F_2PI * cutoff / state->Frequency;

            /* FIXME: Resonance controls the resonant peak, or Q. How? Not sure
             * that Q = resonance*0.1. */
            alpha = sinf(w0) / (2.0f * state->Resonance*0.1f);
            state->LowPass.b[0] = (1.0f - cosf(w0)) / 2.0f;
            state->LowPass.b[1] =  1.0f - cosf(w0);
            state->LowPass.b[2] = (1.0f - cosf(w0)) / 2.0f;
            state->LowPass.a[0] =  1.0f + alpha;
            state->LowPass.a[1] = -2.0f * cosf(w0);
            state->LowPass.a[2] =  1.0f - alpha;

            state->LowPass.b[2] /= state->LowPass.a[0];
            state->LowPass.b[1] /= state->LowPass.a[0];
            state->LowPass.b[0] /= state->LowPass.a[0];
            state->LowPass.a[2] /= state->LowPass.a[0];
            state->LowPass.a[1] /= state->LowPass.a[0];
            state->LowPass.a[0] /= state->LowPass.a[0];

            temps[it] = ALfilterState_processSingle(&state->LowPass, smp);
        }
        state->GainCtrl = gain;

        for(kt = 0;kt < MaxChannels;kt++)
        {
            ALfloat gain = state->Gain[kt];
            if(!(gain > GAIN_SILENCE_THRESHOLD))
                continue;

            for(it = 0;it < td;it++)
                SamplesOut[kt][base+it] += gain * temps[it];
        }

        base += td;
    }
}