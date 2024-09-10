/*******************************************************************************
 * Write x number of lines of any data type to file in the data format specified
 * by the meta structure. It is always written in big endian format. Returns the
 * amount of samples successfully converted & written. Will not write more lines
 * than specified in the supplied meta struct. */
static int put_data_lines(FILE *file, meta_parameters *meta, int band_number,
                          int line_number_in_band, int num_lines_to_put,
                          const void *source, int source_data_type)
{
  int ii;               /* Sample index.                       */
  int samples_put;      /* Number of samples written           */
  size_t sample_size;   /* Sample size in bytes.               */
  void *out_buffer;     /* Buffer of converted data to write.  */
  int sample_count       = meta->general->sample_count;
  int data_type          = meta->general->data_type;
  int num_samples_to_put = num_lines_to_put * sample_count;
  int line_number        = meta->general->line_count * band_number +
                               line_number_in_band;

  if ((source_data_type>=COMPLEX_BYTE) && (data_type<=REAL64)) {
    printf("\nput_data_lines: Cannot put complex data into a simple data file. Exiting.\n\n");
    exit(EXIT_FAILURE);
  }
  if ((source_data_type<=REAL64) && (data_type>=COMPLEX_BYTE)) {
    printf("\nput_data_lines: Cannot put simple data into a complex data file. Exiting.\n\n");
    exit(EXIT_FAILURE);
  }

  // Write out all optical data as byte image.
  // They don't have a larger dynamic range than that.
  if (meta->optical)
    data_type = ASF_BYTE;

  /* Determine sample size.  */
  sample_size = data_type2sample_size(data_type);

  /* Make sure not to make file bigger than meta says it should be */
  if (line_number > meta->general->line_count * meta->general->band_count) {
    printf("\nput_data_lines: Cannot write line %d of band %d in a\n"
           "file that should be %d lines. Exiting.\n",
           line_number, band_number,
           meta->general->line_count * meta->general->band_count);
    exit(EXIT_FAILURE);
  }
  if ((line_number+num_lines_to_put) >
      meta->general->line_count * meta->general->band_count)
  {
    num_samples_to_put = (meta->general->line_count - line_number)
                          * sample_count;
  }

  FSEEK64(file, (long long)sample_size*sample_count*line_number, SEEK_SET);
  out_buffer = MALLOC( sample_size * sample_count * num_lines_to_put );

  /* Fill in destination array.  */
  switch (data_type) {
    case REAL32:
      for ( ii=0; ii<num_samples_to_put; ii++ ) {
        switch (source_data_type) {
         case ASF_BYTE:((float*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case INTEGER16:((float*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case INTEGER32:((float*)out_buffer)[ii] = ((int*)source)[ii];break;
         case REAL32:((float*)out_buffer)[ii] = ((float*)source)[ii];break;
         case REAL64:((float*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        ieee_big32( ((float*)out_buffer)[ii] );
      }
      break;
    case COMPLEX_REAL32:
      for ( ii=0; ii<num_samples_to_put*2; ii++ ) {
        switch (source_data_type) {
         case COMPLEX_BYTE:((float*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case COMPLEX_INTEGER16:((float*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case COMPLEX_INTEGER32:((float*)out_buffer)[ii] = ((int*)source)[ii];break;
         case COMPLEX_REAL32:((float*)out_buffer)[ii] = ((float*)source)[ii];break;
         case COMPLEX_REAL64:((float*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        ieee_big32( ((float*)out_buffer)[ii] );
      }
      break;
    case ASF_BYTE:
      for ( ii=0; ii<num_samples_to_put; ii++ ) {
        switch (source_data_type) {
         case ASF_BYTE:((unsigned char*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case INTEGER16:((unsigned char*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case INTEGER32:((unsigned char*)out_buffer)[ii] = ((int*)source)[ii];break;
         case REAL32:((unsigned char*)out_buffer)[ii] = ((float*)source)[ii];break;
         case REAL64:((unsigned char*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
      }
      break;
    case INTEGER16:
      for ( ii=0; ii<num_samples_to_put; ii++ ) {
        switch (source_data_type) {
         case ASF_BYTE:((short int*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case INTEGER16:((short int*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case INTEGER32:((short int*)out_buffer)[ii] = ((int*)source)[ii];break;
         case REAL32:((short int*)out_buffer)[ii] = ((float*)source)[ii];break;
         case REAL64:((short int*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        big16( ((short int*)out_buffer)[ii] );
      }
      break;
    case INTEGER32:
      for ( ii=0; ii<num_samples_to_put; ii++ ) {
        switch (source_data_type) {
         case ASF_BYTE:((int*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case INTEGER16:((int*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case INTEGER32:((int*)out_buffer)[ii] = ((int*)source)[ii];break;
         case REAL32:((int*)out_buffer)[ii] = ((float*)source)[ii];break;
         case REAL64:((int*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        big32( ((int*)out_buffer)[ii] );
      }
      break;
    case REAL64:
      for ( ii=0; ii<num_samples_to_put; ii++ ) {
        switch (source_data_type) {
         case ASF_BYTE:((double*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case INTEGER16:((double*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case INTEGER32:((double*)out_buffer)[ii] = ((int*)source)[ii];break;
         case REAL32:((double*)out_buffer)[ii] = ((float*)source)[ii];break;
         case REAL64:((double*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        ieee_big64( ((double*)out_buffer)[ii] );
      }
      break;
    case COMPLEX_BYTE:
      for ( ii=0; ii<num_samples_to_put*2; ii++ )
        switch (source_data_type) {
         case COMPLEX_BYTE:((unsigned char*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case COMPLEX_INTEGER16:((unsigned char*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case COMPLEX_INTEGER32:((unsigned char*)out_buffer)[ii] = ((int*)source)[ii];break;
         case COMPLEX_REAL32:((unsigned char*)out_buffer)[ii] = ((float*)source)[ii];break;
         case COMPLEX_REAL64:((unsigned char*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
     break;
    case COMPLEX_INTEGER16:
      for ( ii=0; ii<num_samples_to_put*2; ii++ ) {
        switch (source_data_type) {
         case COMPLEX_BYTE:((short int*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case COMPLEX_INTEGER16:((short int*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case COMPLEX_INTEGER32:((short int*)out_buffer)[ii] = ((int*)source)[ii];break;
         case COMPLEX_REAL32:((short int*)out_buffer)[ii] = ((float*)source)[ii];break;
         case COMPLEX_REAL64:((short int*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        big16( ((short int*)out_buffer)[ii] );
      }
      break;
    case COMPLEX_INTEGER32:
      for ( ii=0; ii<num_samples_to_put*2; ii++ ) {
        switch (source_data_type) {
         case COMPLEX_BYTE:((int*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case COMPLEX_INTEGER16:((int*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case COMPLEX_INTEGER32:((int*)out_buffer)[ii] = ((int*)source)[ii];break;
         case COMPLEX_REAL32:((int*)out_buffer)[ii] = ((float*)source)[ii];break;
         case COMPLEX_REAL64:((int*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        big32( ((int*)out_buffer)[ii] );
      }
      break;
    case COMPLEX_REAL64:
      for ( ii=0; ii<num_samples_to_put*2; ii++ ) {
        switch (source_data_type) {
         case COMPLEX_BYTE:((double*)out_buffer)[ii] = ((unsigned char*)source)[ii];break;
         case COMPLEX_INTEGER16:((double*)out_buffer)[ii] = ((short int*)source)[ii];break;
         case COMPLEX_INTEGER32:((double*)out_buffer)[ii] = ((int*)source)[ii];break;
         case COMPLEX_REAL32:((double*)out_buffer)[ii] = ((float*)source)[ii];break;
         case COMPLEX_REAL64:((double*)out_buffer)[ii] = ((double*)source)[ii];break;
        }
        ieee_big64( ((double*)out_buffer)[ii] );
      }
      break;
  }
  samples_put = FWRITE(out_buffer, sample_size, num_samples_to_put, file);
  FREE(out_buffer);

  if ( samples_put != num_samples_to_put ) {
    printf("put_data_lines: failed to write the correct number of samples\n");
  }

  return samples_put;
}