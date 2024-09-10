void sample_hmm (
    dlib::rand& rnd,
    const matrix<double>& transition_probabilities,
    const matrix<double>& emission_probabilities,
    unsigned long previous_label,
    unsigned long& next_label,
    unsigned long& next_sample
)
/*!
    requires
        - previous_label < transition_probabilities.nr()
        - transition_probabilities.nr() == transition_probabilities.nc()
        - transition_probabilities.nr() == emission_probabilities.nr()
        - The rows of transition_probabilities and emission_probabilities must sum to 1.
          (i.e. sum_cols(transition_probabilities) and sum_cols(emission_probabilities)
          must evaluate to vectors of all 1s.)
    ensures
        - This function randomly samples the HMM defined by transition_probabilities
          and emission_probabilities assuming that the previous hidden state
          was previous_label. 
        - The HMM is defined by:
            - P(next_label |previous_label) == transition_probabilities(previous_label, next_label)
            - P(next_sample|next_label)     == emission_probabilities  (next_label,     next_sample)
        - #next_label == the sampled value of the hidden state
        - #next_sample == the sampled value of the observed state
!*/
{
    // sample next_label
    double p = rnd.get_random_double();
    for (long c = 0; p >= 0 && c < transition_probabilities.nc(); ++c)
    {
        next_label = c;
        p -= transition_probabilities(previous_label, c);
    }

    // now sample next_sample
    p = rnd.get_random_double();
    for (long c = 0; p >= 0 && c < emission_probabilities.nc(); ++c)
    {
        next_sample = c;
        p -= emission_probabilities(next_label, c);
    }
}