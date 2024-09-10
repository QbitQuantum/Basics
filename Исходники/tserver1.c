int
main(int argc, char **argv)
{
    struct stat	stat;

    if (argc != 2)
        err_quit("usage: server1 <pathname>");

    Door_server_create(my_create);

    /* 4create a door descriptor */
    fd = Door_create(server, (void *) 44, DOOR_PRIVATE);
    Fstat(fd, &stat);
    printf("server() at %p, fmt = %lx\n", server,
           (long) stat.st_mode & S_IFMT);

    /* 4bind it to the specified pathname */
    unlink(argv[1]);
    Close(Open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE));
    Fattach(fd, argv[1]);
    /* Close(fd); */

    /* server() handles all client requests */
    for ( ; ; )
        pause();
}