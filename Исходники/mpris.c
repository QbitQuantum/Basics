static void sendTrackStatus(int property_list) {
  if (HAS_TITLE(property_list) && mpris_data->title != NULL) {
    debug("sending title\n");
    transmitMsg(client_socket, pathFromUrl(mpris_data->title),
                strlen(pathFromUrl(mpris_data->title)),
                TRACK_TITLE, TRACK_TITLE_SZ);
  }
  if (HAS_ARTIST(property_list) && mpris_data->artist != NULL) {
    debug("sending artist\n");
    transmitMsg(client_socket, mpris_data->artist, strlen(mpris_data->artist),
                TRACK_ARTIST, TRACK_ARTIST_SZ);
  }
  if (HAS_ALBUM(property_list) && mpris_data->album != NULL) {
    debug("sending album\n");
    transmitMsg(client_socket, mpris_data->album, strlen(mpris_data->album),
                TRACK_ALBUM, TRACK_ALBUM_SZ);
  }
  if (HAS_LENGTH(property_list)) {
    int64_t length = htobe64(mpris_data->length);
    debug("sending length : %ld\n", mpris_data->length);
    transmitMsg(client_socket, (char *)&length, sizeof(int64_t),
                TRACK_LENGTH, TRACK_LENGTH_SZ);
  }
  if (HAS_TRACKID(property_list) && mpris_data->trackid != NULL) {
    debug("sending trackid : %s\n", mpris_data->trackid);
    transmitMsg(client_socket, mpris_data->trackid, strlen(mpris_data->trackid),
                TRACK_ID, TRACK_ID_SZ);
  }
  if (HAS_ARTURL(property_list) && mpris_data->artUrl != NULL) {
    debug("sending arturl\n");
    transmit(client_socket, TRACK_ARTURL, TRACK_ARTURL_SZ);
    transmitFile(client_socket, pathFromUrl(mpris_data->artUrl));
  }
}