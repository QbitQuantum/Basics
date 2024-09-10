bool trpgTexTable::Read(trpgReadBuffer &buf)
{
    int32 numTex;
    trpgToken texTok;
    int32 len;

    try {
	buf.Get(numTex);
		
	for (int i=0;i<numTex;i++) {
	    buf.GetToken(texTok,len);
	    if (texTok != TRPGTEXTURE) throw 1;
	    buf.PushLimit(len);
	    trpgTexture tex;
	    bool status = tex.Read(buf);
	    //set the block for multi-archive archives (version>=2.3)
	    if((currentRow!=-1)&&(currentCol!=-1)) {
		trpgwAppAddress taddr;
		tex.GetImageAddr(taddr);
		taddr.col = currentCol;
		taddr.row = currentRow;
		tex.SetImageAddr(taddr);
	    }
	    AddTexture(tex);
	    buf.PopLimit();
	    if (!status) throw 1;
	}
    }
    catch (...) {
	return false;
    }

    return true;
}