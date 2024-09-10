FB::variant ibrowserAPI::downloadFile(const std::string& url,const std::string& filename,const boost::optional<FB::JSObjectPtr>& pcb, F_ADD)
{
    if(url.empty() || filename.empty())
        ERRO("url or filename is empty!");
    
    THREAD(&ibrowserAPI::downloadFile,url,filename,pcb);
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    double fileSize = -1;
    CURL *fileSizeCurl = curl_easy_init();
    curl_easy_setopt(fileSizeCurl, CURLOPT_URL,url.c_str());
    curl_easy_setopt(fileSizeCurl, CURLOPT_HEADER, 1);
    curl_easy_setopt(fileSizeCurl, CURLOPT_NOBODY, 1);
    curl_easy_perform(fileSizeCurl);
    curl_easy_getinfo(fileSizeCurl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &fileSize);
    curl_easy_cleanup(fileSizeCurl);
    
    log("download file size:%.0f",fileSize);
    if(0 >= fileSize)
    {
        ERRO("get file size error");
    }
    
    char tmpName[1024];
    sprintf(tmpName,"%s/%s",dirname(tmpnam(NULL)),filename.c_str());
    
    log("start download, save file:%s, use %d threads",tmpName,this->downloadThreads);
    
    double partSize=fileSize/this->downloadThreads;
    pthread_t threads[this->downloadThreads];
    std::vector<double> counter;
    for(int i=0;i<this->downloadThreads;i++)
    {
        double start=partSize*i;
        double end=0;
        if(i+1<this->downloadThreads)
            end=partSize*(i+1)-1;
        else
            end=fileSize;
        FILE *tmpFile=fopen(tmpName,"wb+");
        if(!tmpFile)
            ERRO("create tmp file error");
        fseek(tmpFile,start,SEEK_SET);
        counter.push_back(0);
        
        log("threadid:%d,range:%.0f-%.0f",i,start,end);
        DownloadConfig *cfg=new DownloadConfig(i,url,tmpFile,*pcb,fileSize,start,end,&counter);
        pthread_create(&threads[i],NULL,&ibrowserAPI::downloadThread,cfg);
    }
    
    for(int i=0; i< this->downloadThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    curl_global_cleanup();
    
    double downloadSize=0;
    int len=counter.size();
    for(int i=0;i<len;i++)
    {
        downloadSize+=counter.at(i);
    }
    //downloadSize+=1;
    log("downloadSize:%.0f",downloadSize);
    if(downloadSize == fileSize)
    {
        SUCC(tmpName);
    }else{
        ERRO("download error");
    }
    
    
    return true;
}