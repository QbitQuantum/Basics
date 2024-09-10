int main(int argc, char *argv[]) {
    if(argc!=2) exit(EXIT_FAILURE);
    int pid = GetProcessToPid(argv[1]);
    printf("[#] PID du CrackMe : %d\n", pid);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    if(hProcess==NULL) {
        printf("OpenProcess() : KO\n");
        exit(EXIT_FAILURE);
    }

    DWORD buffer, taille;
    if(!(ReadProcessMemory(hProcess, (LPDWORD) 0x0028FF40, &buffer, sizeof(DWORD), &taille))) { // la seule difficultée est l'adresse du stack
        printf("ReadProcessMemory() : KO\n");
        exit(EXIT_FAILURE);                           // que l'on récupère via le debugger
    }
    printf("[#] La key est : %d\n", buffer);
    close(hProcess);
    return 0;
}