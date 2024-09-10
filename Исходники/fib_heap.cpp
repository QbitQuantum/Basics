/**
 * Transform the root list into a list of binonmial heaps.
 * It makes the amortized cost so good for a secuence of mixed insert() and deleteMin() calls.
 * Cost: O(log n)
 * Pre: this fib_heap has at least 1 element.
 * Post: list of binomial heaps
 **/
void fib_heap::consolidate()
{
	const int max_bin_heaps = 1.5 * (log2(n) + 1) ; //1.5*log n

	node_t* aux_array[max_bin_heaps];

	//Init array:
	for (int i = 0; i<max_bin_heaps; ++i) {
		aux_array[i] = nullptr;
	}

	node_t *aux1, *aux2;	//correspondence with MAR notes x <=> aux1 & y <=> aux2
	D(std::cerr << "Debug: consolidate loop starts" << std::endl);

	//We've gotta go over every node in the root list
	while (root_list != nullptr) {
		aux1 = root_list;

		remove_from_list(root_list,aux1);

		//Make aux1 an unitary circular list (link to itself only)
		aux1->right = aux1;
		aux1->left = aux1;

		//Inside this while, we make sure we are creating only one bin heap of every degree
		while (aux_array[aux1->degree] != nullptr) {
			D(std::cerr << "bin heap of degree " << aux1->degree << " already taken by " << aux_array[aux1->degree]->key << std::endl);
			D(std::cerr << "consolidate loop" << std::endl << std::endl);

			aux2 = aux_array[aux1->degree]; //Another node with the same degree as aux1

			//if aux1 is greater, it swaps them so that aux1 is always <= aux2
			if (aux1->key > aux2->key) {
				swap(aux1,aux2);
			}

			aux_array[aux1->degree] = nullptr;
			fib_heap_link(aux2,aux1);
		}
		aux_array[aux1->degree] = aux1;

	}

	//Now, we restore the heap and the min pointer
	for (int i = 0; i<max_bin_heaps; ++i) {
		node_t *x = aux_array[i];
		if (x != nullptr) {
			if (this->isEmpty()) {
				root_list = x;
			} else {
				concatenate_circular_lists(root_list,x);

				if (x->key < min->key)
					min = x;
			}
		}
	}

	D(std::cerr << "Debug: consolidate ok" << std::endl);
	D(std::cout << *this << std::endl);

}