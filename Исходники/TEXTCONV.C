static void textconv_cpmaps_init(void)
{
 if(textconv_cpmaps_ok)
  return;
 textconv_cpmaps_ok=1;

 textconv_cpsource_map=textconv_select_mapping_by_name(textconv_codepage_sourcename);
 textconv_cptarget_map=textconv_select_mapping_by_name(textconv_codepage_targetname);
#ifdef MPXPLAY_UTF8
 if(!textconv_cpsource_map){
  textconv_cpsource_map=textconv_select_mapping_by_id(GetACP());
  if(!textconv_cpsource_map){
   mpxp_uint16_t *mug;
   char asciistr[260];
   mapping_unicode_generated=mug=(mpxp_uint16_t*)calloc(1,(256-32+8)*sizeof(mpxp_uint16_t));
   if(mug){
    unsigned int i;
    for(i=32;i<256;i++)
     asciistr[i]=i;
    asciistr[256]=0;
    for(i=32;i<256;){
     unsigned int len=MultiByteToWideChar(CP_ACP,0,&asciistr[i],-1,mug,256+4-i);
     //fprintf(stdout,"%d len:%d   ",i,len);
     if(len){
      mug+=len;
      i+=len;
     }else{
      *mug++=(mpxp_uint16_t)('_');
      i++;
     }
    }
    //mug=mapping_unicode_generated;
    //for(i=32;i<256;i++,mug++)
    // fprintf(stdout,"| %3d %c %4.4X    ",i,i,mug[0]);
    textconv_cpmap_generated.map=mapping_unicode_generated;
    textconv_cpmap_generated.begin=32;
    textconv_cpsource_map=&textconv_cpmap_generated;
   }else
    textconv_cpsource_map=&cp_maps[0];
  }
 }
 if(textconv_cptarget_map)
  textscreen_console_codepage=textconv_cptarget_map->cp_id_num;
#else
 if(!textconv_cpsource_map){
  if(funcbit_test(id3textconv,ID3TEXTCONV_GET_WINCP))
   textconv_cpsource_map=textconv_select_mapping_by_id(GetACP());
  if(!textconv_cpsource_map)
   textconv_cpsource_map=&cp_maps[0];
 }
 if(!textconv_cptarget_map){
  if(funcbit_test(id3textconv,ID3TEXTCONV_GET_WINCP))
   textconv_cptarget_map=textconv_select_mapping_by_id(GetOEMCP());
  if(!textconv_cptarget_map)
   textconv_cptarget_map=&cp_maps[1];
 }
 textscreen_console_codepage=textconv_cptarget_map->cp_id_num;
 if(funcbit_test(id3textconv,ID3TEXTCONV_CODEPAGE)) // at -8
  textconv_cptarget_map=NULL; // WinChars/DosChars are used
 else if(textconv_cptarget_map==textconv_cpsource_map)
  textconv_cptarget_map=NULL;
#endif
}