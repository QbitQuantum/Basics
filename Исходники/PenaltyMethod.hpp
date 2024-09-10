	virtual void onIterationStart() {
		// Only need to do this once
		rA = right->A( nextTime() );
		rb = right->b( nextTime() );
		lA =  left->A( nextTime() );
		lb =  left->b( nextTime() );

		// Evaluate the predicate using the previous iterand
		Vector predicate = rA * iterand(0) - rb;

		Vector compare = domain->zero();
		if(direct) {
			compare = lA * iterand(0) - lb;
		}

		// Initialize penalty matrix
		P.setZero();
		P.reserve( IntegerVector::Constant( domain->size(), 1 ) );

		// Initialize other matrix
		Q.setZero();
		Q.reserve( IntegerVector::Constant( domain->size(), 1 ) );

		// Build penalty matrix
		for(Index i = 0; i < domain->size(); ++i) {
			const bool c = Order()(
				(scale * predicate(i)),
				compare(i)
			);
			if(c) { P.insert(i, i) = scale; }
			if(!direct || !c) { Q.insert(i, i) = 1.; }
		}
	}