int
TextPointer::CompareToWithError (const TextPointer *pointer, MoonError *error) const
{
	if (!verify_textpointer_in_document (this, error) ||
	    !verify_textpointer_in_document (pointer, error))
		return -1;

	if (this->GetParent() == pointer->GetParent()) {
		DependencyObjectCollection *children = this->GetParentNode()->GetDocumentChildren();
		if (children && children->GetCount() > 0)
			return compare_locations (this->GetLocation(), pointer->GetLocation());
		else
			return this->ResolveLocation() - pointer->ResolveLocation();
	}
	else {
		GPtrArray *this_array = g_ptr_array_new();
		GPtrArray *pointer_array = g_ptr_array_new();

		DependencyObject *el = GetParent();
		while (el) {
			g_ptr_array_insert (this_array, 0, el);
			if (el->Is (Type::RICHTEXTBOX))
				break;
			el = el->GetParent() ? el->GetParent()->GetParent() : NULL;
			if (!el)
				break;
		}

		el = pointer->GetParent();
		while (el) {
			g_ptr_array_insert (pointer_array, 0, el);
			if (el->Is (Type::RICHTEXTBOX))
				break;
			el = el->GetParent() ? el->GetParent()->GetParent() : NULL;
			if (!el)
				break;
		}

		guint32 count_to_compare = MIN (this_array->len, pointer_array->len);

		for (guint32 i = 0; i < count_to_compare; i ++) {
			DependencyObject *this_el = (DependencyObject*)g_ptr_array_index (this_array, i);
			DependencyObject *pointer_el = (DependencyObject*)g_ptr_array_index (pointer_array, i);

			if (this_el == pointer_el)
				continue;

			if (i == 0) {
				// this shouldn't happen... there shouldn't be a difference between two paths on the first element, since that should always be a RTB
				int rv = this_array->len < pointer_array->len ? -1 : 1;
				g_ptr_array_free (this_array, TRUE);
				g_ptr_array_free (pointer_array, TRUE);
				return rv;
			}

			/* at this point this_el and pointer_el are
			   different.  check index i-1's idea of their
			   positions */
			DependencyObject *common_parent = (DependencyObject*)g_ptr_array_index (this_array, i-1);
			IDocumentNode *common_parent_node = IDocumentNode::CastToIDocumentNode (common_parent);
			int this_index = common_parent_node->GetDocumentChildren()->IndexOf (Value (this_el));
			int pointer_index = common_parent_node->GetDocumentChildren()->IndexOf (Value (pointer_el));
			g_ptr_array_free (this_array, TRUE);
			g_ptr_array_free (pointer_array, TRUE);
			return this_index < pointer_index ? -1 : 1;
		}

		// if we make it here, it means we've run through
		// "count_to_compare" items that were identical, and
		// one of the paths is longer (so represents a child
		// of items[count_to_compare].

		// so we need to figure out which array has more
		// elements, then compare that against the other
		// TextPointer's location

		if (count_to_compare < this_array->len) {
			// @this's parent is a child of pointer_array[count_to_compare-1]
			DependencyObject *parent = (DependencyObject*)g_ptr_array_index(pointer_array, count_to_compare - 1);
			IDocumentNode *parent_node = IDocumentNode::CastToIDocumentNode (parent);
			guint32 child_index = parent_node->GetDocumentChildren()->IndexOf (Value ((DependencyObject*)g_ptr_array_index(this_array, count_to_compare)));

			return pointer->GetLocation() > child_index ? -1 : 1;
		}
		else if (count_to_compare < pointer_array->len) {
			// @pointer's parent is a child of this_array[count_to_compare-1]
			DependencyObject *parent = (DependencyObject*)g_ptr_array_index(this_array, count_to_compare - 1);
			IDocumentNode *parent_node = IDocumentNode::CastToIDocumentNode (parent);
			guint32 child_index = parent_node->GetDocumentChildren()->IndexOf (Value ((DependencyObject*)g_ptr_array_index(pointer_array, count_to_compare)));

			return child_index >= this->GetLocation () ? -1 : 1;
		}
	}
	return -1;
}