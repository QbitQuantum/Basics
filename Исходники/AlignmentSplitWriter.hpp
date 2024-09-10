				void push(libmaus2::dazzler::align::Overlap const & OVL)
				{
					if ( OVL.aread != previd )
					{
						numids += 1;
						
						if ( numids > idsperfile )
						{
							openNextFile();
							numids = 1;	
						}
						
					}

					OVL.serialiseWithPath(*Pstream,small);
					novl += 1;
					previd = OVL.aread;
				}