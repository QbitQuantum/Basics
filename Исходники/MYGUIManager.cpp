void MYGUIManager::setupResources()
{
    MyGUI::xml::Document doc;
    if ( !_platform || !doc.open(_resourcePathFile) ) doc.getLastError();
    
    MyGUI::xml::ElementPtr root = doc.getRoot();
    if ( root==nullptr || root->getName()!="Paths" ) return;
    
    MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
    while ( node.next() )
    {
        if ( node->getName()=="Path" )
        {
			bool root = false, recursive = false;
			if (!node->findAttribute("root").empty())
            {
                root = MyGUI::utility::parseBool( node->findAttribute("root") );
                if ( root ) _rootMedia = node->getContent();
            }
			if (!node->findAttribute("recursive").empty())
			{
				recursive = MyGUI::utility::parseBool(node->findAttribute("recursive"));
			}
			_platform->getDataManagerPtr()->addResourceLocation(node->getContent(), recursive);
        }
    }
}