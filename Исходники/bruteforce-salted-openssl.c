int main(int argc, char **argv)
{
  pthread_t *decryption_threads;
  char *filename;
  int fd, i, ret, c;
  struct stat file_stats;

  setlocale(LC_ALL, "");
  OpenSSL_add_all_algorithms();

  /* Get options and parameters */
  opterr = 0;
  while((c = getopt(argc, argv, "1aB:b:c:d:e:f:hL:l:M:m:Nns:t:v:w:")) != -1)
    switch(c)
    {
    case '1':
      only_one_password = 1;
      break;

    case 'a':
      list_algorithms();
      exit(EXIT_FAILURE);
      break;

    case 'B':
      binary = optarg;
      break;

    case 'b':
      prefix_len = mbstowcs(NULL, optarg, 0);
      if(prefix_len == (unsigned int) -1)
      {
        fprintf(stderr, "Error: invalid character in prefix.\n\n");
        exit(EXIT_FAILURE);
      }
      prefix = (wchar_t *) calloc(prefix_len + 1, sizeof(wchar_t));
      if(prefix == NULL)
      {
        fprintf(stderr, "Error: memory allocation failed.\n\n");
        exit(EXIT_FAILURE);
      }
      mbstowcs(prefix, optarg, prefix_len + 1);
      break;

    case 'c':
      cipher = EVP_get_cipherbyname(optarg);
      if(cipher == NULL)
      {
        fprintf(stderr, "Error: unknown cipher: %s.\n\n", optarg);
        exit(EXIT_FAILURE);
      }
      break;

    case 'd':
      digest = EVP_get_digestbyname(optarg);
      if(digest == NULL)
      {
        fprintf(stderr, "Error: unknown digest: %s.\n\n", optarg);
        exit(EXIT_FAILURE);
      }
      break;

    case 'e':
      suffix_len = mbstowcs(NULL, optarg, 0);
      if(suffix_len == (unsigned int) -1)
      {
        fprintf(stderr, "Error: invalid character in suffix.\n\n");
        exit(EXIT_FAILURE);
      }
      suffix = (wchar_t *) calloc(suffix_len + 1, sizeof(wchar_t));
      if(suffix == NULL)
      {
        fprintf(stderr, "Error: memory allocation failed.\n\n");
        exit(EXIT_FAILURE);
      }
      mbstowcs(suffix, optarg, suffix_len + 1);
      break;

    case 'f':
      dictionary = fopen(optarg, "r");
      if(dictionary == NULL)
      {
        fprintf(stderr, "Error: can't open dictionary file.\n\n");
        exit(EXIT_FAILURE);
      }
      break;

    case 'h':
      usage(argv[0]);
      exit(EXIT_FAILURE);
      break;

    case 'L':
      limit = (long unsigned int) atol(optarg);
      break;

    case 'l':
      min_len = (unsigned int) atoi(optarg);
      break;

    case 'M':
      magic = optarg;
      break;

    case 'm':
      max_len = (unsigned int) atoi(optarg);
      break;

    case 'N':
      no_error = 1;
      break;

    case 'n':
      no_salt = 1;
      break;

    case 's':
      charset_len = mbstowcs(NULL, optarg, 0);
      if(charset_len == 0)
      {
        fprintf(stderr, "Error: charset must have at least one character.\n\n");
        exit(EXIT_FAILURE);
      }
      if(charset_len == (unsigned int) -1)
      {
        fprintf(stderr, "Error: invalid character in charset.\n\n");
        exit(EXIT_FAILURE);
      }
      charset = (wchar_t *) calloc(charset_len + 1, sizeof(wchar_t));
      if(charset == NULL)
      {
        fprintf(stderr, "Error: memory allocation failed.\n\n");
        exit(EXIT_FAILURE);
      }
      mbstowcs(charset, optarg, charset_len + 1);
      break;

    case 't':
      nb_threads = (unsigned int) atoi(optarg);
      if(nb_threads == 0)
        nb_threads = 1;
      break;

    case 'v':
      status_interval = (unsigned int) atoi(optarg);
      break;

    case 'w':
      state_file = optarg;
      break;

    default:
      usage(argv[0]);
      switch(optopt)
      {
      case 'B':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'L':
      case 'l':
      case 'M':
      case 'm':
      case 's':
      case 't':
      case 'v':
      case 'w':
        fprintf(stderr, "Error: missing argument for option: '-%c'.\n\n", optopt);
        break;

      default:
        fprintf(stderr, "Error: unknown option: '%c'.\n\n", optopt);
        break;
      }
      exit(EXIT_FAILURE);
      break;
    }

  if(optind >= argc)
  {
    usage(argv[0]);
    fprintf(stderr, "Error: missing filename.\n\n");
    exit(EXIT_FAILURE);
  }

  filename = argv[optind];

  /* Check variables */
  if(cipher == NULL)
    cipher = EVP_aes_256_cbc();
  if(digest == NULL)
    digest = EVP_md5();
  if(dictionary != NULL)
  {
    fprintf(stderr, "Warning: using dictionary mode, ignoring options -b, -e, -l, -m and -s.\n\n");
  }
  else
  {
    if(prefix == NULL)
    {
      prefix_len = mbstowcs(NULL, "", 0);
      prefix = (wchar_t *) calloc(prefix_len + 1, sizeof(wchar_t));
      if(prefix == NULL)
      {
        fprintf(stderr, "Error: memory allocation failed.\n\n");
        exit(EXIT_FAILURE);
      }
      mbstowcs(prefix, "", prefix_len + 1);
    }
    if(suffix == NULL)
    {
      suffix_len = mbstowcs(NULL, "", 0);
      suffix = (wchar_t *) calloc(suffix_len + 1, sizeof(wchar_t));
      if(suffix == NULL)
      {
        fprintf(stderr, "Error: memory allocation failed.\n\n");
        exit(EXIT_FAILURE);
      }
      mbstowcs(suffix, "", suffix_len + 1);
    }
    if(charset && binary)
    {
      fprintf(stderr, "Error: options -B and -s can't be both set.\n\n");
      exit(EXIT_FAILURE);
    }
    else if(binary)
    {
      charset_len = strlen(binary_charset);
      prefix_len = wcstombs(NULL, prefix, 0);
      suffix_len = wcstombs(NULL, suffix, 0);
    }
    else if(charset == NULL)
    {
      charset_len = mbstowcs(NULL, default_charset, 0);
      charset = (wchar_t *) calloc(charset_len + 1, sizeof(wchar_t));
      if(charset == NULL)
      {
        fprintf(stderr, "Error: memory allocation failed.\n\n");
        exit(EXIT_FAILURE);
      }
      mbstowcs(charset, default_charset, charset_len + 1);
    }
    if(charset_len == 0)
    {
      fprintf(stderr, "Error: charset must have at least one character.\n\n");
      exit(EXIT_FAILURE);
    }
    if(min_len < prefix_len + suffix_len + 1)
    {
      fprintf(stderr, "Warning: minimum length (%u) isn't bigger than the length of specified password characters (%u). Setting minimum length to %u.\n\n", min_len, prefix_len + suffix_len, prefix_len + suffix_len + 1);
      min_len = prefix_len + suffix_len + 1;
    }
    if(max_len < min_len)
    {
      fprintf(stderr, "Warning: maximum length (%u) is smaller than minimum length (%u). Setting maximum length to %u.\n\n", max_len, min_len, min_len);
      max_len = min_len;
    }
  }

  last_pass[0] = '\0';

  /* Check header */
  fd = open(filename, O_RDONLY);
  if(fd == -1)
  {
    perror("open file");
    exit(EXIT_FAILURE);
  }
  if(no_salt == 0)
  {
    memset(salt, 0, sizeof(salt));
    ret = read(fd, salt, 8);
    if(strncmp(salt, "Salted__", 8) != 0)
    {
      close(fd);
      fprintf(stderr, "Error: %s is not a salted openssl file.\n\n", filename);
      exit(EXIT_FAILURE);
    }

    /* Read salt */
    ret = read(fd, salt, 8);
    if(ret != 8)
    {
      close(fd);
      fprintf(stderr, "Error: could not read salt.\n\n");
      exit(EXIT_FAILURE);
    }
  }

  /* Read encrypted data */
  ret = fstat(fd, &file_stats);
  if(no_salt)
    data_len = file_stats.st_size;
  else
    data_len = file_stats.st_size - 16;
  data = (char *) malloc(data_len);
  if(data == NULL)
  {
    fprintf(stderr, "Error: memory allocation failed.\n\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < data_len;)
  {
    ret = read(fd, data + i, data_len - i);
    if(ret == -1)
    {
      close(fd);
      fprintf(stderr, "Error: could not read data.\n\n");
      exit(EXIT_FAILURE);
    }
    else if(ret > 0)
      i += ret;
  }
  close(fd);

  signal(SIGUSR1, handle_signal);
  if(status_interval > 0)
  {
    signal(SIGALRM, handle_signal);
    progress_timer.it_value.tv_sec = status_interval;
    progress_timer.it_value.tv_usec = 0;
    progress_timer.it_interval.tv_sec = status_interval;
    progress_timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &progress_timer, NULL);
  }

  pthread_mutex_init(&found_password_lock, NULL);
  pthread_mutex_init(&get_password_lock, NULL);
  
  decryption_threads = (pthread_t *) malloc(nb_threads * sizeof(pthread_t));
  thread_locals = (struct decryption_func_locals *) calloc(nb_threads, sizeof(struct decryption_func_locals));
  if((decryption_threads == NULL) || (thread_locals == NULL))
  {
    fprintf(stderr, "Error: memory allocation failed.\n\n");
    exit(EXIT_FAILURE);
  }

  start_time = time(NULL);

  if(state_file != NULL)
  {
    restore_state();

    signal(SIGVTALRM, save_state);
    state_timer.it_value.tv_sec = 60 * nb_threads;
    state_timer.it_value.tv_usec = 0;
    state_timer.it_interval.tv_sec = 60 * nb_threads;
    state_timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &state_timer, NULL);
  }

  /* Start decryption threads */
  for(i = 0; i < nb_threads; i++)
  {
    ret = pthread_create(&decryption_threads[i], NULL, &decryption_func, &thread_locals[i]);
    if(ret != 0)
    {
      perror("Error: decryption thread");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 0; i < nb_threads; i++)
  {
    pthread_join(decryption_threads[i], NULL);
  }
  if(found_password == 0)
  {
    handle_signal(SIGUSR1); /* Print some stats */
    fprintf(stderr, "Password not found\n");
  }

  free(thread_locals);
  free(decryption_threads);
  pthread_mutex_destroy(&found_password_lock);
  pthread_mutex_destroy(&get_password_lock);
  free(data);
  EVP_cleanup();

  exit(EXIT_SUCCESS);
}