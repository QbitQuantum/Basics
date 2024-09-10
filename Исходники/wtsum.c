int __cdecl main(int argc, char *argv[]) {
#define N_FRAME 100
#define N_PATCH 600000//(1<<LFSR_SIZE)
  const char* readfn = "\\\\.\\xillybus_rd"
	  , * writefn = "\\\\.\\xillybus_wr";
  HANDLE tid[2];
  struct xillyfifo fifo;
  unsigned int fifo_size = 4096*16;
  int write_fd, bTalk2FPGA = (int)(argc < 2);
  unsigned int n_frame = 0;
  unsigned int msg, n_msg;
  int rd;
  FILE* pixel_coeff_f = fopen("reducer_coeff_0.bin", "rb")
    , *ds_coeff_f = fopen("ds_0.bin", "rb");
  if(!pixel_coeff_f) {
    perror("Failed to open reducer_coeff");
    exit(errno);
  }
  if(!ds_coeff_f) {
    perror("Failed to open ds_coeff");
    exit(errno);
  }

  if(bTalk2FPGA) {
    //printf("Press any key to connect to FPGA\n"); getchar();
    write_fd = _open(writefn, O_WRONLY | _O_BINARY);
    if (write_fd < 0) {
      if (errno == ENODEV)
        fprintf(stderr, "(Maybe %s a write-only file?)\n", writefn);

      fprintf(stderr, "Failed to open %s", writefn);
      exit(1);
    }

    // If more than one FIFO is created, use the total memory needed instead
    // of fifo_size with SetProcessWorkingSetSize()
    if(fifo_size > 20000
      && !SetProcessWorkingSetSize(GetCurrentProcess()
            , 1024*1024 + fifo_size, 2048*1024 + fifo_size))
      errorprint("Failed to enlarge unswappable RAM limit", GetLastError());

    if (fifo_init(&fifo, fifo_size)) {
      perror("Failed to init");
      exit(1);
    }

    read_fd = _open(readfn, O_RDONLY | _O_BINARY);
    if (read_fd < 0) {
      perror("Failed to open read file");
      exit(1);
    }

    if (_setmode(1, _O_BINARY) < 0)
      fprintf(stderr, "Failed to set binary mode for standard output\n");

    // default security, default stack size, default startup flags
    tid[0] = CreateThread(NULL, 0, read_thread, &fifo, 0, NULL);
    if (tid[0] == NULL) {
      errorprint("Failed to create read thread", GetLastError());
      exit(1);
    }
    tid[1] = CreateThread(NULL, 0, report_thread, &fifo, 0, NULL);
    if (tid[1] == NULL) {
      errorprint("Failed to create report thread", GetLastError());
      exit(1);
    }
  }//end if(bTalk2FPGA)

  for(n_msg = 0; !feof(pixel_coeff_f); ) {
    rd = fread(&msg, sizeof(msg), 1, pixel_coeff_f);
    if(bTalk2FPGA) allwrite(write_fd, (unsigned char*)&msg, sizeof(msg));
    printf("weights 0x%08X\n", msg);
  } //end for

  for(; !feof(ds_coeff_f); ) {
    rd = fread(&msg, sizeof(msg), 1, ds_coeff_f);
    printf("DS 0x%08X\n", msg);
    if(bTalk2FPGA) allwrite(write_fd, (unsigned char*)&msg, sizeof(msg));
  } //end for

cleanup:
  if(bTalk2FPGA) {
    unsigned int msg = ~0;//Make the FPGA close the rd file
    allwrite(write_fd, (unsigned char*)&msg, sizeof(msg));
    _close(write_fd);
    _close(read_fd);

    // Wait for threads to exit
    if (WaitForSingleObject(tid[0], INFINITE) != WAIT_OBJECT_0) 
      errorprint("Failed waiting for read_thread to terminate"
        , GetLastError());
    fifo_destroy(&fifo);
  }
  fclose(ds_coeff_f);
  fclose(pixel_coeff_f);
  printf("Press any key to exit\n"); getchar();
  return 0;
}