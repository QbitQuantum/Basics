void handle_fstab_record(struct MNvramObserver* observer,
			 struct ParsedRecord* record,
			 void* obj1, void* obj2, void* obj3){
    assert(record);
    struct FstabObserver* fobserver = (struct FstabObserver*)observer;
    s_channels_mount = (struct MountsPublicInterface*)obj1;     /*obj1 - channels filesystem interface*/
    s_transparent_mount = (struct MountsPublicInterface*)obj2;  /*obj2 - whole filesystem interface*/

    if ( observer->is_valid_record(observer, record) != 0 ) return; /*skip record invalid*/

    /*check array*/
    if ( fobserver->postpone_mounts_array == NULL ){
	assert( fobserver->postpone_mounts_count ==0 );
    }

    /*extend array & add record to mounts array
      no checks for duplicated items doing*/
    ++fobserver->postpone_mounts_count;
    fobserver->postpone_mounts_array 
	= realloc(fobserver->postpone_mounts_array, 
		  sizeof(*fobserver->postpone_mounts_array)*fobserver->postpone_mounts_count);
    assert(fobserver->postpone_mounts_array != NULL);
    /*record added into postopne mounts list and must be handled later*/
    struct FstabRecordContainer* record_container = &fobserver->postpone_mounts_array[ fobserver->postpone_mounts_count -1 ];
    record_container->mount_status = EFstabMountWaiting;
    copy_record(record, &record_container->mount);

    /*get all params*/
    char* channel_alias = NULL;
    char* mount_path = NULL;
    char* access = NULL;
    char* removable = NULL;
    char* fsname = NULL;
    GET_FSTAB_PARAMS(record, &channel_alias, &mount_path, &access, &removable, &fsname);

    int write=0;     
    if ( !strcmp(access, FSTAB_VAL_ACCESS_WRITE) )  write =1;

    /*if archivemount is available and want mount tar in read-only mode*/
    if ( !strcasecmp( fsname, "tar") && !strcmp(access, FSTAB_VAL_ACCESS_READ) ){
#ifdef FUSEGLUE_EXT
        int    expect_absolute_path;
        char   proxy_mode;
        int    archivemount_argc;
        char **archivemount_argv;
        fs_main archivemount_entrypoint =
            fusefs_entrypoint_get_args_by_fsname("archivemount", write, 
                                                 channel_alias, mount_path,
                                                 &expect_absolute_path, &proxy_mode,
                                                 &archivemount_argc, &archivemount_argv);
        /*If archivemount is available then use it for tar mounting*/
        if ( archivemount_entrypoint ){
            /*mount fusefs*/
            int mount_res = exec_fuse_main(mount_path, expect_absolute_path, proxy_mode,
                                           archivemount_entrypoint,
                                           archivemount_argc, archivemount_argv);
            if (mount_res!=0){
                ZRT_LOG(L_ERROR, "exec_fuse_main err=%d", mount_res);
            }
        }
        else
#endif /*FUSEGLUE_EXT*/
        /*If no archimemount available and for compatibility use old approach.
          For first fstab handling (s_updated_fstab_records=0) after
          checks try mount channel with keys access=ro, removable=no*/
            if ( !s_updated_fstab_records  ){
                fobserver->mount_import(fobserver, record_container);
        }
    }
#ifdef FUSEGLUE_EXT
    /*Mount all another file systems*/
    else{
        int    fs_expect_absolute_path;
        int    fs_proxy_mode;
        int    fs_argc=0;
        char **fs_argv;
        fs_main fs_entrypoint =
            fusefs_entrypoint_get_args_by_fsname(fsname, write, 
                                                 channel_alias, mount_path,
                                                 &fs_expect_absolute_path, &fs_proxy_mode,
                                                 &fs_argc, &fs_argv);

        /*If fuse extensions are available and trying mount tar archive then use archivemount*/
        if (   fs_entrypoint != NULL ){
            /*mount fusefs*/
            int mount_res = exec_fuse_main(mount_path, fs_expect_absolute_path, fs_proxy_mode,
                                           fs_entrypoint, fs_argc, fs_argv);
            if (mount_res!=0){
                ZRT_LOG(L_ERROR, "exec_fuse_main err=%d", mount_res);
            }
        }
    }
#endif /*FUSEGLUE_EXT*/

    ZRT_LOG(L_SHORT, "fstab record channel=%s, mount_path=%s, access=%s, removable=%s, fsname=%s",
	    channel_alias, mount_path, access, removable, fsname);
}