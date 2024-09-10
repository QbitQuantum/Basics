MStatus preview(const MArgList& args,bool useVertexColor)
{
	//单实例先清除
	if(MaterialSet::getSingletonPtr())
		MaterialSet::getSingletonPtr()->clear();

	char tempPath[MAX_PATH];
	GetTempPath(MAX_PATH, tempPath);
	std::string tempFileName(tempPath);
	ExportOptions::instance().m_outFilePath = tempFileName.c_str();
	tempFileName += "\\";
	tempFileName += _T("maya.mz");

	ExportOptions::instance().m_outFile = tempFileName.c_str();

	ExportOptions::instance().clipList.clear();
	MTime kTimeMin   = MAnimControl::animationStartTime();		//整个场景的起始帧
	MTime kTimeMax   = MAnimControl::animationEndTime();		//整个场景的结束帧

	clipInfo clip;
	clip.name = "Animation";
	clip.startFrame = (int)kTimeMin.value();
	clip.endFrame = (int)kTimeMax.value();
	clip.stepFrame = 1;
	ExportOptions::instance().clipList.push_back(clip);
	ExportOptions::instance().exportAnims = true;
	ExportOptions::instance().exportVertexColour = useVertexColor;

	/*BindPoseTool bindPoseTool;
	bindPoseTool.GoIntoBindPose();*/

	MWriter writer;
	writer.read();
	MStatus status = writer.write();

#ifdef RELEASEDEBUG
#define DLL_NAME "MayaPreview_rd.exe"
#elif _DEBUG
#define DLL_NAME "MayaPreview_d.exe"
#else
#define DLL_NAME "MayaPreview.exe"
#endif

	if(status == MS::kSuccess)
	{
		HWND hWnd = FindWindowEx(0,0,0,"MayaPreview");
		//if(hWnd)
		//{
		//	SendMessage(hWnd,WM_CLOSE,0,0);
		//	hWnd = 0;
		//}
		if(!hWnd)
		{
			static const std::string tMaxProgramName("Maya.exe");
			char path[257];
			GetModuleFileName(GetModuleHandle(tMaxProgramName.c_str()),path,256);
			std::string parentPath(path);
			parentPath.erase(parentPath.size() - tMaxProgramName.size(), tMaxProgramName.size());
			std::string previewProgramPath(parentPath + "preview\\" + DLL_NAME); 
			
			if(!ShellExecute(0,"open",previewProgramPath.c_str(),"","",SW_SHOW))
			{

				MessageBox(0,previewProgramPath.c_str(),"Can't Find MayaPreview Program",0);
				return MS::kFailure;
			}			
			hWnd = FindWindowEx(0,0,0,"MayaPreview");
			DWORD tick = GetTickCount();
			while(!hWnd)
			{
				DWORD tickNow = GetTickCount();
				if(tickNow - tick > 3000)break;
				Sleep(1);
				hWnd = FindWindowEx(0,0,0,"MayaPreview");
			}
		}
		if(hWnd)
		{
			SendMessage(hWnd,WM_USER + 128,0,0);
			SetActiveWindow(hWnd);
			SetForegroundWindow(hWnd);
			BringWindowToTop(hWnd);
		}
	}
	/*bindPoseTool	.UndoGoIntoBindPose();*/

	return MS::kSuccess;
}