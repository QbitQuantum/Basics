int main(int argc, char* argv[], char* envp[]) {
    int status, child;
    strcpy(proc_name, "parent");
    init_shared(argv);
    fprintf(stderr, "Map address is: %p\n", g_shared);

    if (child = fork()) {
        parentWork();
        waitpid(child, &status, 0);
        cleanup_shared();
        fprintf(stderr, "Parent finished!\n");
    } else { /* child executes shmem2 */
        execvpe("./mult2Vecs", argv + 2, envp);
    }
}