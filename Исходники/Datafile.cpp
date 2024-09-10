int BDATreader::seek(unsigned int ID,datablockinfo &db) {
    int n=0;
    if(!hasTOC) createTOC();
    if(!hasTOC) return -1; //no TOC available (empty file?)
    
    while((n<TOCN) && (TOCID[n]!=ID)) n++;
    if(n==TOCN) return -2; //entry not found
    
    pos=TOCpos[n];state=1;
    FileSeek(f,pos,SEEK_SET);
    
    return getnextblockinfo(db);
};