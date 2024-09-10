YSRESULT YsShell::LoadSrf(
    FILE *fp,YsArray <YsShellPolygonHandle> *noShadingPolygon,YsArray <YsShellVertexHandle> *roundVtx)
{
	if(NULL!=fp)
	{
		YsArray <YsString,16> args;

		if(noShadingPolygon!=NULL)
		{
			noShadingPolygon->Set(0,NULL);
		}
		if(roundVtx!=NULL)
		{
			roundVtx->Set(0,NULL);
		}
		if(BeginReadSrf()==YSOK)
		{
			YsString str;
			while(str.Fgets(fp)!=NULL)
			{
				if(ReadSrfOneLine(str,noShadingPolygon,roundVtx)!=YSOK)
				{
					str.Arguments <16> (args);
					if(args.GetN()>0)
					{
						YSBOOL srmExtension;
						srmExtension=YSFALSE;

						args[0].Capitalize();

						switch(args[0][0])
						{
						case 'G':  // GE, GL, GF
						case 'Z':  // ZE, ZF, ZNBE,ZNBF, ZT, ZA, ZZ, ZH, ZU
						case 'Y':  // YE, YF, YN, Y1
						case 'M':  // M
						case 'C':  // CV
						case 'X':  // X
						case 'L':  // LF, LE, LL
							srmExtension=YSTRUE;
							break;
						}

						if(srmExtension!=YSTRUE)
						{
							return YSERR;
						}
					}
				}
			}
			EndReadSrf();
			return YSOK;
		}
	}

	return YSERR;
}