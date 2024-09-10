static void file_stdio_fclearerr(ALLEGRO_FILE *f)
{
   USERDATA *userdata = get_userdata(f);

   clearerr(userdata->fp);
}