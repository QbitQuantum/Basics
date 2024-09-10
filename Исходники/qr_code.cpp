int main(int argc, char *argv[])
{
  AmConfig *config = new AmConfig();
  int enable_send_ipaddr = 0;
  unsigned short server_msg_port = 4848;//hard default code here
  unsigned short local_msg_port = 8484;//hard default code here
  int i = 0;
  int dgram_socket = -1;
  struct sockaddr_in dest_addr;
  int get_url = 0;
  char server_ip_addr_buffer[64] = {0};
  char local_ip_addr_buffer[INET6_ADDRSTRLEN + 4] = {0};//plus 4 for safe
  char local_rtsp_url_buffer[128] = {0};

  //If you have different config, please set it here
  config->set_vin_config_path(SIMPLE_CAM_VIN_CONFIG);
  //config->set_vout_config_path    (vout_config_path);
  //config->set_vdevice_config_path (vdevice_config_path);
  //config->set_record_config_path  (record_config_path);

  //simple check arguments
  if (argc > 1) {
    for (i = 0; i < argc; ++ i) {
      if (!strcmp("--enable-msgport", argv[i])) {
        enable_send_ipaddr = 1;
        fprintf(stdout, "\tparams: enable msg port.\n");
      } else if (!strcmp("--msgport", argv[i])) {
        ++ i;
        server_msg_port = atoi(argv[i]);
        fprintf(stdout, "\tparams: msg port %hu.\n", server_msg_port);
      } else if (!strcmp("--localmsgport", argv[i])) {
        ++ i;
        local_msg_port = atoi(argv[i]);
        fprintf(stdout, "\tparams: local msg port %hu.\n", local_msg_port);
      }
    }
  }

  if (config && config->load_vdev_config()) {
    VDeviceParameters *vdevConfig = config->vdevice_config();
    YBufferFormat yBuffer = {0};
    ImageScanner zbarScanner;
    int retVal = 0;
    int count = 0;

    if (vdevConfig) {
      AmSimpleCam simplecam(vdevConfig);
      for (uint32_t i = 0; i < vdevConfig->vin_number; ++ i) {
        simplecam.set_vin_config(config->vin_config(i), i);
      }
      for (uint32_t i = 0; i < vdevConfig->vout_number; ++ i) {
        simplecam.set_vout_config(config->vout_config(i), i);
      }
      simplecam.set_encoder_config(config->encoder_config());
      for (uint32_t i = 0; i < vdevConfig->stream_number; ++ i) {
        simplecam.set_stream_config(config->stream_config(i), i);
      }
      do {
        if (simplecam.get_y_data(&yBuffer)) {
          Image image(yBuffer.y_width, yBuffer.y_height, "Y800",
                      yBuffer.y_addr, yBuffer.y_width * yBuffer.y_height);
          if (AM_LIKELY((retVal = zbarScanner.scan(image)) > 0)) {
            for (Image::SymbolIterator symbol = image.symbol_begin();
                 symbol != image.symbol_end(); ++ symbol) {
              fprintf(stdout, "\n%s\n\n", symbol->get_data().c_str());
              if (enable_send_ipaddr) {
                get_url = 1;
                strncpy(server_ip_addr_buffer, symbol->get_data().c_str(),
                        sizeof(server_ip_addr_buffer) - 1);
                server_ip_addr_buffer[sizeof(server_ip_addr_buffer) - 1] = 0x0;
              }
            }
          } else if (retVal == 0) {
            NOTICE("No symbold found!");
          } else if (retVal < 0) {
            ERROR("Zbar scan error!");
          }
        } else {
          ERROR("Failed to get Y data!");
        }
        ++ count;
      } while ((retVal <= 0) && (count < 20));
      if (count >= 20) {
        ERROR("Failed to resolve symbol!");
      }
    } else {
      ERROR("Faild to get VideoDevice's configurations!");
    }
    delete config;
  } else {
    ERROR("Failed to load configurations!");
  }

  //parse host ipaddress, and port, have
  if (enable_send_ipaddr && get_url) {
    dgram_socket = _setup_datagram_socket(INADDR_ANY, local_msg_port, false);
    if (_build_addr_from_url(&dest_addr, server_ip_addr_buffer,
                             server_msg_port) < 0) {
      ERROR("build addr fail, url %s\n", server_ip_addr_buffer);
    } else {
      //send rtsp url to server
      _get_local_ip_address(local_ip_addr_buffer);
      _buildup_rtsp_url(local_ip_addr_buffer, local_rtsp_url_buffer,
                        sizeof(local_rtsp_url_buffer) - 1, "stream1+stream2");
      _post_msg_to_server(local_rtsp_url_buffer, &dest_addr, dgram_socket);
    }
    if (dgram_socket >= 0) {
      close(dgram_socket);
    }
  }

  return 0;
}