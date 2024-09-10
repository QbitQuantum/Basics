/****************************************************************************
 * Name: ubgps_handle_aid_alpsrv
 *
 * Description:
 *   Handle AID-ALPSRV UBX message
 *
 * Input Parameters:
 *   gps         - GPS object
 *   msg         - UBX AID-ALPSRV message
 *
 * Returned Values:
 *   Status
 *
 ****************************************************************************/
int ubgps_handle_aid_alpsrv(struct ubgps_s * const gps, struct ubx_msg_s const * const msg)
{
  uint8_t requested_data_type;
  size_t data_offset;
  size_t data_size;
  ssize_t data_read;
  struct ubx_msg_s * resp = NULL;
  int alpfd = -1;
  int status = ERROR;
  int ret;

  DEBUGASSERT(gps && msg);

  if (!gps->assist)
    return OK;

  /* Check that AssistNow Offline data is available */

  ret = pthread_mutex_trylock(&g_aid_mutex);
  if (ret != 0)
    {
      dbg_int("mutex_trylock failed: %d\n", ret);
      return OK;
    }

  if (!gps->assist->alp_file || !gps->assist->alp_file_id)
    {
      pthread_mutex_unlock(&g_aid_mutex);
      return OK;
    }

  if (!ubgps_check_alp_file_validity(gps->assist->alp_file))
    {
      free(gps->assist->alp_file);
      gps->assist->alp_file = NULL;
      pthread_mutex_unlock(&g_aid_mutex);
      return OK;
    }

  requested_data_type = UBX_GET_U1(msg, 1);
  data_offset = (uint32_t)UBX_GET_U2(msg, 2) * 2;
  data_size = (uint32_t)UBX_GET_U2(msg, 4) * 2;

  dbg_int("file_id:%u, type:%u, offset:%u, size:%u\n",
      gps->assist->alp_file_id, requested_data_type, data_offset, data_size);

  /* Check if AID-ALPSRV is a download request */

  if (requested_data_type != 0xff)
    {
      /* Allocate response */

      resp = ubx_msg_allocate(UBX_CLASS_AID,
                              UBX_AID_ALPSRV,
                              UBX_AID_ALPSRV_LEN + data_size);
      if (!resp)
        goto errout;

      /* Copy original data to response */

      memcpy(&resp->payload[0], &msg->payload[0], UBX_AID_ALPSRV_LEN);

      /* Set ALP file ID */

      UBX_SET_U2(resp, 6, gps->assist->alp_file_id);
    }

  /* Open ALP file */

  alpfd = open(gps->assist->alp_file, O_RDWR);
  if (alpfd < 0)
    {
      int error = get_errno();

      dbg("ALP file '%s' open failed: %d.\n", gps->assist->alp_file, error);
      goto errout;
    }

  /* Seek to requested offset */

  status = lseek(alpfd, data_offset, SEEK_SET);
  if (status < 0)
    {
      int error = get_errno();

      dbg("Failed to seek ALP file to offset %d: %d.\n", data_offset,
          error);

      goto errout;
    }

  if (resp)
    {
      /* Read data from AlmanacPlus file */

      data_read = read(alpfd, &resp->payload[UBX_AID_ALPSRV_LEN], data_size);
      if (data_read < 0)
        {
          int error = get_errno();

          dbg("ALP file read failed (offset:%d, size:%d): %d.\n", data_offset,
              data_size, error);

          goto errout;
        }

      /* Set read data size */

      UBX_SET_U2(resp, 8, data_read);

      /* Send response */

      status = ubx_msg_send(gps, gps->fd, resp);
    }
  else
    {
      uint16_t file_id = UBX_GET_U2(msg, 6);

      /* Update data in AlmanacPlus file */

      if (file_id == gps->assist->alp_file_id)
        {
          status = write(alpfd, &msg->payload[8], data_size);
          if (status != data_size)
          {
            status = ERROR;
            dbg("ALP write failed: %d\n", get_errno());
          }
          else
          {
            status = OK;
          }
        }
    }

errout:

  if (resp)
    UBX_MSG_FREE(resp);

  if (alpfd >= 0)
    close(alpfd);

  pthread_mutex_unlock(&g_aid_mutex);

  return status;
}