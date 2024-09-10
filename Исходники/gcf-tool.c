static void gcf_extract(){
    char *gcf_name=HREnextArg();
    if (gcf_name==NULL) {
        Abort("missing <gcf archive> argument");
    }
    archive_t arch=arch_gcf_read(raf_unistd(gcf_name));
    archive_t dir;
    if (outputdir) {
        dir=arch_dir_create(outputdir,blocksize,force?DELETE_ALL:DELETE_NONE);
    } else {
        dir=arch_dir_open(".",blocksize);
    }
    char*pattern=HREnextArg();
    do {
        archive_copy(arch,dir,NULL,blocksize,pattern);
    } while((pattern=HREnextArg()));
    arch_close(&dir);
    arch_close(&arch);
}