void remove(BinarySearchTree<ItemType>& BST, const string& treeName, const string& title)
{
	soundtrack cd;
	cd.setTitle(title);
	bool success = BST.remove(cd);
	if (success)
		cout << "\"" << title << "\"" << " deleted from " << treeName << "\n\n";
	else
		cout << "\"" << title << "\"" << " NOT deleted from " << treeName << "\n";
}  // end remove