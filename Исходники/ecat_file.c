/* ----------------------------- MNI Header -----------------------------------
@NAME       : ecat_open
@INPUT      : filename - name of file to open
@OUTPUT     : (none)
@RETURNS    : Pointer to ECAT file descriptor or NULL if an error occurs.
@DESCRIPTION: Routine to open an ECAT file (for reading only), given 
              its pathname.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    : January 4, 1996 (Peter Neelin)
@MODIFIED   : 
---------------------------------------------------------------------------- */
 Ecat_file *ecat_open(char *filename)
{
   Ecat_file *file;

   /* Allocate space for an ecat file structure */
   file = (void *) MALLOC(sizeof(*file));


   file->main_header = (void *) MALLOC(MAIN_HEADER_SIZE);
   file->subheader = (void *) MALLOC(SUBHEADER_SIZE);
   file->cur_subhdr_offset = -1;
   file->subhdr_offsets = NULL;

   /* Open the file */
   if ((file->file_pointer=fopen(filename, "rb")) == NULL) {
      ecat_close(file);
      return NULL;
   }

   /* Read in the main header */
   if (fread(file->main_header, sizeof(char), (size_t) MAIN_HEADER_SIZE, 
             file->file_pointer) != MAIN_HEADER_SIZE) {
      ecat_close(file);
      return NULL;
   }

   /* Figure out which type of file we are using */
   if (strncmp((char *)file->main_header, MAGIC_STRING, 
               strlen(MAGIC_STRING)) == 0) {
      file->header_description = ECAT_VER_7;
      file->vax_byte_order = FALSE;
   }
   else {
      file->header_description = ECAT_VER_PRE7;
      file->vax_byte_order = TRUE;
   }

   /* Get the number of frames, slices, bed positions and gates */
   if (ecat_get_main_value(file, ECAT_Num_Planes, 0, 
                           &file->num_planes, NULL, NULL) ||
       ecat_get_main_value(file, ECAT_Num_Frames, 0, 
                           &file->num_frames, NULL, NULL) ||
       ecat_get_main_value(file, ECAT_Num_Bed_Pos, 0, 
                           &file->num_bed_positions, NULL, NULL) ||
       ecat_get_main_value(file, ECAT_Num_Gates, 0, 
                           &file->num_gates, NULL, NULL)) {
      ecat_close(file);
      return NULL;
   }
   file->num_volumes = file->num_frames;
   if (file->num_volumes < file->num_bed_positions)
      file->num_volumes = file->num_bed_positions;
   if (file->num_volumes < file->num_gates)
      file->num_volumes = file->num_gates;


   /* Read the directory structure */
   if (ecat_read_directory(file)) {
      ecat_close(file);
      return NULL;
   }
   /* Return the file pointer */

   return file;
}