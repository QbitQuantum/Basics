static inline void TranslateFilename( int c,char * tmp,size_t tmplen )
{
 int i;
 char * p;
 size_t len;
 gchar *msg = NULL;

 switch ( guiIntfStruct.StreamType )
  {
   case STREAMTYPE_STREAM:
        av_strlcpy(tmp, guiIntfStruct.Filename, tmplen);
        break;
   case STREAMTYPE_FILE:
          if ( ( guiIntfStruct.Filename )&&( guiIntfStruct.Filename[0] ) )
           {
            if ( (p = strrchr(guiIntfStruct.Filename, '/')) )
              av_strlcpy(tmp, p + 1, tmplen);
            else
              av_strlcpy(tmp, guiIntfStruct.Filename, tmplen);
            len=strlen( tmp );
            if ( ( len > 3 )&&( tmp[len - 3] == '.' ) ) tmp[len - 3]=0;
            else if ( ( len > 4 )&&( tmp[len - 4] == '.' ) ) tmp[len - 4]=0;
            else if ( ( len > 5 )&&( tmp[len - 5] == '.' ) ) tmp[len - 5]=0;
           }
          else
           {
            msg = g_filename_from_utf8( MSGTR_NoFileLoaded, -1, NULL, NULL, NULL );
            av_strlcpy( tmp, ( msg ? msg : MSGTR_NoFileLoaded ), tmplen );
           }
          break;
#ifdef CONFIG_DVDREAD
   case STREAMTYPE_DVD:
          if ( guiIntfStruct.DVD.current_chapter )
           {
            msg = g_filename_from_utf8( MSGTR_Chapter, -1, NULL, NULL, NULL );
            snprintf( tmp, tmplen, ( msg ? msg : MSGTR_Chapter ), guiIntfStruct.DVD.current_chapter );
           }
          else
           {
            msg = g_filename_from_utf8( MSGTR_NoChapter, -1, NULL, NULL, NULL );
            av_strlcat( tmp, ( msg ? msg : MSGTR_NoChapter ), tmplen );
           }
          break;
#endif
#ifdef CONFIG_VCD
   case STREAMTYPE_VCD:
        msg = g_filename_from_utf8( MSGTR_VCDTrack, -1, NULL, NULL, NULL );
        snprintf( tmp, tmplen, ( msg ? msg : MSGTR_VCDTrack ), guiIntfStruct.Track );
	break;
#endif
   default:
     msg = g_filename_from_utf8( MSGTR_NoMediaOpened, -1, NULL, NULL, NULL );
     av_strlcpy( tmp, ( msg ? msg : MSGTR_NoMediaOpened ), tmplen );
  }
 g_free(msg);
 if ( c )
  {
   for ( i=0;i < (int)strlen( tmp );i++ )
    {
     int t=0;
     if ( c == 1 ) { if ( ( tmp[i] >= 'A' )&&( tmp[i] <= 'Z' ) ) t=32; }
     if ( c == 2 ) { if ( ( tmp[i] >= 'a' )&&( tmp[i] <= 'z' ) ) t=-32; }
     tmp[i]=(char)( tmp[i] + t );
    }
  }
}