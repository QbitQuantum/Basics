void
TextSelection::Insert (TextElement *element)
{
	if (anchor.GetParent() == NULL || moving.GetParent() == NULL)
		// if either are null we're going nowhere fast...
		return;

	ClearSelection ();

	// at this point both anchor and moving are the same location

	// depending on what the anchor's parent is,
	// and what @element is, we might need to
	// split the tree higher up
	DependencyObject *el = anchor.GetParent ();
	int loc = anchor.ResolveLocation();

	while (el) {
		DependencyObject *el_parent = el->GetParent();
		if (el_parent)
			el_parent = el_parent->GetParent();

		IDocumentNode *node = IDocumentNode::CastToIDocumentNode (el);

		DependencyObjectCollection *children = node->GetDocumentChildren ();
		if (children && element->Is (children->GetElementType())) {
			// we can insert the element here, so let's do it and be done with things
			children->Insert (loc, element);
			return;
		}

		if (!el_parent) {
			g_warning ("new element cannot fit inside element, and we can't split it");
			return;
		}
				
		// we need to split the current element at
		// @loc, add the new element to el's parent
		// after el, and walk back up to el's parent
		// with new_el's index as @loc.
		IDocumentNode *parent_node = IDocumentNode::CastToIDocumentNode (el_parent);
		DependencyObjectCollection *parents_children = parent_node ? parent_node->GetDocumentChildren () : NULL;

		if (parents_children == NULL)
			return; /* #rtx24 */

		DependencyObject *new_el;
		if (element->Is (el->GetObjectType()) /* a more precise check perhaps?  instead of subclass? */) {
			// we don't need to split the node.  we just
			// need to reach in and reparent children
			// after @loc into element.
			new_el = node ? node->Split (loc, element) : NULL;
		}
		else {
			new_el = node ? node->Split (loc) : NULL;
		}

		int new_el_loc = parents_children->IndexOf (el) + 1;

		if (new_el)
			parents_children->Insert (new_el_loc, new_el);

		el = el_parent;
		loc = new_el_loc;
		if (new_el && new_el != element)
			new_el->unref ();

		if (new_el == element) {
			// we've already inserted the element as part of the split.
			return;
		}
	}

	printf ("NIEX TextSelection::Insert\n");
}