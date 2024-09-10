	ContainsPointVisitor(const geom::Polygon &rect)
		:
		rectEnv(*(rect.getEnvelopeInternal())),
		containsPointVar(false),
		rectSeq(*(rect.getExteriorRing()->getCoordinatesRO()))
		{}