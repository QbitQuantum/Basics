void addnth(int data, int nth)
{
	printf("%s: %d %d ", __FUNCTION__, data, nth);
	NODE *newnode; 
	NODE *cur = head; 
	int l = length();

	if (nth <= 0 || nth > l+1) { 
		printf("Invalid nth \n");
		return;
	}

	if (newnode = (NODE *) malloc(sizeof (NODE))) {
		newnode->data = data;
		newnode->next = NULL;
		newnode->prev = NULL;
	} else {
		printf("unable to allocate memory \n");
		return;
	}

	if (nth == 1) {
		// If list is empty and nth is position #1
		if (head == NULL) {
			assert (tail == NULL);
			head = tail = newnode;
			printf("added \n");
			return;
		}
		// The list is not empty but attempting to 
		// add the element in the head's position
		newnode->next = head;
		head->prev = newnode;
		head = newnode;	
		printf("added \n");
		return;
	}

	// Adding just after the tail node.. ie. when 
	// nth == len+1	
	if (nth == l+1) { 
		tail->next = newnode;
		newnode->prev = tail;
		tail = newnode;
		printf("added \n");
		return;
	}

	// All the other cases
	--nth;
	while (--nth) {
		cur = cur->next;
	}
	newnode->prev = cur;
	newnode->next = cur->next;
	cur->next->prev = newnode;
	cur->next = newnode;
	printf("added \n");

	return;
}