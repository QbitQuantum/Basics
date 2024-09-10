/**
  * Handle the case of a vector consisting entirely (or almost entirely) of
  * integers. (If the cardinality of string values in a vector is 1 and that
  * unique string value looks a representation of missing data, the vector
  * is treated as if it were entirely integral.) This is the trickiest case
  * since it could be any or none of the 3 statistical classes.
  *
  * Heuristics.
  * 1. card({values}) < MAX_CATEGORY_CARDINALITY
  *     The real question is whether or not categorical statistical tests
  *     are applicable to a given vector.
  *     Categorical methods are rarely applied to data with more than
  *     MAX_CATEGORY_CARDINALITY categories. However, as the sample size
  *     grows MAX_CATEGORY_CARDINALITY *can* grow as well.
  * 2. max(abs({values})) < MAX_VALUE
  *		Although integers can serve as category labels it rarely makes
  *     sense for those integers to have large absolute values.
  *     Zip codes are a confounder of this heuristic.
  * 3. negative integers are almost never involved in categorical data
  *    UNLESS they represent levels symmetric around 0...which further
  *    constrains plausible max(abs({values})).
  *
  * Caveats:
  * 1. The current rationale will miss quantitative variables (of either
  *    integral or floating-point type) that might be usefully treated as
  *    categorical (e.g. a vector of zip codes containing only 3 distinct
  *    values). Or even more extreme: an essentially boolean variable in
  *    which the labels happen to be two large integers.
  *
  * For plausibly categorical cases might be better to consider number
  * of duplicate values (using value_bag instead of value_set).
  *
  */
static int _integer_inference( const struct column *c ) {

	int stat_class = STC_UNK; // ...unless overridden below.

	const int N
		= c->type_vote[ FTY_INTEGER ];
	const double K
		= set_count( & c->value_set );
	const int N_MAG
		= __builtin_popcount( c->integer_magnitudes );

	if( c->excess_values ) {

		// It can only be ordinal or quantitative, and...

		if( c->has_negative_integers ) { // ...it's not ordinal.

			stat_class = STC_QUA;

		} else {

			const int MAX_MAG
				= (int)floorf( log10f( c->extrema[1] ) );

			// Following can't positively id ordinal variables,
			// but it can positively rule them out. I'm sampling
			// the interval [1,N] divided into ranges by base-10
			// magnitude. If data are missing in any range, it's
			// not strictly ordinal...or it's just missing some
			// data. TODO: See comments at top.

			if( ( N_MAG == MAX_MAG )
				&& ( (int)round(c->extrema[0]) == 1 )
				&& ( (int)round(c->extrema[1]) == N ) )
				stat_class = STC_ORD;
			else
				stat_class = STC_QUA;
		}

	} else { // |{value_set}| <= MAX_CATEGORY_CARDINALITY

		// There are few enough values to treat it as a
		// categorical variable, but...

		if( c->has_negative_integers ) {

			// ...require all values to be in (-K,+K) where
			// K == MAX_ABSOLUTE_CATEGORICAL_VALUE
			// e.g. { -2, -1, 0, 1, 2 } with -2 indicating
			// "strongly dislike" and +2 "strongly like"

			stat_class 
				= (-(MAX_ABSOLUTE_CATEGORICAL_VALUE/2) <= c->extrema[0])
					&& (c->extrema[1] <= +(MAX_ABSOLUTE_CATEGORICAL_VALUE/2))
				? STC_CAT
				: STC_QUA;

		} else {

			// The column takes on a "small" set of non-negative
			// integer values. Very likely categorical. The
			// relation between the cardinality of the value set
			// and the sample size is primary determinant now...

			stat_class 
				 = (K <= MAX_CATEGORY_CARDINALITY)
				 	&& (c->extrema[1] <= MAX_ABSOLUTE_CATEGORICAL_VALUE)
				 	&& (K < (N/2))
					// 3rd clause is just a sanity check for very small
					// sample sizes.
				 ? STC_CAT
				 : STC_QUA;

			// Zip codes are a confounding case. They *can* be categorical,
			// but in a large sample they're more likely to be nominative--
			// that is, non-statistical.
		}
	}

	return stat_class;
}