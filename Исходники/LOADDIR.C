static void playlist_loaddir_get_driveinfos(void)
{
 DWORD drivesbits,i,vlen;

 loaddir_clear_driveinfos(0);

 drivesbits=GetLogicalDrives();
 if(!drivesbits)
  return;

 i=LOADDIR_FIRSTDRIVE;
 drivesbits>>=LOADDIR_FIRSTDRIVE;
 do{
  if(drivesbits&1){
   mpxplay_drivemap_info_t *di=&drivemap_infos[i];
   di->type=pds_chkdrive(i);
   loaddir_build_drivename(i,di->drivename);
   if((i>=2) || (di->type!=DRIVE_TYPE_FLOPPY)){
    if(di->type==DRIVE_TYPE_NETWORK){
     vlen=LOADDIR_DRIVE_VOLUMENAME_LEN;
     WNetGetConnection(di->drivename,&di->volumename[0],&vlen);
    }
    if((di->type!=DRIVE_TYPE_NETWORK) || !di->volumename[0])
     pds_drive_getvolumelabel(i,&di->volumename[0],LOADDIR_DRIVE_VOLUMENAME_LEN);
   }
   if(loaddir_lastvaliddrive<i)
    loaddir_lastvaliddrive=i;
  }
  drivesbits>>=1;
  i++;
 }while(i<LOADDIR_MAX_LOCAL_DRIVES);

 loaddir_diskdrives_mount_localdisks();
}