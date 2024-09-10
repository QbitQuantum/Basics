void main(void)
{


#if 1
    /*
     *  1 Word,
     *  2 Byte,
     *  4 Kb
     *
     *  #define Bit (1)    Single Binary Digit (1 or 0)
     *  #define KB (1<<4)  Kilobyte
     *  #define MB (1<<8)  Megabyte (MB)   1,024 Kilobytes
     *  #define GB (1<<12) Gigabyte (GB)   1,024 Megabytes
     *  #define TB (1<<16) Terabyte (TB)   1,024 Gigabytes
     *  #define PB (1<<20) Petabyte (PB)   1,024 Terabytes
     *  #define EB (1<<24) Exabyte (EB)    1,024 Petabytes
     */
    #define BUFSIZE (1<<24)

    unsigned int ok, i;
    unsigned long long *rand = malloc(BUFSIZE*sizeof(unsigned long long)),
                       *seed = malloc(BUFSIZE*sizeof(unsigned long long));

    clock_t start, end, bm;
    // RDRAND (the benchmark)
    start = clock();
    for (i = 0; i < BUFSIZE; i++) {
      while (!_rdrand64_step(&rand[i]))
          ;
    }
    bm = clock() - start;
    printf("RDRAND: %li\n", bm);

    // RDSEED
    start = clock();
    for (i = 0; i < BUFSIZE; i++) {
      while (!_rdseed64_step(&seed[i]))
          ;
    }
    end = clock();
    exit(0);
#endif

    printf("Linked List Testing\n");
    // Master thread
    head = create_list(NULL,0,0);


// Choice 1: Create a server socket
    // Create a server socket.
    // Client socket will connect and update the linked list

// Choice 2:
    // Shared Memory buffer so that threads can read from the shared memory buffer.
    //

// Choice 3:
    // Message Queue Processing the linked list

}