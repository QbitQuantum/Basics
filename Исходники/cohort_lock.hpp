				/**
				 * @brief Acquire the lock
				 */
				void lock() {
					node = numa_node();

					/* Take the local lock for your NUMA node */
					local_lock[node].lock();
					/* Checks if this NUMA node already has the node_lock or not */
					if(node != nodelockowner){
						/* Take the node_lock and set that this NUMA node has the node_lock */
						node_lock->lock();
						nodelockowner = node;
						/* Check if this ArgoDSM node has the global lock or not */
						if(!has_global_lock){
							/* Take the global lock */
							global_lock->lock();
							has_global_lock = true;
						}
					}
				}