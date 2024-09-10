/*
	If panning or note_to_use != -1, it will be used for all samples,
	instead of the sample-specific values in the instrument file.

	For note_to_use, any value <0 or >127 will be forced to 0.

	For other parameters, 1 means yes, 0 means no, other values are
	undefined.

	TODO: do reverse loops right */
static Instrument *load_instrument(Renderer *song, const char *name, int percussion,
                                   int panning, int note_to_use,
                                   int strip_loop, int strip_envelope,
                                   int strip_tail)
{
    Instrument *ip;
    Sample *sp;
    FileReader *fp;
    GF1PatchHeader header;
    GF1InstrumentData idata;
    GF1LayerData layer_data;
    GF1PatchData patch_data;
    int i, j;
    bool noluck = false;

    if (!name) return 0;

    /* Open patch file */
    if ((fp = pathExpander.openFileReader(name, NULL)) == NULL)
    {
        /* Try with various extensions */
        FString tmp = name;
        tmp += ".pat";
        if ((fp = pathExpander.openFileReader(tmp, NULL)) == NULL)
        {
#ifdef __unix__			// Windows isn't case-sensitive.
            tmp.ToUpper();
            if ((fp = pathExpander.openFileReader(tmp, NULL)) == NULL)
#endif
            {
                noluck = true;
            }
        }
    }

    if (noluck)
    {
        cmsg(CMSG_ERROR, VERB_NORMAL, "Instrument `%s' can't be found.\n", name);
        return 0;
    }

    cmsg(CMSG_INFO, VERB_NOISY, "Loading instrument %s\n", name);

    /* Read some headers and do cursory sanity checks. */

    if (sizeof(header) != fp->Read(&header, sizeof(header)))
    {
failread:
        cmsg(CMSG_ERROR, VERB_NORMAL, "%s: Error reading instrument.\n", name);
        delete fp;
        return 0;
    }
    if (strncmp(header.Header, GF1_HEADER_TEXT, HEADER_SIZE - 4) != 0)
    {
        cmsg(CMSG_ERROR, VERB_NORMAL, "%s: Not an instrument.\n", name);
        delete fp;
        return 0;
    }
    if (strcmp(header.Header + 8, "110") < 0)
    {
        cmsg(CMSG_ERROR, VERB_NORMAL, "%s: Is an old and unsupported patch version.\n", name);
        delete fp;
        return 0;
    }
    if (sizeof(idata) != fp->Read(&idata, sizeof(idata)))
    {
        goto failread;
    }

    header.WaveForms = LittleShort(header.WaveForms);
    header.MasterVolume = LittleShort(header.MasterVolume);
    header.DataSize = LittleLong(header.DataSize);
    idata.Instrument = LittleShort(idata.Instrument);

    if (header.Instruments != 1 && header.Instruments != 0) /* instruments. To some patch makers, 0 means 1 */
    {
        cmsg(CMSG_ERROR, VERB_NORMAL, "Can't handle patches with %d instruments.\n", header.Instruments);
        delete fp;
        return 0;
    }

    if (idata.Layers != 1 && idata.Layers != 0) /* layers. What's a layer? */
    {
        cmsg(CMSG_ERROR, VERB_NORMAL, "Can't handle instruments with %d layers.\n", idata.Layers);
        delete fp;
        return 0;
    }

    if (sizeof(layer_data) != fp->Read(&layer_data, sizeof(layer_data)))
    {
        goto failread;
    }

    if (layer_data.Samples == 0)
    {
        cmsg(CMSG_ERROR, VERB_NORMAL, "Instrument has 0 samples.\n");
        delete fp;
        return 0;
    }

    ip = new Instrument;
    ip->samples = layer_data.Samples;
    ip->sample = (Sample *)safe_malloc(sizeof(Sample) * layer_data.Samples);
    memset(ip->sample, 0, sizeof(Sample) * layer_data.Samples);
    for (i = 0; i < layer_data.Samples; ++i)
    {
        if (sizeof(patch_data) != fp->Read(&patch_data, sizeof(patch_data)))
        {
fail:
            cmsg(CMSG_ERROR, VERB_NORMAL, "Error reading sample %d.\n", i);
            delete ip;
            delete fp;
            return 0;
        }

        sp = &(ip->sample[i]);

        sp->data_length = LittleLong(patch_data.WaveSize);
        sp->loop_start = LittleLong(patch_data.StartLoop);
        sp->loop_end = LittleLong(patch_data.EndLoop);
        sp->sample_rate = LittleShort(patch_data.SampleRate);
        sp->low_freq = float(LittleLong(patch_data.LowFrequency));
        sp->high_freq = float(LittleLong(patch_data.HighFrequency)) + 0.9999f;
        sp->root_freq = float(LittleLong(patch_data.RootFrequency));
        sp->high_vel = 127;
        sp->velocity = -1;
        sp->type = INST_GUS;

        // Expand to SF2 range.
        if (panning == -1)
        {
            sp->panning = (patch_data.Balance & 0x0F) * 1000 / 15 - 500;
        }
        else
        {
            sp->panning = (panning & 0x7f) * 1000 / 127 - 500;
        }
        song->compute_pan((sp->panning + 500) / 1000.0, INST_GUS, sp->left_offset, sp->right_offset);

        /* tremolo */
        if (patch_data.TremoloRate == 0 || patch_data.TremoloDepth == 0)
        {
            sp->tremolo_sweep_increment = 0;
            sp->tremolo_phase_increment = 0;
            sp->tremolo_depth = 0;
            cmsg(CMSG_INFO, VERB_DEBUG, " * no tremolo\n");
        }
        else
        {
            sp->tremolo_sweep_increment = convert_tremolo_sweep(song, patch_data.TremoloSweep);
            sp->tremolo_phase_increment = convert_tremolo_rate(song, patch_data.TremoloRate);
            sp->tremolo_depth = patch_data.TremoloDepth;
            cmsg(CMSG_INFO, VERB_DEBUG, " * tremolo: sweep %d, phase %d, depth %d\n",
                 sp->tremolo_sweep_increment, sp->tremolo_phase_increment, sp->tremolo_depth);
        }

        /* vibrato */
        if (patch_data.VibratoRate == 0 || patch_data.VibratoDepth == 0)
        {
            sp->vibrato_sweep_increment = 0;
            sp->vibrato_control_ratio = 0;
            sp->vibrato_depth = 0;
            cmsg(CMSG_INFO, VERB_DEBUG, " * no vibrato\n");
        }
        else
        {
            sp->vibrato_control_ratio = convert_vibrato_rate(song, patch_data.VibratoRate);
            sp->vibrato_sweep_increment = convert_vibrato_sweep(song, patch_data.VibratoSweep, sp->vibrato_control_ratio);
            sp->vibrato_depth = patch_data.VibratoDepth;
            cmsg(CMSG_INFO, VERB_DEBUG, " * vibrato: sweep %d, ctl %d, depth %d\n",
                 sp->vibrato_sweep_increment, sp->vibrato_control_ratio, sp->vibrato_depth);
        }

        sp->modes = patch_data.Modes;

        /* Mark this as a fixed-pitch instrument if such a deed is desired. */
        if (note_to_use != -1)
        {
            sp->scale_note = note_to_use;
            sp->scale_factor = 0;
        }
        else
        {
            sp->scale_note = LittleShort(patch_data.ScaleFrequency);
            sp->scale_factor = LittleShort(patch_data.ScaleFactor);
            if (sp->scale_factor <= 2)
            {
                sp->scale_factor *= 1024;
            }
            else if (sp->scale_factor > 2048)
            {
                sp->scale_factor = 1024;
            }
            if (sp->scale_factor != 1024)
            {
                cmsg(CMSG_INFO, VERB_DEBUG, " * Scale: note %d, factor %d\n",
                     sp->scale_note, sp->scale_factor);
            }
        }

#if 0
        /* seashore.pat in the Midia patch set has no Sustain. I don't
           understand why, and fixing it by adding the Sustain flag to
           all looped patches probably breaks something else. We do it
           anyway. */

        if (sp->modes & PATCH_LOOPEN)
        {
            sp->modes |= PATCH_SUSTAIN;
        }
#endif
        /* [RH] Alas, eawpats has percussion instruments with bad envelopes. :(
         * (See cymchina.pat for one example of this sadness.)
         * Do this logic for instruments without a description, only. Hopefully that
         * catches all the patches that need it without including any extra.
         */
        for (j = 0; j < DESC_SIZE; ++j)
        {
            if (header.Description[j] != 0)
                break;
        }
        /* Strip any loops and envelopes we're permitted to */
        /* [RH] (But PATCH_BACKWARD isn't a loop flag at all!) */
        if ((strip_loop == 1) &&
                (sp->modes & (PATCH_SUSTAIN | PATCH_LOOPEN | PATCH_BIDIR | PATCH_BACKWARD)))
        {
            cmsg(CMSG_INFO, VERB_DEBUG, " - Removing loop and/or sustain\n");
            if (j == DESC_SIZE)
            {
                sp->modes &= ~(PATCH_SUSTAIN | PATCH_LOOPEN | PATCH_BIDIR | PATCH_BACKWARD);
            }
        }

        if (strip_envelope == 1)
        {
            cmsg(CMSG_INFO, VERB_DEBUG, " - Removing envelope\n");
            /* [RH] The envelope isn't really removed, but this is the way the standard
             * Gravis patches get that effect: All rates at maximum, and all offsets at
             * a constant level.
             */
            if (j == DESC_SIZE)
            {
                int k;
                for (k = 1; k < ENVELOPES; ++k)
                {   /* Find highest offset. */
                    if (patch_data.EnvelopeOffset[k] > patch_data.EnvelopeOffset[0])
                    {
                        patch_data.EnvelopeOffset[0] = patch_data.EnvelopeOffset[k];
                    }
                }
                for (k = 0; k < ENVELOPES; ++k)
                {
                    patch_data.EnvelopeRate[k] = 63;
                    patch_data.EnvelopeOffset[k] = patch_data.EnvelopeOffset[0];
                }
            }
        }

        for (j = 0; j < 6; j++)
        {
            sp->envelope.gf1.rate[j] = patch_data.EnvelopeRate[j];
            /* [RH] GF1NEW clamps the offsets to the range [5,251], so we do too. */
            sp->envelope.gf1.offset[j] = clamp<BYTE>(patch_data.EnvelopeOffset[j], 5, 251);
        }

        /* Then read the sample data */
        if (((sp->modes & PATCH_16) && sp->data_length/2 > MAX_SAMPLE_SIZE) ||
                (!(sp->modes & PATCH_16) && sp->data_length > MAX_SAMPLE_SIZE))
        {
            goto fail;
        }
        sp->data = (sample_t *)safe_malloc(sp->data_length);

        if (sp->data_length != fp->Read(sp->data, sp->data_length))
            goto fail;

        convert_sample_data(sp, sp->data);

        /* Reverse reverse loops and pass them off as normal loops */
        if (sp->modes & PATCH_BACKWARD)
        {
            int t;
            /* The GUS apparently plays reverse loops by reversing the
               whole sample. We do the same because the GUS does not SUCK. */

            cmsg(CMSG_WARNING, VERB_NORMAL, "Reverse loop in %s\n", name);
            reverse_data((sample_t *)sp->data, 0, sp->data_length);
            sp->data[sp->data_length] = sp->data[sp->data_length - 1];

            t = sp->loop_start;
            sp->loop_start = sp->data_length - sp->loop_end;
            sp->loop_end = sp->data_length - t;

            sp->modes &= ~PATCH_BACKWARD;
            sp->modes |= PATCH_LOOPEN; /* just in case */
        }

        /* Then fractional samples */
        sp->data_length <<= FRACTION_BITS;
        sp->loop_start <<= FRACTION_BITS;
        sp->loop_end <<= FRACTION_BITS;

        /* Adjust for fractional loop points. */
        sp->loop_start |= (patch_data.Fractions & 0x0F) << (FRACTION_BITS-4);
        sp->loop_end   |= (patch_data.Fractions & 0xF0) << (FRACTION_BITS-4-4);

        /* If this instrument will always be played on the same note,
           and it's not looped, we can resample it now. */
        if (sp->scale_factor == 0 && !(sp->modes & PATCH_LOOPEN))
        {
            pre_resample(song, sp);
        }

        if (strip_tail == 1)
        {
            /* Let's not really, just say we did. */
            cmsg(CMSG_INFO, VERB_DEBUG, " - Stripping tail\n");
            sp->data_length = sp->loop_end;
        }
    }
    delete fp;
    return ip;
}