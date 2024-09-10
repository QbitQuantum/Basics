/*************************************************
* Description: Loads the directoy contents of ~/Documents/Pictures into listview
* Author: Rick Caudill
* Date: Thu Mar 18 20:17:32 2004
**************************************************/
void WallpaperChangerSettings::LoadDirectoryList()
{
	String cDir = getenv( "HOME" );
	cDir += "/Pictures/";
	String cFile;
	
	Directory* pcDir = new Directory(cDir);
	pcDir->Rewind();
	
	while (pcDir->GetNextEntry(&cFile))
	{
		FSNode* pcNode = new FSNode(String(cDir + cFile));
		if (pcNode->IsFile())		//if not a dir, link and just a regular file
		{
			ListViewStringRow* pcRow = new ListViewStringRow();
			pcRow->AppendString(cFile);
			pcDirectoryList->InsertRow(pcRow);
		}
		delete pcNode;
	}
	delete pcDir;
}