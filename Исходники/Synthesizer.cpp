std::vector<float> Synthesizer::generate_frame()
{
    // shift the signal left to get space for the new signal
    sig = sig.shift(R);

    for(int i = 0; i < R; i++)
    {
        sample_idx++;

        if(update_params() >= 0 || finished)
        {
            finished = true;
            break;
        }

        fpoint in = samples[sample_idx - last_phoneme_sample_idx];

        // append the signal at the end
        sig[L - R + i] = in;
    }

    // apply analysis window
    std::valarray<complex> seg = sig * window, tmp(L);

    fft(seg);

    auto env = spectral_envelope(seg);
    //for(auto a : env) std::cout << std::fixed << a << ",";
    //std::cout << "\n\n";

    const fpoint expect = 2 * M_PI / Ov;

    // frequency between two bins
    const fpoint bin_freq = fpoint(Fs) / L;

    std::valarray<fpoint> tmp_mag(L / 2 + 1);
    std::valarray<fpoint> tmp_frq(L / 2 + 1);

    for(unsigned i = 0; i <= L / 2; i++)
    {
        // compute magnitude and phase
        fpoint magn = abs(seg[i]) * 2;
        fpoint phas = arg(seg[i]);

        // compute phase difference
        fpoint pdiff = phas - last_phase[i];
        last_phase[i] = phas;

        // subtract expected phase difference
        pdiff -= i * expect;

        // map delta phase into +/- Pi interval
        pdiff -= 2 * M_PI * floor(pdiff / (2 * M_PI) + 0.5);

        // get deviation from bin frequency from the +/- Pi interval
        fpoint fdev = Ov * pdiff / (2 * M_PI);

        // compute the k-th partials' true frequency
        fpoint true_freq = i * bin_freq + fdev * bin_freq;

        // store magnitude and true frequency in analysis arrays
        tmp_mag[i] = magn;
        tmp_frq[i] = true_freq;
    }

    // copy buffers
    std::valarray<fpoint> seg_mag(L / 2 + 1);
    std::valarray<fpoint> seg_frq(L / 2 + 1);

    // pitch shifting
    fpoint pitch_shift = 1.5;
    for (unsigned i = 0; i <= L / 2; i++)
    {
        unsigned index = i * pitch_shift;
        if (index <= L / 2)
        {
            seg_mag[index] += tmp_mag[i];// / env[i];
            seg_frq[index] = tmp_frq[i] * pitch_shift;
        }
    }

    // synthesis
    for (unsigned i = 0; i <= L / 2; i++)
    {
        // get magnitude and true frequency from synthesis arrays
        fpoint mag = seg_mag[i];
        fpoint frq = seg_frq[i];

        // subtract bin mid frequency
        frq -= i * bin_freq;

        // get bin deviation from freq deviation
        frq /= bin_freq;

        // take osamp into account
        frq = 2 * M_PI * frq / Ov;

        // add the overlap phase advance back in
        frq += i * expect;

        // accumulate delta phase to get bin phase
        sum_phase[i] += frq;
        fpoint phase = sum_phase[i];

        // get real and imag part
        seg[i] = std::polar(mag, phase);
        seg[L - i - 1] = 0;
    }

    ifft(seg);

    ova = ova.shift(R) + seg * window;

    std::vector<float> out(R, 0);

    for(unsigned i = 0; i < R; i++)
    {
        out[i] = (float)clamp(-1, 1, ova[i].real());
    }

    return out;
}