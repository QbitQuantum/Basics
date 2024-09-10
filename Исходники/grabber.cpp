void Grabber::CopyGrabbedArea(int Append, int VerticalBlock)
{
	if (GArea.X1 < 0)
		return;

	int X1,Y1,X2,Y2;
	X1=Min(GArea.X1,GArea.X2);
	X2=Max(GArea.X1,GArea.X2);
	Y1=Min(GArea.Y1,GArea.Y2);
	Y2=Max(GArea.Y1,GArea.Y2);
	int GWidth=X2-X1+1,GHeight=Y2-Y1+1;
	int BufSize=(GWidth+3)*GHeight;
	FAR_CHAR_INFO* CharBuf=new FAR_CHAR_INFO[BufSize], *PtrCharBuf;
	wchar_t *CopyBuf=(wchar_t *)xf_malloc(BufSize*sizeof(wchar_t)), *PtrCopyBuf;
	WORD Chr;
	GetText(X1,Y1,X2,Y2,CharBuf,BufSize*sizeof(FAR_CHAR_INFO));
	*CopyBuf=0;
	PtrCharBuf=CharBuf;
	PtrCopyBuf=CopyBuf;

	for (int I=0; I<GHeight; I++)
	{
		if (I>0)
		{
			*PtrCopyBuf++=L'\r';
			*PtrCopyBuf++=L'\n';
			*PtrCopyBuf=0;
		}

		for (int J=0; J<GWidth; J++, ++PtrCharBuf)
		{
			WORD Chr2 = PtrCharBuf->Char;
			Chr=PtrCharBuf->Char;

			if (Opt.CleanAscii)
			{
				switch (Chr2)
				{
					case L'.':  Chr=L'.'; break;
					case 0x07: Chr=L'*'; break;
					case 0x10: Chr=L'>'; break;
					case 0x11: Chr=L'<'; break;
					case 0x18:
					case 0x19: Chr=L'|'; break;
					case 0x1E:
					case 0x1F: Chr=L'X'; break;
					case 0xFF: Chr=L' '; break;
					default:

						if (Chr2 < 0x20)
							Chr=L'.';
						else if (Chr2 < 0x100)
							Chr=Chr2;

						break;
				}
			}

			if (Opt.NoGraphics && Chr2 >=0xB3 && Chr2 <= 0xDA)
			{
				switch (Chr2)
				{
					case 0xB3:
					case 0xBA: Chr=L'|'; break;
					case 0xC4: Chr=L'-'; break;
					case 0xCD: Chr=L'='; break;
					default:   Chr=L'+'; break;
				}
			}

			*PtrCopyBuf++=Chr;
			*PtrCopyBuf=0;
		}

		for (int K=StrLength(CopyBuf)-1; K>=0 && CopyBuf[K]==L' '; K--)
			CopyBuf[K]=0;

		PtrCopyBuf=CopyBuf+StrLength(CopyBuf);
	}

	Clipboard clip;

	if (clip.Open())
	{
		if (Append)
		{
			wchar_t *AppendBuf=clip.Paste();
			if (AppendBuf)
			{
				int add=0;
				size_t DataSize=StrLength(AppendBuf);

				if (AppendBuf[DataSize-1]!=L'\n')
				{
					add=2;
				}

				AppendBuf=(wchar_t *)xf_realloc(AppendBuf,(DataSize+BufSize+add)*sizeof(wchar_t));
				wmemcpy(AppendBuf+DataSize+add,CopyBuf,BufSize);

				if (add)
					wmemcpy(AppendBuf+DataSize,L"\r\n",2);

				xf_free(CopyBuf);
				CopyBuf=AppendBuf;
			}
		}

		if (VerticalBlock)
			clip.CopyFormat(FAR_VerticalBlock_Unicode,CopyBuf);
		else
			clip.Copy(CopyBuf);

		clip.Close();
	}

	if (CopyBuf)
		xf_free(CopyBuf);

	delete[] CharBuf;
}