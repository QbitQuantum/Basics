/* Write a sequence of commands able to fully rebuild the dataset into
 * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
static int rewriteAppendOnlyFile(char *filename) {
    dictIterator *di = NULL;
    dictEntry *de;
    FILE *fp;
    char tmpfile[256];
    int j;
    time_t now = time(NULL);

    /* Note that we have to use a different temp name here compared to the
     * one used by rewriteAppendOnlyFileBackground() function. */
    snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
    fp = fopen(tmpfile,"w");

    for (j = 0; j < server.dbnum; j++) {
        char selectcmd[] = "*2\r\n$6\r\nSELECT\r\n";
        redisDb *db = server.db+j;
        dict *d = db->dict;

        if (dictSize(d) == 0) continue;
        di = dictGetIterator(d);


        /* SELECT the new DB */
        fwrite(selectcmd,sizeof(selectcmd)-1,1,fp);
        fwriteBulkLong(fp,j);

        /* Iterate this DB writing every entry */
        while((de = dictNext(di)) != NULL) {
            robj *key, *o;
            time_t expiretime;
            int swapped;

            key = dictGetEntryKey(de);
            /* If the value for this key is swapped, load a preview in memory.
             * We use a "swapped" flag to remember if we need to free the
             * value object instead to just increment the ref count anyway
             * in order to avoid copy-on-write of pages if we are forked() */
            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
                key->storage == REDIS_VM_SWAPPING) {
                o = dictGetEntryVal(de);
                swapped = 0;
            } else {
                o = vmPreviewObject(key);
                swapped = 1;
            }
            expiretime = getExpire(db,key);

            /* Save the key and associated value */
            if (o->type == REDIS_STRING) {
                /* Emit a SET command */
                char cmd[]="*3\r\n$3\r\nSET\r\n";
                fwrite(cmd, sizeof(cmd)-1,1,fp);
                /* Key and value */
                fwriteBulkObject(fp,key);
                fwriteBulkObject(fp,o);
            } 
            else if (o->type == REDIS_LIST) {
                /* Emit the RPUSHes needed to rebuild the list */
                list *list = o->ptr;
                listNode *ln;
                listIter li;

                listRewind(list,&li);
                while((ln = listNext(&li))) {
                    char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
                    robj *eleobj = listNodeValue(ln);

                    fwrite(cmd, sizeof(cmd)-1, 1, fp);
                    fwriteBulkObject(fp,key);
                    fwriteBulkObject(fp,eleobj);
                }
            } 
            else if (o->type == REDIS_SET) {
                /* Emit the SADDs needed to rebuild the set */
                dict *set = o->ptr;
                dictIterator *di = dictGetIterator(set);
                dictEntry *de;

                while((de = dictNext(di)) != NULL) {
                    char cmd[]="*3\r\n$4\r\nSADD\r\n";
                    robj *eleobj = dictGetEntryKey(de);

                    fwrite(cmd,sizeof(cmd)-1,1,fp) ;
                    fwriteBulkObject(fp,key) ;
                    fwriteBulkObject(fp,eleobj);
                }
                dictReleaseIterator(di);
            } 
            else if (o->type == REDIS_ZSET) {
                /* Emit the ZADDs needed to rebuild the sorted set */
                zset *zs = o->ptr;
                dictIterator *di = dictGetIterator(zs->dict);
                dictEntry *de;

                while((de = dictNext(di)) != NULL) {
                    char cmd[]="*4\r\n$4\r\nZADD\r\n";
                    robj *eleobj = dictGetEntryKey(de);
                    double *score = dictGetEntryVal(de);

                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                    if (fwriteBulkObject(fp,key) == 0) goto werr;
                    if (fwriteBulkDouble(fp,*score) == 0) goto werr;
                    if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                }
                dictReleaseIterator(di);
            } else if (o->type == REDIS_HASH) {
                char cmd[]="*4\r\n$4\r\nHSET\r\n";

                /* Emit the HSETs needed to rebuild the hash */
                if (o->encoding == REDIS_ENCODING_ZIPMAP) {
                    unsigned char *p = zipmapRewind(o->ptr);
                    unsigned char *field, *val;
                    unsigned int flen, vlen;

                    while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                        if (fwriteBulkObject(fp,key) == 0) goto werr;
                        if (fwriteBulkString(fp,(char*)field,flen) == -1)
                            return -1;
                        if (fwriteBulkString(fp,(char*)val,vlen) == -1)
                            return -1;
                    }
                } else {
                    dictIterator *di = dictGetIterator(o->ptr);
                    dictEntry *de;

                    while((de = dictNext(di)) != NULL) {
                        robj *field = dictGetEntryKey(de);
                        robj *val = dictGetEntryVal(de);

                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                        if (fwriteBulkObject(fp,key) == 0) goto werr;
                        if (fwriteBulkObject(fp,field) == -1) return -1;
                        if (fwriteBulkObject(fp,val) == -1) return -1;
                    }
                    dictReleaseIterator(di);
                }
            } else {
                redisAssert(0);
            }
            /* Save the expire time */
            if (expiretime != -1) {
                char cmd[]="*3\r\n$8\r\nEXPIREAT\r\n";
                /* If this key is already expired skip it */
                if (expiretime < now) continue;
                fwrite(cmd,sizeof(cmd)-1,1,fp) ;
                fwriteBulkObject(fp,key) ;
                fwriteBulkLong(fp,expiretime) ;
            }
            if (swapped) decrRefCount(o);
        }
        dictReleaseIterator(di);
    }

    /* Make sure data will not remain on the OS's output buffers */
    fflush(fp);
    fsync(fileno(fp));
    fclose(fp);
    
    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    rename(tmpfile,filename) ;
    
    redisLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
    return REDIS_OK;
}