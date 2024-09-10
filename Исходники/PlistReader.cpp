PlistReader::PlistReader()
{
    XmlTree plist =  XmlTree(loadResource( "RECIPES.plist" ) );
    console() << "this is the tag name... " << plist.getTag() << "IS THIS A DOC ELEMENT OR WAHAT???? " << plist.isDocument() << endl;
    try {
        root = plist.getChild("plist");
    } catch(XmlTree::Exception e){
        console() << "darn" << endl;
    }
    //trace(root);
    parseRecipes();
}