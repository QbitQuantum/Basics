bool
TabNavigationWalker::FocusChild ()
{
	UIElement *child;
	bool child_is_control;
	int current_index = -1;

	// Add each branch of the visual tree to the array and then sort them
	// based on the TabIndex of the first Control in each branch
	VisualTreeWalker child_walker (root);
	while ((child = child_walker.Step ()))
		g_ptr_array_add (tab_sorted, child);

	if (tab_sorted->len > 1) {
		Sort (tab_sorted, types);

		if (ReverseTab ()) {
			GPtrArray *reverse = g_ptr_array_sized_new (tab_sorted->len);
			for (int i = tab_sorted->len - 1; i >= 0; i--)
				g_ptr_array_add (reverse, tab_sorted->pdata [i]);
				
			g_ptr_array_free (tab_sorted, true);
			tab_sorted = reverse;
		}
	}

	// Find the index of the currently selected node so we know which node to
	// tab to next
	for (uint i = 0; i < tab_sorted->len; i++)
		if (tab_sorted->pdata [i] == current)
			current_index = i;

	// If a child of the root element is Focused and we're forward-tabbing, it means we should
	// skip the entire subtree and go to the next 'root'. If we're reverse-tabbing it means we
	// should Focus the root.
	if (current_index != -1 && GetActiveNavigationMode (root, types) == KeyboardNavigationModeOnce) {
		// If we're tabbing backwards and a child of this control is currently Focused, we
		// should focus this control.
		if (ReverseTab () && types->IsSubclassOf (root->GetObjectType (), Type::CONTROL))
			return TabTo ((Control *)root);
		return false;
	}

	if (tab_sorted->len > 0) {
		// If the currently selected element was found at index 'i' we need to tab
		// to the *next* index. If the currently selected item was not here, we
		// need to start at index 0.
		for (unsigned int i = 0; i < tab_sorted->len; i++) {
			// If we are not cycling, it means we've tabbed to the last element of this node and so should 
			if ((i + current_index + 1) == tab_sorted->len && GetActiveNavigationMode (root, types) != KeyboardNavigationModeCycle)
				break;

			child = (UIElement *) tab_sorted->pdata [(i + current_index + 1) % tab_sorted->len];
			child_is_control = types->IsSubclassOf (child->GetObjectType (), Type::CONTROL);

			if (child_is_control && !((Control *)child)->GetIsEnabled ())
				continue;

			// When tabbing backwards, we recurse all children *before* attempting to select this node
			if (ReverseTab () && WalkChildren (child))
				return true;

			if (child_is_control && TabTo ((Control *)child))
				return true;

			if (ForwardTab () && WalkChildren (child))
				return true;
		}
	}

	// If we're tabbing backwards and a child of this control is currently Focused, we
	// should focus this control.
	if (current_index != -1 && ReverseTab ()) {
		if (types->IsSubclassOf (root->GetObjectType (), Type::CONTROL))
			return TabTo ((Control *)root);
	}

	// Nothing could be tabbed to on this visual level
	return false;
}