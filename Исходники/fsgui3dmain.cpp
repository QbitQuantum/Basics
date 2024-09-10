/* virtual */ void FsLazyWindowApplication::GetOpenWindowOption(FsOpenWindowOption &opt) const
{
	opt.x0=96;
	opt.y0=0;
	opt.wid=1200;
	opt.hei=640;

	auto *cfg=PolyCreConfig::Create();
	auto *fileAndDirName=PolyCreFileName::Create();

	cfg->Load(fileAndDirName->GetOptionFileName());
	if(YSTRUE==cfg->saveWindowPositionAndSize)
	{
		auto wposFn=fileAndDirName->GetLastWindowPositionFileName();

		FILE *fp=YsFileIO::Fopen(wposFn,"r");
		if(NULL!=fp)
		{
			YsString str;
			while(NULL!=str.Fgets(fp))
			{
				YsArray <YsString> args;
				str.Arguments(args);
				if(0==strcmp(args[0],"POS") && 5<=args.GetN())
				{
					opt.x0=atoi(args[1]);
					opt.y0=atoi(args[2]);
					opt.wid=atoi(args[3]);
					opt.hei=atoi(args[4]);
					if(0>opt.x0)
					{
						opt.x0=0;
					}
					if(0>opt.y0)
					{
						opt.y0=0;
					}
					if(120>opt.wid)
					{
						opt.wid=120;
					}
					if(120>opt.hei)
					{
						opt.hei=120;
					}
				}
			}
			fclose(fp);
		}
	}

	PolyCreConfig::Delete(cfg);
	PolyCreFileName::Delete(fileAndDirName);
}