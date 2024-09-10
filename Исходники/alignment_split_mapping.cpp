/// \brief TODOCUMENT
///
/// \relates alignment_split_mapping
alignment cath::align::detail::build_alignment(const alignment               &arg_inter_mapping_alignment, ///< TODOCUMENT
                                               const alignment_split_mapping &arg_mapping_a,               ///< TODOCUMENT
                                               const alignment_split_mapping &arg_mapping_b                ///< TODOCUMENT
                                               ) {
	check_alignment_is_a_pair( arg_inter_mapping_alignment );

	const size_t inter_mapping_aln_length = arg_inter_mapping_alignment.length();

	const size_vec entries_a     = get_orig_entries( arg_mapping_a );
	const size_vec entries_b     = get_orig_entries( arg_mapping_b );
	const size_t   num_entries_a = arg_mapping_a.num_entries();
	const size_t   num_entries_b = arg_mapping_b.num_entries();

	alignment new_alignment( num_entries_a + num_entries_b );
	new_alignment.reserve( inter_mapping_aln_length );

	for (size_t inter_mapping_index = 0; inter_mapping_index < inter_mapping_aln_length; ++inter_mapping_index) {
		const aln_posn_opt a_position = a_position_of_index( arg_inter_mapping_alignment, inter_mapping_index );
		const aln_posn_opt b_position = b_position_of_index( arg_inter_mapping_alignment, inter_mapping_index );
		if ( ! a_position && ! b_position) {
			BOOST_THROW_EXCEPTION(out_of_range("Inter-mapping alignment has an empty row"));
		}
		const alignment_row aln_row_a = a_position ? get_row_of_alignment( arg_mapping_a, *a_position )
		                                           : make_empty_aln_row( num_entries_a );
		const alignment_row aln_row_b = b_position ? get_row_of_alignment( arg_mapping_b, *b_position )
		                                           : make_empty_aln_row( num_entries_b );

		append_row( new_alignment, weave( aln_row_a, entries_a, aln_row_b, entries_b ) );
	}
	return new_alignment;
}