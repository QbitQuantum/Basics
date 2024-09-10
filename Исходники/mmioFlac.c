FLAC__StreamDecoderWriteStatus mwrite
    (const FLAC__SeekableStreamDecoder *decoder, 
    const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
{
   Mdata *mdata = client_data;
   unsigned i,j;
   size_t newend;

   if (!mdata) { return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;} 

   newend = frame->header.blocksize*frame->header.channels*(frame->header.bits_per_sample/8);
   if (mdata->bufend < newend) {
        if (mdata->buffer) {
            free(mdata->buffer);
            mdata->buffer = 0;
        } /* endif */
        mdata->bufend=newend;
   } /* endif */

   if (!mdata->buffer) {
        mdata->buffer = malloc(mdata->bufend);
        if (!mdata->buffer) { return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;} 
   } /* endif */

#ifdef DEBUG
			fprintf(file,"callback write %ld\n",newend);
			fprintf(file,"size_t: %ld\n",sizeof(size_t));
     fprintf(file,"heap: %d\n",_heapchk());
#endif
   mdata->bufsize=0;
   for(i=0;i<frame->header.blocksize;i++) {
       for(j=0;j<frame->header.channels;j++) {
           mdata->buffer[mdata->bufsize] = (buffer[j][i] & 0xFF);
           if (mdata->bits_per_sample <= 8) {
              mdata->buffer[mdata->bufsize]+=1<<(mdata->bits_per_sample-1);
           }
           mdata->bufsize++;
           if (mdata->bits_per_sample > 8) {
               mdata->buffer[mdata->bufsize] = ((buffer[j][i] & 0xFF00) >> 8);
               mdata->bufsize++;
           } /* endif */
           if (mdata->bits_per_sample > 16) {
               mdata->buffer[mdata->bufsize] = ((buffer[j][i] & 0xFF0000) >> 8);
               mdata->bufsize++;
           } /* endif */
           if (mdata->bits_per_sample > 24) {
               mdata->buffer[mdata->bufsize] = ((buffer[j][i] & 0xFF000000) >> 8);
               mdata->bufsize++;
           } /* endif */