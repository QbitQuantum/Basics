void CookbookEq::computeFilterCoefs()
{
    float tmp = 0.0f;
    float omega, sn, cs, alpha, beta;
    bool zeroCoefs = false; // this is used if the freq is too high

    // do not allow frequencies bigger than samplerate/2
    float freq = _freq;
    if (freq > (static_cast<float>(_sampleRate) / 2.0f - 500.0f))
    {
        freq = static_cast<float>(_sampleRate) / 2.0f - 500.0f;
        zeroCoefs = true;
    }
    freq = std::max(freq, 0.1f);

    const float gain = static_cast<float>(::exp(_gainDb * Log10() / 20.0));

    // do not allow bogus Q
    float q = std::max(_q, 0.0f);

    // most of theese are implementations of
    // the "Cookbook formulae for audio EQ" by Robert Bristow-Johnson
    switch (_type)
    {
    case LoPass1:
        if (!zeroCoefs)
        {
            tmp = static_cast<float>(::exp(-2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate)));
        }
        _c[0] = 1.0f - tmp;
        _c[1] = 0.0f;
        _c[2] = 0.0f;
        _d[1] = tmp;
        _d[2] = 0.0f;
        _order = 1;
        break;
    case HiPass1:
        if (!zeroCoefs)
        {
            tmp = static_cast<float>(::exp(-2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate)));
        }
        _c[0] = (1.0f + tmp) / 2.0f;
        _c[1] = -(1.0f + tmp) / 2.0f;
        _c[2] = 0.0f;
        _d[1] = tmp;
        _d[2] = 0.0f;
        _order = 1;
        break;
    case LoPass2:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin (omega);
            cs = cos (omega);
            alpha = sn / (2.0f * q);
            tmp = 1.0f + alpha;
            _c[0] = (1.0f - cs) / 2.0f / tmp;
            _c[1] = (1.0f - cs) / tmp;
            _c[2] = (1.0f - cs) / 2.0f / tmp;
            _d[1] = -2.0f * cs / tmp * (-1.0f);
            _d[2] = (1.0f - alpha) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = 1.0f;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    case HiPass2:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin (omega);
            cs = cos (omega);
            alpha = sn / (2.0f * q);
            tmp = 1.0f + alpha;
            _c[0] = (1.0f + cs) / 2.0f / tmp;
            _c[1] = -(1.0f + cs) / tmp;
            _c[2] = (1.0f + cs) / 2.0f / tmp;
            _d[1] = -2.0f * cs / tmp * (-1.0f);
            _d[2] = (1.0f - alpha) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = 0.0f;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    case BandPass:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin(omega);
            cs = cos(omega);
            alpha = sn / (2.0f * q);
            tmp = 1.0f + alpha;
            _c[0] = alpha / tmp * sqrt (q + 1.0f);
            _c[1] = 0.0f;
            _c[2] = -alpha / tmp * sqrt (q + 1.0f);
            _d[1] = -2.0f * cs / tmp * (-1.0f);
            _d[2] = (1.0f - alpha) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = 0.0f;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    case Notch:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin(omega);
            cs = cos(omega);
            alpha = sn / (2 * sqrt (q));
            tmp = 1.0f + alpha;
            _c[0] = 1.0f / tmp;
            _c[1] = -2.0f * cs / tmp;
            _c[2] = 1.0f / tmp;
            _d[1] = -2.0f * cs / tmp * (-1.0f);
            _d[2] = (1.0f - alpha) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = 1.0f;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    case Peak:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin(omega);
            cs = cos(omega);
            q *= 3.0;
            alpha = sn / (2 * q);
            tmp = 1 + alpha / gain;
            _c[0] = (1.0f + alpha * gain) / tmp;
            _c[1] = (-2.0f * cs) / tmp;
            _c[2] = (1.0f - alpha * gain) / tmp;
            _d[1] = -2.0f * cs / tmp * (-1.0f);
            _d[2] = (1.0f - alpha / gain) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = 1.0f;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    case LoShelf:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin (omega);
            cs = cos (omega);
            q = sqrt (q);
            alpha = sn / (2 * q);
            beta = sqrt (gain) / q;
            tmp = (gain + 1.0f) + (gain - 1.0f) * cs + beta * sn;
            _c[0] = gain * ((gain + 1.0f) - (gain - 1.0f) * cs + beta * sn) / tmp;
            _c[1] = 2.0f * gain * ((gain - 1.0f) - (gain + 1.0f) * cs) / tmp;
            _c[2] = gain * ((gain + 1.0f) - (gain - 1.0f) * cs - beta * sn) / tmp;
            _d[1] = -2.0f * ((gain - 1.0f) + (gain + 1.0f) * cs) / tmp * (-1.0f);
            _d[2] = ((gain + 1.0f) + (gain - 1.0f) * cs - beta * sn) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = gain;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    case HiShelf:
        if (!zeroCoefs)
        {
            omega = static_cast<float>(2.0 * Pi() * static_cast<double>(freq) / static_cast<double>(_sampleRate));
            sn = sin(omega);
            cs = cos(omega);
            q = sqrt(q);
            alpha = sn / (2.0f * q);
            beta = sqrt (gain) / q;
            tmp = (gain + 1.0f) - (gain - 1.0f) * cs + beta * sn;
            _c[0] = gain * ((gain + 1.0f) + (gain - 1.0f) * cs + beta * sn) / tmp;
            _c[1] = -2.0f * gain * ((gain - 1.0f) + (gain + 1.0f) * cs) / tmp;
            _c[2] = gain * ((gain + 1.0f) + (gain - 1.0f) * cs - beta * sn) / tmp;
            _d[1] = 2.0f * ((gain - 1.0f) - (gain + 1.0f) * cs) / tmp * (-1.0f);
            _d[2] = ((gain + 1.0f) - (gain - 1.0f) * cs - beta * sn) / tmp * (-1.0f);
        }
        else
        {
            _c[0] = 1.0f;
            _c[1] = 0.0f;
            _c[2] = 0.0f;
            _d[1] = 0.0f;
            _d[2] = 0.0f;
        }
        _order = 2;
        break;
    default: // wrong type
        assert(false);
        break;
    }
}