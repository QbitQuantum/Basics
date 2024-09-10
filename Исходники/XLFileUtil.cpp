void XLFileUtil::rotate(const std::string & inDir,const std::string& filenameprefix , unsigned int limit)
{
	//ファイルを見つけてリストに入れる
	std::vector<rotateSt> filelist;
	XLFileUtil::findfile(inDir , [&](const std::string& filename,const std::string& fullfilename) -> bool {
		if ( strstr(filename.c_str() , filenameprefix.c_str() )  )
		{
			filelist.push_back(rotateSt(getfiletime(fullfilename),fullfilename));
		}
		return true;
	});
	//limit 以上だったら、古いものから消す
	if (filelist.size() < limit)
	{
		return ;
	}
	//古いものを見つけるためにソートする
	std::sort(filelist.begin() , filelist.end() , [](const rotateSt& a,const rotateSt& b){
		return a.time < b.time ;
	});
	//リストの前の方から消していく
	int delCount = filelist.size() - limit;
	for(auto it = filelist.begin() ; it != filelist.end() ; ++it )
	{
		XLFileUtil::del(it->fullfilename);
		delCount --;
		if (delCount <= 0) break;
	}
	return ;
}