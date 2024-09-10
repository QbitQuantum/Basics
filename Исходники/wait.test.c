int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num-processes>\n", argv[0]);
        return -1;
    }

    int num_processes = atoi(argv[1]);
    fprintf(stderr, "Creating %d %s\n", num_processes, num_processes == 1 ? "process" : "processes");

    for (int i = 0; i < num_processes; i++) {
        pid_t pid;
        if ((pid = Fork()) == 0) {
            fprintf(stderr, "Child (%d) delaying\n", GetPid());
            Delay(2 * i);
            fprintf(stderr, "Child (%d) exiting\n", GetPid());
            Exit(100 + GetPid());
        } else {
            fprintf(stderr, "Child (%d) forked\n", pid);
        }
    }

    while (true) {
        int status;
        pid_t pid = Wait(&status);
        if (pid == ERROR) {
            break;
        } else {
            fprintf(stderr, "PID %d exited with status %d\n", pid, status);
        }
    }

    fprintf(stderr, "parent PID %d is now exiting\n", GetPid());
    Exit(0);
}