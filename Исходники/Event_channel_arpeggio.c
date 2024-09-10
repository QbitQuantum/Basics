bool Event_channel_arpeggio_on_process(
        Channel* ch,
        Device_states* dstates,
        const Value* value)
{
    assert(ch != NULL);
    assert(dstates != NULL);
    (void)dstates;
    (void)value;

    for (int i = 0; i < KQT_GENERATORS_MAX; ++i)
    {
        Event_check_voice(ch, i);
        Voice* voice = ch->fg[i];
        Voice_state* vs = voice->state;
        //pitch_t orig_pitch = -1;
        if (vs->arpeggio || voice->gen->ins_params->pitch_locks[i].enabled)
            continue;

#if 0
        if (voice->gen->ins_params->scale != NULL &&
                *voice->gen->ins_params->scale != NULL &&
                **voice->gen->ins_params->scale != NULL)
        {
            orig_pitch = Scale_get_pitch_from_cents(
                         **voice->gen->ins_params->scale, vs->orig_cents);
        }
        else
        {
            orig_pitch = exp2(vs->orig_cents / 1200) * 440;
        }
        if (orig_pitch <= 0)
        {
            vs->arpeggio = false;
            continue;
        }
#endif
        if (isnan(ch->arpeggio_ref))
            ch->arpeggio_ref = vs->orig_cents;

        if (isnan(ch->arpeggio_tones[0]))
            ch->arpeggio_tones[0] = ch->arpeggio_ref;

        vs->arpeggio_ref = ch->arpeggio_ref;
        memcpy(vs->arpeggio_tones, ch->arpeggio_tones,
                KQT_ARPEGGIO_NOTES_MAX * sizeof(double));
#if 0
        int last_nonzero = -1;
        for (int k = 0; k < KQT_ARPEGGIO_NOTES_MAX; ++k)
        {
            if (data[k + 1].field.double_type != 0)
            {
                last_nonzero = k;
            }
            pitch_t new_pitch = -1;
            if (voice->gen->ins_params->scale != NULL &&
                    *voice->gen->ins_params->scale != NULL &&
                    **voice->gen->ins_params->scale != NULL)
            {
                Scale* scale = **voice->gen->ins_params->scale;
                new_pitch = Scale_get_pitch_from_cents(scale,
                            vs->orig_cents + data[k + 1].field.double_type);
            }
            else
            {
                new_pitch = vs->orig_cents + data[k + 1].field.double_type;
            }
            if (new_pitch <= 0)
            {
                last_nonzero = -1;
                break;
            }
            else
            {
                vs->arpeggio_factors[k] = new_pitch / orig_pitch;
            }
        }
        if (last_nonzero == -1)
        {
            vs->arpeggio = false;
            continue;
        }
        else if (last_nonzero < KQT_ARPEGGIO_NOTES_MAX - 1)
        {
            vs->arpeggio_factors[last_nonzero + 1] = -1;
        }
#endif
        const double unit_len = Tstamp_toframes(
                Tstamp_set(TSTAMP_AUTO, 1, 0),
                *ch->tempo,
                *ch->freq);
        vs->arpeggio_length = unit_len / ch->arpeggio_speed;
        vs->arpeggio_frames = 0;
        vs->arpeggio_note = 0;
        vs->arpeggio = true;
    }

    return true;
}