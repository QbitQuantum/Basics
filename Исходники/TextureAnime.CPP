	bool TextureAnime<T>::Load(TDFNode *tdf,uint fmt,int mip)
	{
		tdf->ReadInt32(L"帧数",FrameCount);

		PicList=new TextureAnime<T>::Frame[FrameCount];
		TotalTime=0;

		for(int i=0;i<FrameCount;i++)
		{
			String name;

			name.Sprintf(L"第%d帧",i);

			int w,h;
			int8 c;
			uint8 *data;
			uint format;

			TDFNode *node=tdf->FindNode(name);

			if(!node)
            	return(false);

			node->ReadUint32(L"时间",PicList[i].time);

			TotalTime+=PicList[i].time;

			node->ReadInt32(L"宽",  w );
			node->ReadInt32(L"高",  h);
			node->ReadInt8 (L"色彩",c );

			width=w;
			height=h;
			orign_color=(ColorType)c;

			data=new uint8[w*h*c];

			tdfReadCompressData(node,L"象素数据",data,w*h*c);

			if(fmt==0)
				format=GLFormatByColorType[c];
			else
            	format=fmt;

			PicList[i].pic=new T(data,w,h,GLFormatByColorType[c],format,mip);

			delete[] data;
		}

		return(true);
	}