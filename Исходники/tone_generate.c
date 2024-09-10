int tone_gen(tone_gen_state_t *s, int16_t amp[], int max_samples)
{
    int samples;
    int limit;
    float xamp;
    int i;

    if (s->current_section < 0)
        return  0;

    for (samples = 0;  samples < max_samples;  )
    {
        limit = samples + s->duration[s->current_section] - s->current_position;
        if (limit > max_samples)
            limit = max_samples;
        
        s->current_position += (limit - samples);
        if (s->current_section & 1)
        {
            /* A silent section */
            for (  ;  samples < limit;  samples++)
                amp[samples] = 0;
        }
        else
        {
            if (s->tone[0].phase_rate < 0)
            {
                for (  ;  samples < limit;  samples++)
                {
                    /* There must be two, and only two tones */
                    xamp = dds_modf(&s->phase[0], -s->tone[0].phase_rate, s->tone[0].gain, 0)
                         *(1.0f + dds_modf(&s->phase[1], s->tone[1].phase_rate, s->tone[1].gain, 0));
                    amp[samples] = (int16_t) lrintf(xamp);
                }
            }
            else
            {
                for (  ;  samples < limit;  samples++)
                {
                    xamp = 0.0f;
                    for (i = 0;  i < 4;  i++)
                    {
                        if (s->tone[i].phase_rate == 0)
                            break;
                        xamp += dds_modf(&s->phase[i], s->tone[i].phase_rate, s->tone[i].gain, 0);
                    }
                    /* Saturation of the answer is the right thing at this point.
                       However, we are normally generating well controlled tones,
                       that cannot clip. So, the overhead of doing saturation is
                       a waste of valuable time. */
                    amp[samples] = (int16_t) lrintf(xamp);
                }
            }
        }
        if (s->current_position >= s->duration[s->current_section])
        {
            s->current_position = 0;
            if (++s->current_section > 3  ||  s->duration[s->current_section] == 0)
            {
                if (!s->repeat)
                {
                    /* Force a quick exit */
                    s->current_section = -1;
                    break;
                }
                s->current_section = 0;
            }
        }
    }
    return samples;
}