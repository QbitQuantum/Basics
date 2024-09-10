int run(char *program_name[], char **program_argv[], unsigned int count) {
    int child[count];
    int num_proc = 0;
    int soyhijo = 0;
    int pipes[count][2];
    char buf[1024];
    //char buf_sal[1024];
    //char *newenviron[] = { NULL };
    //int haydatos = 0;
    //int status = 0;
    
    while (num_proc < count && soyhijo == 0) {
        //creo un nuevo pipe
        if (pipe(pipes[num_proc]) < 0) {
            perror("pipe");
        }

        //creo un nuevo proceso
        child[num_proc] = fork();
        if (child[num_proc] == 0) {
            soyhijo = 1;
        } else {
            num_proc++;
        }
    }
    if (soyhijo == 1) {
        //printf("Soy el hijo %d\n", num_proc);
        for (int i = 0; i < num_proc; i++) {
            close(pipes[i][1]);
            if (i != num_proc-1) {
                close(pipes[i][0]);
            }
        }
        close(pipes[num_proc][0]);
        //close(0);
        if (num_proc > 0) {
            dup2(pipes[num_proc-1][0], 0);
            //if (read(pipes[num_proc-1][0], buf, 1024) < 0) {
            //    perror("leyendo datos");
            //}
            //haydatos = 1;
        }
        //printf("Pude pasar. Soy el hijo %d\n", num_proc);

        /*if (haydatos == 1) {
            printf("Datos: %s\n", buf);
            int noencontre = 1;
            int j = 0;
            while (noencontre) {
                if (program_argv[num_proc][j] == NULL) {
                    noencontre = 0;
                    program_argv[num_proc][j] = buf;
                    program_argv[num_proc][j+1] = NULL;
                }
                printf("%d: %s\n", j, program_argv[num_proc][j]);
                j++;
            }
            printf("%d: %s\n", j, program_argv[num_proc][j]);
        }*/
        //printf("%s\n", program_argv[num_proc][0]);
        //printf("%s\n", program_argv[num_proc][1]);
        dup2(pipes[num_proc][1], 1);
        //perror("antes de ejecutar");
        printf("asd\n");
        execvp(program_name[num_proc], program_argv[num_proc]);
        if (num_proc > 0) {
            close(pipes[num_proc-1][0]);
            close(0);
        }
        close(pipes[num_proc][1]);
        //perror("despues de ejecutar");
        /*if (write(pipes[num_proc][1], buf_sal, sizeof(buf_sal)) < 0) {
            perror("escribiendo datos");
        }*/
    } else {
        for (int i = 0; i < count - 1; i++) {
            close(pipes[i][1]);
            close(pipes[i][0]);
        }
        close(pipes[count-1][1]);

        //dup2(1, pipes[count-1][0]);
        //waitpid(child[count-1], &status, 1);
        if (read(pipes[count-1][0], buf, 1024) < 0) {
            perror("leyendo datos");
        }
        printf("%s", buf);
        close(pipes[count-1][0]);
        //perror("Soy el padre saliendo");
    }

    return 0;
}