uint8_t do_symlink(uint64_t lv,uint32_t ts,char *ptr) {
        uint32_t parent,uid,gid,inode;
        uint8_t name[256];
        static uint8_t *path;
        static uint32_t pathsize;
        EAT(ptr,lv,'(');
        GETU32(parent,ptr);
        EAT(ptr,lv,',');
        GETNAME(name,ptr,lv,',');
        EAT(ptr,lv,',');
        GETPATH(path,pathsize,ptr,lv,',');
        EAT(ptr,lv,',');
        GETU32(uid,ptr);
        EAT(ptr,lv,',');
        GETU32(gid,ptr);
        EAT(ptr,lv,')');
        EAT(ptr,lv,':');
        GETU32(inode,ptr);
        return shadow_fs_symlink(ts,parent,strlen((char*)name),name,path,uid,gid,inode);
}