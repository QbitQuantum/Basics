	// functions
		/// \brief Returns the offset into the bitset for the specified arc.
		/// \note The ordering of regular, irregular, routethrough, and tied sinks does not matter 
		///		as long as it is consistent.  The only impact comes from the likelihood of access 
		///		for the different types, where more common ones ought to be visited first.
		uint32_t getArcOffset(const Tilewire& inTilewire1, const Tilewire& inTilewire2) const {
			// first make sure the arc is defined
			if(inTilewire1.isUndefined() || inTilewire2.isUndefined()) 
				throw InvalidArcException(Arc(inTilewire1, inTilewire2));
			// look up the relevant tile and wire indexes
			TileIndex tile1 = inTilewire1.getTileIndex();
			WireIndex wire1 = inTilewire1.getWireIndex();
			WireIndex wire2 = inTilewire2.getWireIndex();
			// determine the tile type
			const TileInfo& tileInfo = mTiles.getTileInfo(tile1);
			TileTypeIndex type = tileInfo.getTypeIndex();
			// next get the wire's base arc offset
			const WireInfo& wireInfo = mTiles.getWireInfo(type, wire1);
			uint32_t offset = wireInfo.getArcOffset();
			// look for a regular sink
			const WireArray& sinks = wireInfo.getSinks();
			for(WireIndex i; i < sinks.getSize(); i++) {
				if(sinks[i] == wire2) return offset;
				offset++;
			}
			// look for an irregular sink
			const WireArray& irregularSinks = wireInfo.getIrregularSinks();
			for(WireIndex i; i < irregularSinks.getSize(); i++) {
				if(irregularSinks[i] == wire2) return offset;
				offset++;
			}
			// look for a routethrough sink
			const WireArray& routethroughSinks = wireInfo.getRoutethroughSinks();
			for(WireIndex i; i < routethroughSinks.getSize(); i++) {
				if(routethroughSinks[i] == wire2) return offset;
				offset++;
			}
			// look for a tied sink
			const WireArray& tiedSinks = wireInfo.getTiedSinks();
			for(WireIndex i; i < tiedSinks.getSize(); i++) {
				if(tiedSinks[i] == wire2) return offset;
				offset++;
			}
			// if we didn't find the sink in the regular or irregular arcs, the call failed
			/// \todo Throw a meaningful exception.
			throw InvalidArcException(Arc(inTilewire1, inTilewire2));
		}