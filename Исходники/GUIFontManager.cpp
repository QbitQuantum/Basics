void GUIFontManager::clear()
{
  for(size_t i = 0; i < guiFontList.size(); i++)
    deleteObject(guiFontList[i]); 
  
  guiFontList.clear();
}