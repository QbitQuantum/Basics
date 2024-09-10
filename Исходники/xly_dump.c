static void
dump_noteval(note_p note, voice_p voice)
{
    /* Find out the pitch */
    int val = note->value + clef_current->offset;
    int octave;
    int key;
    int accidental;

    if (val < 0) {
        octave = - ((- val + OCTAVE_DIATON - 1) / OCTAVE_DIATON);
        val = (val - octave * OCTAVE_DIATON) % OCTAVE_DIATON;
    } else {
        octave = val / OCTAVE_DIATON;
        val = val % OCTAVE_DIATON;
    }

    accidental = measure_accidental[note->value];
    if (note->tie_end != NO_ID) {
        tie_p tie = &ties[note->tie_end];
        accidental = tie->notes[0]->accidental;
    }

    key = defaultKey(val, voice);
    VPRINTF(" dump note, keyed value = %d, accidental %d, measure accidental %d, key ofdset %d\n",
            val, note->accidental, measure_accidental[note->value],
            defaultKey(val, voice));
    fprintf(lily_out, " %s", keyName(val));
    if (note->accidental != 0) {
        dumpAccidental(note->accidental);
        measure_accidental[note->value] = note->accidental;
    } else if (accidental != 0) {
        /* Require the actual accidental for cross-bar ties */
        note->accidental = accidental;
        dumpAccidental(accidental);
    } else {
        switch (key) {
        case 0: break;
        case 1: fprintf(lily_out, "is"); break;
        case 2: fprintf(lily_out, "isis"); break;
        case -1: fprintf(lily_out, "es"); break;
        case -2: fprintf(lily_out, "eses"); break;
        }
    }

    while (octave > 0) {
        fprintf(lily_out, "'");
        octave--;
    }
    while (octave < 0) {
        fprintf(lily_out, ",");
        octave++;
    }
}