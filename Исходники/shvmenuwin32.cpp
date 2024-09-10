/*************************************
 * Destructor
 *************************************/
SHVMenuCommandBarPocketPC::~SHVMenuCommandBarPocketPC()
{
	if (hCmdWnd)
		CommandBar_Destroy(hCmdWnd);

	SetMenu(NULL, NULL);
}