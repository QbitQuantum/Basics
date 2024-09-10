/// \brief TODOCUMENT
alignment_split_list cath::align::detail::get_preexisting_alignment_splits(const alignment &arg_alignment ///< TODOCUMENT
                                                                           ) {
	const size_t num_entries = arg_alignment.num_entries();
	const size_t aln_length  = arg_alignment.length();
	alignment_split_list new_alignment_splits;
	for (size_t aln_index = 0; aln_index < aln_length; ++aln_index) {
		const size_vec present_positions = entries_present_at_index( arg_alignment, aln_index );
		const alignment_split multi_split = make_alignment_split( present_positions, num_entries );
		if ( is_valid_split( multi_split) ) {
			new_alignment_splits.insert( get_least_version( multi_split ) );
		}
	}
	return new_alignment_splits;
}