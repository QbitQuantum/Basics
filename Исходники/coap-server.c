error_t
parse_message(coap_packet_t* packet, u8_t* buf, u16_t size)
{
  u16_t processed = 0;
  u16_t i = 0;
  PRINTF("parse_message size %d-->\n",size);

  init_packet(packet);

  packet->ver = (buf[0] & COAP_HEADER_VERSION_MASK) >> COAP_HEADER_VERSION_POSITION;
  packet->type = (buf[0] & COAP_HEADER_TYPE_MASK) >> COAP_HEADER_TYPE_POSITION;
  packet->option_count = buf[0] & COAP_HEADER_OPTION_COUNT_MASK;
  packet->code = buf[1];
  packet->tid = (buf[2] << 8) + buf[3];

  processed += 4;

  if (packet->option_count) {
    u8_t option_index = 0;
    u8_t option_delta;
    u16_t option_len;
    u8_t* option_buf = buf + processed;
    packet->options = (header_option_t*)allocate_buffer(sizeof(header_option_t) * packet->option_count);

    if (!packet->options) {
      return MEMORY_ALLOC_ERR;
    }
    header_option_t* current_option = packet->options;
    header_option_t* prev_option = NULL;
    while ((option_index < packet->option_count) && (i <= (size - processed))) {
      option_delta = (option_buf[i] & COAP_HEADER_OPTION_DELTA_MASK)
          >> COAP_HEADER_OPTION_DELTA_POSITION;
      option_len = (option_buf[i] & COAP_HEADER_OPTION_SHORT_LENGTH_MASK);
      i++;
      if (option_len == 0xf) {
        option_len += option_buf[i];
        i++;
      }

      current_option->option = option_delta;
      current_option->len = option_len;
      current_option->value = option_buf + i;
      if (option_index) {
        prev_option->next = current_option;
        /*This field defines the difference between the option Type of
         * this option and the previous option (or zero for the first option)*/
        current_option->option += prev_option->option;
      }

      if (current_option->option == Option_Type_Uri_Path) {
        if (!packet->url) {
          /* Allocate space for url */
          packet->url = allocate_buffer(MAX_URI_PATH_LENGTH);
          if (!packet->url){
            return MEMORY_ALLOC_ERR;
          }
        } else {
          if (packet->url_len + 1 <= MAX_URI_PATH_LENGTH) {
            packet->url[packet->url_len++] = '/';
          } else {
            return MEMORY_ALLOC_ERR;
          }
        }
        if (packet->url_len + current_option->len <= MAX_URI_PATH_LENGTH) {
          strncpy(&packet->url[packet->url_len], (char*) current_option->value,
                  current_option->len);
          packet->url_len += current_option->len;
        } else {
          return MEMORY_ALLOC_ERR;
        }
      } else if (current_option->option == Option_Type_Uri_Query) {
        packet->query = (char*) current_option->value;
        packet->query_len = current_option->len;
      }

      i += option_len;
      option_index++;
      prev_option = current_option;
      if (option_index < packet->option_count) {
        /* There are still options to parse */
        current_option++;
      }
    }
    if (i > (size - processed)) {
      /* Out of bounds. Bad request? */
      return BAD_REQUEST_ERR;
    }
    current_option->next = NULL;
  }