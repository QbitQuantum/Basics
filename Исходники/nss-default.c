/* Flags once read from the file.  */
static int default_nss_flags;

/* Code to make sure we call 'init' once.  */
__libc_once_define (static, once);

/* Table of the recognized variables.  */
static const struct
{
  char name[23];
  unsigned int len;
  int flag;
} vars[] =
  {
#define STRNLEN(s) s, sizeof (s) - 1
    { STRNLEN ("NETID_AUTHORITATIVE"), NSS_FLAG_NETID_AUTHORITATIVE },
    { STRNLEN ("SERVICES_AUTHORITATIVE"), NSS_FLAG_SERVICES_AUTHORITATIVE },
    { STRNLEN ("SETENT_BATCH_READ"), NSS_FLAG_SETENT_BATCH_READ }
  };
#define nvars (sizeof (vars) / sizeof (vars[0]))


static void
init (void)
{
  int saved_errno = errno;
  FILE *fp = fopen (default_nss, "rc");
  if (fp != NULL)
    {
      char *line = NULL;
      size_t linelen = 0;