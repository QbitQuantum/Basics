/**
 * Does a source file.
 *
 * @param filename_in  the file to read
 * @param filename_out NULL (stdout) or the file to write
 * @param parsed_file  NULL or the filename for the parsed debug info
 * @param no_backup    don't create a backup, if filename_out == filename_in
 * @param keep_mtime   don't change the mtime (dangerous)
 */
static void do_source_file(const char *filename_in,
                           const char *filename_out,
                           const char *parsed_file,
                           bool       no_backup,
                           bool       keep_mtime)
{
   FILE     *pfout;
   bool     did_open    = false;
   bool     need_backup = false;
   file_mem fm;
   string   filename_tmp;

   /* Do some simple language detection based on the filename extension */
   if (!cpd.lang_forced || (cpd.lang_flags == 0))
   {
      cpd.lang_flags = language_from_filename(filename_in);
   }

   /* Try to read in the source file */
   if (load_mem_file(filename_in, fm) < 0)
   {
      LOG_FMT(LERR, "Failed to load (%s)\n", filename_in);
      cpd.error_count++;
      return;
   }

   LOG_FMT(LSYS, "Parsing: %s as language %s\n",
           filename_in, language_to_string(cpd.lang_flags));

   if (filename_out == NULL)
   {
      pfout = stdout;
   }
   else
   {
      /* If the out file is the same as the in file, then use a temp file */
      filename_tmp = filename_out;
      if (strcmp(filename_in, filename_out) == 0)
      {
         /* Create 'outfile.uncrustify' */
         filename_tmp = fix_filename(filename_out);

         if (!no_backup)
         {
            if (backup_copy_file(filename_in, fm.raw) != SUCCESS)
            {
               LOG_FMT(LERR, "%s: Failed to create backup file for %s\n",
                       __func__, filename_in);
               cpd.error_count++;
               return;
            }
            need_backup = true;
         }
      }
      make_folders(filename_tmp);

      pfout = fopen(filename_tmp.c_str(), "wb");
      if (pfout == NULL)
      {
         LOG_FMT(LERR, "%s: Unable to create %s: %s (%d)\n",
                 __func__, filename_tmp.c_str(), strerror(errno), errno);
         cpd.error_count++;
         return;
      }
      did_open = true;
      //LOG_FMT(LSYS, "Output file %s\n", filename_out);
   }

   cpd.filename = filename_in;
   uncrustify_file(fm, pfout, parsed_file);

   if (did_open)
   {
      fclose(pfout);

      if (need_backup)
      {
         backup_create_md5_file(filename_in);
      }

      if (filename_tmp != filename_out)
      {
         /* We need to compare and then do a rename */
         if (file_content_matches(filename_tmp, filename_out))
         {
            /* No change - remove tmp file */
            (void)unlink(filename_tmp.c_str());
         }
         else
         {
#ifdef WIN32

            /* windows can't rename a file if the target exists, so delete it
             * first. This may cause data loss if the tmp file gets deleted
             * or can't be renamed.
             */
            (void)unlink(filename_out);
#endif
            /* Change - rename filename_tmp to filename_out */
            if (rename(filename_tmp.c_str(), filename_out) != 0)
            {
               LOG_FMT(LERR, "%s: Unable to rename '%s' to '%s'\n",
                       __func__, filename_tmp.c_str(), filename_out);
               cpd.error_count++;
            }
         }
      }

#ifdef HAVE_UTIME_H
      if (keep_mtime)
      {
         /* update mtime -- don't care if it fails */
         fm.utb.actime = time(NULL);
         (void)utime(filename_in, &fm.utb);
      }
#endif
   }
}