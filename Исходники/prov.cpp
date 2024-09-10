void delProvFiles(const int *p, int iCnt){
   CTEditBase b(1024);
   for(int i=0;i<2;i++){
      if(!pFN_to_save[i])break;
      setCfgFN(b,pFN_to_save[i]);
      deleteFileW(b.getText());
   }
   
   char buf[64];
   
   for(int i=0;i<iCnt;i++){
      printf("del prov %d\n",p[i]);
      if(p[i]==1)continue;//dont delete if created by user
      if(i)snprintf(buf, sizeof(buf)-1, "tivi_cfg%d.xml", i); else strcpy(buf,"tivi_cfg.xml");
      setCfgFN(b,buf);
      deleteFileW(b.getText());
   }
}