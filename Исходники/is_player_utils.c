//The octave here refers to the 'internal' octave.
int get_freq(int octave, int note_ind)
{
    double curr_ref_freq;
    curr_ref_freq = REF_FREQ + (octave - REF_OCT) * log(2);
    return (int)(exp(curr_ref_freq + note_ind * DLOG) * 1000 + 0.5);
}