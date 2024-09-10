void stdin_filler::fill(process& p) {
    if (fd == -1) return; //don't need to fill anything...
    char buf[512];
    int numbytes;
    do {
        numbytes = read(fd, buf, 512);
        if (numbytes == -1) {
            perror("read");
            std::exit(1);
        }
        if (!writeall(p.in(), buf, numbytes)) {
            //it is easy to imagine this write failing - so if that happens
            //just kill the process, as it's not useful to us...
            if (settings.verbose) {
                std::cerr << "write failed to subprocess, killing...\n";
            }
            p.term();
            break;
        }
    } while (numbytes != 0);
    lseek(fd, 0, SEEK_SET); //return to beginning of file
}