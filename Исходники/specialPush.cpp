int SpecialPush::getSpecialPush(uint32_t type)
{
	if(!_getPid())
		return false;
	struct dirent *dir_info = NULL;
    char filename[1024];
    uint32_t index=0;
    int ret=0;
    int typeCount = 0;
    
    if(type!=0)
        typeCount = _queryTypeCount(type);

    DIR* innerDir = opendir(_baseDir.c_str());
    if(innerDir==NULL)
    {    
        mylogF("spec innerDir is NULL, baseDir is %s, error %d",_baseDir.c_str(),errno); 
        return -1;
    }

    while(  NULL !=(dir_info=readdir(innerDir)) ) 
    {
        if((strcmp(dir_info->d_name,".")==0)||(strcmp(dir_info->d_name,"..")==0))
            continue;
        _curPid++;
        typeCount++;
        snprintf(filename,1024,"/%s",dir_info->d_name);
        std::string finPath =_baseDir+std::string(filename);
        std::string wh;
        char indexDir[1024]={0};
        char showDir[1024]={0};
        char cpid[1024]={0};
        index=_curPid/_dirSplit;
        snprintf(indexDir,1024,"/index%d/",index);
        snprintf(showDir,1024,"/show%d/",index);
        snprintf(cpid,1024,"%d_",_curPid);
        std::string smallDirFull = _pushBaseDir +  indexDir;
        std::string showDirFull = _pushBaseDir + showDir;
    
        MyImage proImg(finPath);  
        if(""==(wh = proImg.getWidthHeight()))    
        {
            mylogF("this pid getWidthHeight err : %d",_curPid);
            continue;
        }

        std::string sImgname = cpid + wh +".jpg";
        std::string showImgname = getMd5(sImgname); 

        std::string smallImg = smallDirFull + sImgname;
        std::string showImg = showDirFull + showImgname + ".jpg";
    
        mylogD("get smalldir: %s , smallImg: %s, showdir:%s, showImg:%s. pid: %d",smallDirFull.c_str(), smallImg.c_str(), showDirFull.c_str(),showImg.c_str() ,_curPid);
        _makeStaicSql(_curPid,sImgname,_sqlSplit);    
        uint32_t pageIndex = _curPid/EACHPAGE;
        _makeDynamicSql(_curPid,pageIndex);
        
        //说明走的是type添加的流程 
        if(type!=0)
        {
            pageIndex = typeCount/EACHPAGE;
            _insertTypeSql(type,_curPid,pageIndex);
        }
        
        if(! proImg.reSize(_sw,_sh) )
        {
            mylogF("this pid reSize err : %d",_curPid);
            continue;
        }
        
        if(! proImg.saveDstImg(smallImg,smallDirFull))
        {
            mylogF("this pid saveDstImg err : %d",_curPid);
            continue;
        }
       
        if(! proImg.saveSrcImg(showImg,showDirFull))
        {
            mylogF("this pid saveSrcImg err : %d",_curPid);
            continue;
        }

        _pidSet.push_back(_curPid);
        _pidDSet.push_back(DynamicInfo(_curPid,pageIndex,_curPid%5+1));
        ++ret;

    }
    
    if(!_setPid())
    {
        mylogF("update status[count] into pid file fail !!!");
        exit(1);
    }

    if(!_makeStatusSql())
    {
        mylogF("update status[count] into mysql fail !!!");
        exit(1);
    }

    if(type!=0)
    {
        _updateTypeStatus(type,typeCount);
    }
    if(closedir(innerDir)!=0)
    {
        mylogF("close file fail");
    }
    innerDir=NULL;
    mylog("spec: get getSomeSpecial done");
   
 	return ret;
}