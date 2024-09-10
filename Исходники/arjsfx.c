static void final_cleanup(void)
{
 #if SFX_LEVEL>=ARJSFXV
  file_close(aistream);
  aistream=NULL;
  file_close(atstream);
  atstream=NULL;
 #else
  if(atstream!=NULL)
   fclose(atstream);
 #endif
 #if SFX_LEVEL>=ARJSFXV
  if(tmp_tmp_filename!=NULL&&!keep_tmp_file&&tmp_tmp_filename[0]!='\0')
   file_unlink(tmp_tmp_filename);
 #else
  if(tmp_tmp_filename[0]!='\0')
   file_unlink(tmp_tmp_filename);
 #endif
 #if SFX_LEVEL>=ARJSFXV&&(TARGET!=UNIX||defined(HAVE_FCLOSEALL))
  fcloseall();
 #endif
 if(quiet_mode)
  freopen(dev_con, m_w, stdout);
 #if SFX_LEVEL>=ARJSFXV
  if(ferror(stdout))
   msg_fprintf(stderr, M_DISK_FULL);
  if(debug_enabled&&strchr(debug_opt, 't')!=NULL)
  {
   ticks=get_ticks()-ticks;
   msg_cprintf(0, M_FINAL_TIMING, ticks);
  }
 #endif
}