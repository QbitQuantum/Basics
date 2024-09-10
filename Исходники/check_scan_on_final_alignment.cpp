/// \brief TODOCUMENT
///
/// Things for investigation:
///  * raw/final score from alignment
///  * expected raw/final score
///  * top categorised reasons by raw score
///  * repeat for varying scan_stride (can just be called by nmnf fn)
alignment_scan_comparison check_scan_on_final_alignment::do_check(const alignment     &arg_alignment,  ///< TODOCUMENT
                                                                  const protein       &arg_protein_a,  ///< TODOCUMENT
                                                                  const protein       &arg_protein_b,  ///< TODOCUMENT
                                                                  const quad_criteria &arg_criteria,   ///< TODOCUMENT
                                                                  const scan_stride   &arg_scan_stride ///< TODOCUMENT
                                                                  ) const {
	const auto aln_range = irange( 0_z, arg_alignment.length() );
	cerr << "SHOULD THE RANGE BE 7.0 RATHER THAN SQRT(40.0)????\n";
	return accumulate(
		cross( aln_range, aln_range ),
		alignment_scan_comparison{},
		[&] (alignment_scan_comparison x, const size_size_tpl &y) {
			const size_t aln_from_ctr   = get<0>( y );
			const size_t aln_to_ctr     = get<1>( y );
			const bool   from_alns_both = has_both_positions_of_index( arg_alignment, aln_from_ctr );
			const bool   to_alns_both   = has_both_positions_of_index( arg_alignment, aln_to_ctr   );

			if ( from_alns_both && to_alns_both ) {

				const auto a_from     = get_a_position_of_index( arg_alignment, aln_from_ctr );
				const auto b_from     = get_b_position_of_index( arg_alignment, aln_from_ctr );
				const auto a_to       = get_a_position_of_index( arg_alignment, aln_to_ctr   );
				const auto b_to       = get_b_position_of_index( arg_alignment, aln_to_ctr   );
				const bool a_included = difference( a_from, a_to ) > NUM_EXCLUDED_ON_SIDES;
				const bool b_included = difference( b_from, b_to ) > NUM_EXCLUDED_ON_SIDES;

				if ( a_included && b_included ) {
					const auto the_distance = distance_between_points(
						view_vector_of_residue_pair(
							arg_protein_a.get_residue_ref_of_index( a_from ),
							arg_protein_a.get_residue_ref_of_index( a_to   )
						),
						view_vector_of_residue_pair(
							arg_protein_b.get_residue_ref_of_index( b_from ),
							arg_protein_b.get_residue_ref_of_index( b_to   )
						)
					);
//					const auto score       = ( the_distance >= 7.0 ) ? 0.0 : ( 1.0 - the_distance / 7.0 );
					const auto score       = ( the_distance >= sqrt( 40.0 ) ) ? 0.0 : ( 1.0 - the_distance / 7.0 );
					if ( score > 0.0 ) {
						const auto scan_result = quad_and_rep_criteria_result_of(
							arg_protein_a,
							arg_protein_b,
							arg_criteria,
							arg_scan_stride,
							numeric_cast<index_type>( a_from ),
							numeric_cast<index_type>( a_to   ),
							numeric_cast<index_type>( b_from ),
							numeric_cast<index_type>( b_to   )
						);
						x += make_pair( scan_result, score );
					}
				}
			}

			return x;
		}
	);
}