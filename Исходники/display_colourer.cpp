/// \brief TODOCUMENT
///
/// \relates display_colourer
display_colour_spec cath::get_colour_spec(const display_colourer &arg_colourer, ///< TODOCUMENT
                                          const pdb_list         &arg_pdbs,     ///< TODOCUMENT
                                          const str_vec          &arg_names,    ///< TODOCUMENT
                                          const alignment        &arg_alignment ///< TODOCUMENT
                                          ) {
	const alignment::size_type num_entries   = arg_alignment.num_entries();
	const alignment::size_type aln_length    = arg_alignment.length();

	if ( aln_length <= 0 || num_entries <= 0 ) {
		BOOST_THROW_EXCEPTION(invalid_argument_exception("Unable to colour the alignment_context because the alignment is empty"));
	}
	if ( num_entries != arg_pdbs.size()  ) {
		BOOST_THROW_EXCEPTION(invalid_argument_exception("Unable to colour the alignment_context because the number of entries doesn't match the number of PDBs"));
	}
	if ( num_entries != arg_names.size() ) {
		BOOST_THROW_EXCEPTION(invalid_argument_exception("Unable to colour the alignment_context because the number of entries doesn't match the number of names"));
	}
	auto &&result_spec = arg_colourer.get_colour_spec( alignment_context(
		arg_pdbs,
		arg_names,
		arg_alignment
	) );

	return has_score_colour_handler( arg_colourer )
		? adjust_display_colour_spec_copy(
			std::forward< decltype( result_spec ) >( result_spec ),
			get_score_colour_handler( arg_colourer ),
			arg_alignment
		)
		: result_spec;
}