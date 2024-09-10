void GraphTreeModel::updateSelectionStatus(const Glib::RefPtr<Gtk::TreeSelection>& selection, const scene::INodePtr& node)
{
	NodeMap::const_iterator found = _nodemap.find(scene::INodeWeakPtr(node));

	GraphTreeNodePtr foundNode;

	if (found == _nodemap.end())
	{
		// The node is not in our map, it might have been previously hidden
		if (node->visible())
		{
			foundNode = insert(node);
		}
	}
	else
	{
		foundNode = found->second;
	}

	if (foundNode)
	{
		if (Node_isSelected(node))
		{
			// Select the row in the TreeView
			selection->select(foundNode->getIter());

			// Scroll to the row
			Gtk::TreeView* tv = selection->get_tree_view();

			Gtk::TreeModel::Path selectedPath(foundNode->getIter());

			tv->expand_to_path(selectedPath);
			tv->scroll_to_row(selectedPath, 0.3f);
		}
		else
		{
			selection->unselect(foundNode->getIter());
		}
	}
}