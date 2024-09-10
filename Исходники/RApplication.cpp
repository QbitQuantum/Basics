void RApplication::writeVideo()
{
	char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
	_splitpath_s( Pubvar::videoPath.c_str(), drive, dir, fname, ext);
	
	string outputPath = "";
	int start = 0, end = 0, idx = 0, winsize = 8 * fps;
	VideoWriter writer;
	VideoCapture capCut;
	CV_Assert(capCut.open(Pubvar::videoPath));	
	Mat cutFrame;

	for (int i = winsize; i < videoLen; ++i)
	{		
		if(fidOI[i])
		{				
			outputPath = "data/" + (string)fname + "_" + to_string(idx++) + ext;
			writer = VideoWriter(outputPath, CV_FOURCC('D', 'I', 'V', '3') , fps, frame.size());
			capCut.set(CV_CAP_PROP_POS_FRAMES, i-winsize);			
			for(int j=i-winsize ; j<=i ; j++)
			{
				capCut >> cutFrame;
				writer << cutFrame;
			}
			writer.release();			
		}
	}	
}