// returns the last port from the trace file
uint16_t openInputTraceFile(const char *name)
{
  FILE *in = fopen(name, "r");
  TraceRecord *previous = NULL;
  uint16_t i;

  if (in == NULL) {
    fprintf(stderr, "Open \"%s\" failed.\n", name);
    exit(-1);
  }

  emReadingTrace = true;
  int result = 0;

  while (true) {
    int tag = fgetc(in);
    unsigned int length;
    TraceRecord *traceRecord = {0};
    int port;
    uint8_t addressFromFile[100] = {0};

    if (tag == EOF) {
      break;
    } else if (isspace(tag)) {
      continue;
    }

    if (fscanf(in, " %d", &port) != 1) {
      fprintf(stderr, "Failed to read port");
      exit(-1);
    }

    ASSERT(port <= 0xFFFF);

    if (fscanf(in, " %s", addressFromFile) != 1) {
      fprintf(stderr, "Failed to read address");
      exit(-1);
    }

    if (fscanf(in, " %u", &length) != 1) {
      fprintf(stderr, "Failed to read trace length.");
      exit(-1);
    }

    traceRecord = (TraceRecord *) malloc(sizeof(TraceRecord) + length);

    if (traceRecord == NULL) {
      fprintf(stderr, "Failed to allocate TraceRecord.");
      exit(-1);
    }

    traceRecord->tag = tag;
    traceRecord->previous = previous;
    traceRecord->next = NULL;
    traceRecord->length = length;
    traceRecord->port = port;

    result = traceRecord->port;

    // i don't like having an #ifdef here, but it's easier than
    // pulling in ip-address.c to the tls and pana tests
#ifdef UNIX_SCRIPTED_HOST
    stringToIpAddress(addressFromFile,
                      strlen(addressFromFile),
                      traceRecord->address);
#endif

    if (previous == NULL) {
      theTrace = traceRecord;
    } else {
      previous->next = traceRecord;
    }

    previous = traceRecord;

    for (i = 0; i < length; i++) {
      unsigned int n;
      if (fscanf(in, " %2X", &n) != 1) {
        fprintf(stderr, "Failed to read trace value.");
        exit(-1);
      }
      traceRecord->contents[i] = n;
    }
  }

  fprintf(stderr, "[Running \"%s\" ", name);
  return result;
}