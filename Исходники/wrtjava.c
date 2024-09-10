/* Writing Functions */
static void 
string_write_java(struct SResource *res,UErrorCode *status) {       
    if(uprv_strcmp(srBundle->fKeys+res->fKey,"%%UCARULES")==0 ){
        char fileName[1024] ={0};
        const char* file = "UCARules.utf8";
        FileStream* datFile = NULL;
        const char* type = "new ICUListResourceBundle.ResourceString(";
        char* dest  = (char*) uprv_malloc( 8 * res->u.fString.fLength);
        int32_t len = 0;
        if(outDir){
            uprv_strcat(fileName,outDir);
            if(outDir[uprv_strlen(outDir)-1]!=U_FILE_SEP_CHAR){
                uprv_strcat(fileName,U_FILE_SEP_STRING);
            }
        }
        uprv_strcat(fileName,file);/* UCARULES.utf8 UTF-8 file */
        
        write_tabs(out);

        T_FileStream_write(out, type, (int32_t)uprv_strlen(type));
        T_FileStream_write(out, "\"", 1);
        T_FileStream_write(out, file, (int32_t)uprv_strlen(file));
        T_FileStream_write(out, "\")\n", 3);
        datFile=T_FileStream_open(fileName,"w");
        
        if(!dest){
            *status=U_MEMORY_ALLOCATION_ERROR;
        }
        
        u_strToUTF8(dest,8*res->u.fString.fLength,&len,res->u.fString.fChars,res->u.fString.fLength,status);
        if(U_FAILURE(*status)){
            T_FileStream_close(datFile);
            uprv_free(dest);
            return;
        }
        T_FileStream_write(datFile,dest,len);
        T_FileStream_close(datFile);
        uprv_free(dest);
           
    }else{
        str_write_java(res->u.fString.fChars,res->u.fString.fLength,TRUE,status);

        if(uprv_strcmp(srBundle->fKeys+res->fKey,"Rule")==0){
            UChar* buf = (UChar*) uprv_malloc(sizeof(UChar)*res->u.fString.fLength);
            uprv_memcpy(buf,res->u.fString.fChars,res->u.fString.fLength);      
            uprv_free(buf);
        }
    }

}