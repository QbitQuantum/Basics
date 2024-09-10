			~HashTable()
			{
				if(Allocator::can_free)
				{
					V *end = &table[0] + (this->mask + 1);

					for(V *slot = &table[0]; slot != end; ++slot)
					{
						V entry = *slot;

						while(T::valid_value(entry))
						{
							V next = T::get_value_next(entry);

							T::free_value(get_allocator(), entry);

							entry = next;
						}
					}
					
					allocator.free(this->table);
				}
			}