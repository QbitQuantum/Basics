int main(int argc, char *argv[])
{
    int input,x;
    SocketHandler h;
    ListenSocket<DisplaySocket> l(h);
    std::string text = argc > 1 ? argv[1] : "";
    l.Bind(12346);
    h.Add(&l);
    pid_t pid = fork();
    if (pid != 0) {
        while (!done) {
            x = scanf("%d",&input);
            if (input == 1) {
                done = 1;
                kill(pid, SIGTERM);
            }
        }
    } else {
        while (1)
        {
            h.Select(1, 0);
            printf("dada\n");
        }
    }
}