				void put(libmaus2::dazzler::align::Overlap const & OVL)
				{
					if ( (((novl++) & indexer_type::base_index_mask) == 0) && PEMIG )
						PEMIG->put(libmaus2::dazzler::align::OverlapMeta(OVL), std::pair<uint64_t,uint64_t>(dpos,0));

					dpos += OVL.serialiseWithPath(DOSI,small);
				}