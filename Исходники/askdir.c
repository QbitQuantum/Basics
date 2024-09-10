/**
 * Update File Attribute data
 * We do the following:
 *  1. expand the bsock buffer to be large enough
 *  2. Write a "header" into the buffer with serialized data
 *    VolSessionId
 *    VolSeesionTime
 *    FileIndex
 *    Stream
 *    data length that follows
 *    start of raw byte data from the Device record.
 * Note, this is primarily for Attribute data, but can
 *   also handle any device record. The Director must know
 *   the raw byte data format that is defined for each Stream.
 * Now Restore Objects pass through here STREAM_RESTORE_OBJECT
 */
bool dir_update_file_attributes(DCR *dcr, DEV_RECORD *rec)
{
   JCR *jcr = dcr->jcr;
   BSOCK *dir = jcr->dir_bsock;
   ser_declare;

#ifdef NO_ATTRIBUTES_TEST
   return true;
#endif

   dir->msg = check_pool_memory_size(dir->msg, sizeof(FileAttributes) +
                MAX_NAME_LENGTH + sizeof(DEV_RECORD) + rec->data_len + 1);
   dir->msglen = bsnprintf(dir->msg, sizeof(FileAttributes) +
                MAX_NAME_LENGTH + 1, FileAttributes, jcr->Job);
   ser_begin(dir->msg + dir->msglen, 0);
   ser_uint32(rec->VolSessionId);
   ser_uint32(rec->VolSessionTime);
   ser_int32(rec->FileIndex);
   ser_int32(rec->Stream);
   ser_uint32(rec->data_len);
   ser_bytes(rec->data, rec->data_len);
   dir->msglen = ser_length(dir->msg);
   Dmsg1(1800, ">dird %s\n", dir->msg);    /* Attributes */
   return dir->send();
}