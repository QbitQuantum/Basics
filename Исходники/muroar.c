// Open Control connection
muroar_t muroar_connect(const char * server, const char * name) {
 char   useraddr[80] = MUROAR_INVALID;
 char * addr[] = {useraddr, MUROAR_GSOCK, MUROAR_HOST, "::" MUROAR_OBJECT, MUROAR_ABSTRACT, NULL};
 const char * home;
 unsigned char buf[MUROAR_IOBUF];
 uint16_t tmpu16;
 uint16_t pid;
 muroar_t fh = MUROAR_HANDLE_INVALID;
 int i;
#if !defined(__WIN32)
 ssize_t len;
#endif

 // Prepare server address:
 if ( server != NULL && *server == 0 )
  server = NULL;

 if ( server == NULL )
  server = getenv("ROAR_SERVER");

#if !defined(__WIN32)
 if ( server == NULL ) {
  if ( (len = readlink("/etc/roarserver", useraddr, sizeof(useraddr))) != -1 ) {
   useraddr[len < (ssize_t)sizeof(useraddr) ? (size_t)len : sizeof(useraddr)-1] = 0;
   server = useraddr;
  }
 }
#endif

 if ( server != NULL ) {
  // "+default" is an alias to NULL.
  if ( !strcmp(server, MUROAR_DEFAULT) ) {
   server = NULL;

  // "+invalid" always return an invalid handle.
  } else if ( !strcmp(server, MUROAR_INVALID) ) {
#ifdef ECANCELED
   _SET_ERRNO(ECANCELED);
#else
   _SET_ERRNO(EINVAL);
#endif
   return MUROAR_HANDLE_INVALID;
  }
 }

 // Connect to server:
 if ( server != NULL ) {
  if ( (fh = muroar_open_socket(server)) == MUROAR_HANDLE_INVALID )
   return MUROAR_HANDLE_INVALID;
 } else {
  // build string for ~/.roar
  home = getenv("HOME");
  if ( home != NULL && home[0] == '/' && strlen(home) < (sizeof(useraddr) - 7) ) {
   snprintf(useraddr, sizeof(useraddr), "%s/.roar", home);
   useraddr[sizeof(useraddr)-1] = 0;
  }

  // go thru list of possible defaults:
  for (i = 0; fh == MUROAR_HANDLE_INVALID && addr[i] != NULL; i++) {
   if ( !strcmp(addr[i], MUROAR_INVALID) )
    continue;

   fh = muroar_open_socket(addr[i]);
  }

  if ( fh == MUROAR_HANDLE_INVALID ) {
   _SET_ERRNO(ENOENT);
   return MUROAR_HANDLE_INVALID;
  }
 }

 // Prepare client name:
 if ( name == NULL || *name == 0 )
  name = _DEFAULT_CLIENT_NAME;

 // Send IDENTIFY command to server:
 memset(buf, 0, sizeof(buf));
 buf[1] = MUROAR_CMD_IDENTIFY;

 // Calculate the length for the data part of the package.
 // Its 5 bytes plus the length of the name string.
 tmpu16 = strlen(name) + 5;

 // check if we have space for 5 bytes + length of name + tailing \0
 // in the buffer.
 if ( tmpu16 >= MUROAR_IOBUF ) {
  _CLOSE(fh);
  _SET_ERRNO(EINVAL);
  return MUROAR_HANDLE_INVALID;
 }

 buf[8] = (tmpu16 & 0xFF00) >> 8;
 buf[9] = (tmpu16 & 0x00FF);

 if ( muroar_write(fh, buf, 10) != 10 ) {
  _CLOSE(fh);
  return MUROAR_HANDLE_INVALID;
 }

 buf[0] = 1;
 pid = getpid();
 buf[1] = (pid & 0xFF000000UL) >> 24;
 buf[2] = (pid & 0x00FF0000UL) >> 16;
 buf[3] = (pid & 0x0000FF00UL) >>  8;
 buf[4] = (pid & 0x000000FFUL) >>  0;

 // sizes are already checked.
 strcpy((char*)&(buf[5]), name);

 if ( muroar_write(fh, buf, tmpu16) != tmpu16 ) {
  _CLOSE(fh);
  return MUROAR_HANDLE_INVALID;
 }

 if ( muroar_read(fh, buf, 10) != 10 ) {
  _CLOSE(fh);
  return MUROAR_HANDLE_INVALID;
 }

 if ( buf[1] != MUROAR_CMD_OK ) {
  _CLOSE(fh);
  _SET_ERRNO(EACCES);
  return MUROAR_HANDLE_INVALID;
 }

 // Send AUTH command to server:
 // We send zero-byte AUTH command
 // (type=NONE).
 memset(buf, 0, 10);
 buf[1] = MUROAR_CMD_AUTH;

 if ( muroar_write(fh, buf, 10) != 10 ) {
  _CLOSE(fh);
  return MUROAR_HANDLE_INVALID;
 }

 if ( muroar_read(fh, buf, 10) != 10 ) {
  _CLOSE(fh);
  return MUROAR_HANDLE_INVALID;
 }

 if ( buf[1] != MUROAR_CMD_OK ) {
  _CLOSE(fh);
  _SET_ERRNO(EACCES);
  return MUROAR_HANDLE_INVALID;
 }

 // We now have a working control connection, return it.
 return fh;
}