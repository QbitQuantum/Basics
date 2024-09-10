size_t
seqElements(const af_seq &seq) {
    size_t out = 0;
    if      (seq.step > DBL_MIN)    {
        out = ((seq.end - seq.begin) / abs(seq.step)) + 1;
    }
    else if (seq.step < -DBL_MIN)   {
        out = ((seq.begin - seq.end) / abs(seq.step)) + 1;
    }
    else                            {
        out = numeric_limits<size_t>::max();
    }

    return out;
}