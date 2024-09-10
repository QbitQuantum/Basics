static NTSTATUS
XenUsb_CompleteXenbusInit(PXENUSB_DEVICE_DATA xudd) {
  PUCHAR ptr;
  USHORT type;
  PCHAR setting, value, value2;
  ULONG i;

  ptr = xudd->config_page;
  while((type = GET_XEN_INIT_RSP(&ptr, (PVOID)&setting, (PVOID)&value, (PVOID)&value2)) != XEN_INIT_TYPE_END) {
    switch(type) {
    case XEN_INIT_TYPE_RING: /* frontend ring */
      FUNCTION_MSG("XEN_INIT_TYPE_RING - %s = %p\n", setting, value);
      if (strcmp(setting, "urb-ring-ref") == 0) {
        xudd->urb_sring = (usbif_urb_sring_t *)value;
        FRONT_RING_INIT(&xudd->urb_ring, xudd->urb_sring, PAGE_SIZE);
      }
      if (strcmp(setting, "conn-ring-ref") == 0) {
        xudd->conn_sring = (usbif_conn_sring_t *)value;
        FRONT_RING_INIT(&xudd->conn_ring, xudd->conn_sring, PAGE_SIZE);
      }
      break;
    case XEN_INIT_TYPE_EVENT_CHANNEL_DPC: /* frontend event channel */
      FUNCTION_MSG("XEN_INIT_TYPE_EVENT_CHANNEL_DPC - %s = %d\n", setting, PtrToUlong(value) & 0x3FFFFFFF);
      if (strcmp(setting, "event-channel") == 0) {
        xudd->event_channel = PtrToUlong(value);
      }
      break;
    case XEN_INIT_TYPE_READ_STRING_BACK:
    case XEN_INIT_TYPE_READ_STRING_FRONT:
      FUNCTION_MSG("XEN_INIT_TYPE_READ_STRING - %s = %s\n", setting, value);
      break;
    default:
      FUNCTION_MSG("XEN_INIT_TYPE_%d\n", type);
      break;
    }
  }
  if (xudd->urb_sring == NULL || xudd->conn_sring == NULL || xudd->event_channel == 0) {
    FUNCTION_MSG("Missing settings\n");
    FUNCTION_EXIT();
    return STATUS_BAD_INITIAL_PC;
  }
  
  stack_new(&xudd->req_id_ss, REQ_ID_COUNT);
  for (i = 0; i < REQ_ID_COUNT; i++)  {
    put_id_on_freelist(xudd->req_id_ss, (uint16_t)i);
  }
  
  return STATUS_SUCCESS;
}