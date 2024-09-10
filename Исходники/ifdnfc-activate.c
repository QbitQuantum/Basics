int
main(int argc, char *argv[])
{
  LONG rv;
  SCARDCONTEXT hContext;
  SCARDHANDLE hCard;
  char *reader;
  BYTE pbSendBuffer[1 + 1 + sizeof(nfc_connstring)];
  DWORD dwSendLength;
  BYTE pbRecvBuffer[1];
  DWORD dwActiveProtocol, dwRecvLength, dwReaders;
  char* mszReaders = NULL;

  if (argc == 1 ||
      (argc == 2 && (strncmp(argv[1], "yes", strlen("yes")) == 0)))
    pbSendBuffer[0] = IFDNFC_SET_ACTIVE;
  else if (argc == 2 && (strncmp(argv[1], "no", strlen("no")) == 0))
    pbSendBuffer[0] = IFDNFC_SET_INACTIVE;
  else if (argc == 2 && (strncmp(argv[1], "se", strlen("se")) == 0))
    pbSendBuffer[0] = IFDNFC_SET_ACTIVE_SE;
  else if (argc == 2 && (strncmp(argv[1], "status", strlen("status")) == 0))
    pbSendBuffer[0] = IFDNFC_GET_STATUS;
  else {
    printf("Usage: %s [yes|no|status]\n", argv[0]);
    exit(EXIT_FAILURE);
  }


  rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
  if (rv < 0)
    goto pcsc_error;

  dwReaders = 0;
  // Ask how many bytes readers list take
  rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
  if (rv < 0)
    goto pcsc_error;
  // Then allocate and fill mszReaders
  mszReaders = malloc(dwReaders);
  rv = SCardListReaders(hContext, NULL, mszReaders, &dwReaders);
  if (rv < 0)
    goto pcsc_error;

  int l;
  for (reader = mszReaders;
       dwReaders > 0;
       l = strlen(reader) + 1, dwReaders -= l, reader += l) {
    if (strcmp(IFDNFC_READER_NAME, reader) <= 0)
      break;
  }
  if (dwReaders <= 0) {
    printf("Could not find a reader named: %s\n", IFDNFC_READER_NAME);
    rv = SCARD_E_NO_READERS_AVAILABLE;
    goto pcsc_error;
  }

  // TODO Handle multiple ifdnfc instance for multiple NFC device ?
  rv = SCardConnect(hContext, reader, SCARD_SHARE_DIRECT, 0, &hCard,
                    &dwActiveProtocol);
  if (rv < 0)
    goto pcsc_error;

  if ((pbSendBuffer[0] == IFDNFC_SET_ACTIVE) || (pbSendBuffer[0] == IFDNFC_SET_ACTIVE_SE))  {
    const BYTE command = pbSendBuffer[0];
    // To correctly probe NFC devices, ifdnfc must be disactivated first
    pbSendBuffer[0] = IFDNFC_SET_INACTIVE;
    dwSendLength = 1;
    rv = SCardControl(hCard, IFDNFC_CTRL_ACTIVE, pbSendBuffer,
                      dwSendLength, pbRecvBuffer, sizeof(pbRecvBuffer),
                      &dwRecvLength);
    if (rv < 0) {
      goto pcsc_error;
    }

    pbSendBuffer[0] = command;
    // Initialize libnfc
    nfc_context *context;
    nfc_init(&context);
    if (context == NULL) {
      fprintf(stderr, "Unable to init libnfc (malloc)\n");
      goto error;
    }
    // Allocate nfc_connstring array
    nfc_connstring connstrings[MAX_DEVICE_COUNT];
    // List devices
    size_t szDeviceFound = nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);

    int connstring_index = -1;
    switch (szDeviceFound) {
      case 0:
        fprintf(stderr, "Unable to activate ifdnfc: no NFC device found.\n");
        nfc_exit(context);
        goto error;
        break;
      case 1:
        // Only one NFC device available, so auto-select it!
        connstring_index = 0;
        break;
      default:
        // More than one available NFC devices, propose a shell menu:
        printf("%d NFC devices found, please select one:\n", (int)szDeviceFound);
        for (size_t i = 0; i < szDeviceFound; i++) {
          nfc_device *pnd = nfc_open(context, connstrings[i]);
          if (pnd != NULL) {
            printf("[%d] %s\t  (%s)\n", (int)i, nfc_device_get_name(pnd), nfc_device_get_connstring(pnd));
            nfc_close(pnd);
          } else {
            fprintf(stderr, "nfc_open failed for %s\n", connstrings[i]);
          }
        }
        // libnfc isn't needed anymore
        nfc_exit(context);
        printf(">> ");
        // Take user's choice
        if (1 != scanf("%2d", &connstring_index)) {
          fprintf(stderr, "Value must an integer.\n");
          goto error;
        }
        if ((connstring_index < 0) || (connstring_index >= (int)szDeviceFound)) {
          fprintf(stderr, "Invalid index selection.\n");
          goto error;
        }
        break;
    }
    printf("Activating ifdnfc with \"%s\"...\n", connstrings[connstring_index]);
    // pbSendBuffer = { IFDNFC_SET_ACTIVE (1 byte), length (2 bytes), nfc_connstring (lenght bytes)}
    const uint16_t u16ConnstringLength = strlen(connstrings[connstring_index]) + 1;
    memcpy(pbSendBuffer + 1, &u16ConnstringLength, sizeof(u16ConnstringLength));
    memcpy(pbSendBuffer + 1 + sizeof(u16ConnstringLength), connstrings[connstring_index], u16ConnstringLength);
    dwSendLength = 1 + sizeof(u16ConnstringLength) + u16ConnstringLength;
  } else {
    // pbSendBuffer[0] != IFDNFC_SET_ACTIVE
    dwSendLength = 1;
  }

  rv = SCardControl(hCard, IFDNFC_CTRL_ACTIVE, pbSendBuffer,
                    dwSendLength, pbRecvBuffer, sizeof(pbRecvBuffer),
                    &dwRecvLength);
  if (rv < 0) {
    goto pcsc_error;
  }
  if (dwRecvLength < 1) {
    rv = SCARD_F_INTERNAL_ERROR;
    goto pcsc_error;
  }

  switch (pbRecvBuffer[0]) {
    case IFDNFC_IS_ACTIVE: {
      uint16_t u16ConnstringLength;
      if (dwRecvLength < (1 + sizeof(u16ConnstringLength))) {
        rv = SCARD_F_INTERNAL_ERROR;
        goto pcsc_error;
      }
      memcpy(&u16ConnstringLength, pbRecvBuffer + 1, sizeof(u16ConnstringLength));
      if ((dwRecvLength - (1 + sizeof(u16ConnstringLength))) != u16ConnstringLength) {
        rv = SCARD_F_INTERNAL_ERROR;
        goto pcsc_error;
      }
      nfc_connstring connstring;
      memcpy(connstring, pbRecvBuffer + 1 + sizeof(u16ConnstringLength), u16ConnstringLength);
      printf("%s is active using %s.\n", IFDNFC_READER_NAME, connstring);
    }
    break;
    case IFDNFC_IS_INACTIVE:
      printf("%s is inactive.\n", IFDNFC_READER_NAME);
      break;
    default:
      rv = SCARD_F_INTERNAL_ERROR;
      goto pcsc_error;
  }


  rv = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
  if (rv < 0)
    goto pcsc_error;

  free(mszReaders);

  exit(EXIT_SUCCESS);

pcsc_error:
  puts(pcsc_stringify_error(rv));
error:
  if (mszReaders)
    free(mszReaders);

  exit(EXIT_FAILURE);
}