void test_rename(char *workdir) {
    char file1[1024], file2[1024], link[1024],
         subdir[1024], newdir[1024];
    struct stat sb1, sb2;
    int fd;

    printf("testing rename\n");

    sprintf(file1, "%s/file1", workdir);
    sprintf(file2, "%s/file2", workdir);

    /* test stat first.. since we need it to test rename */
    my_stat(file1, &sb1);

    /* Not much to look at, really..  how about making sure that
       the modification time of the file is not in the future.
       allow ten seconds of slack */
    if (sb1.st_mtime > time(NULL) + 10) {
        printf("Modification time of %s is in the future!\n",
               file1);
        exit(1);
    }

    my_rename(file1, file2);

    /* try repeat */
    if (!rename(file1, file2)) {
        printf("repeat rename(%s,%s) worked.. but it shouldn't have\n",
               file1, file2);
        exit(1);
    }


    /* inode number of file2 should be the same as it was for file1 */
    verify_inum(file2, &sb1);


    /* rename back */
    my_rename(file2, file1);

    verify_inum(file1, &sb1);

    /* Make a subdir, which will be renamed */
    sprintf(subdir, "%s/rename_this_dir", workdir);

    my_mkdir(subdir);
    my_stat(subdir, &sb2);

    /* Test moving a file into a subdir */
    sprintf(file2, "%s/file1", subdir);
    my_rename(file1, file2);
    verify_inum(file2, &sb1);

    /* Add in a hard link to spice things up */
    sprintf(link, "%s/link", subdir);
    my_link(file2, link);

    sprintf(newdir, "%s/newdirname", workdir);
    my_rename(subdir, newdir);
    verify_inum(newdir, &sb2);
    sprintf(file2, "%s/file1", newdir);
    verify_inum(file2, &sb1);
    sprintf(link, "%s/newdirname/link", workdir);
    verify_inum(link, &sb1);

    /* Test moving up in the tree */
    my_rename(file2,file1);
    verify_inum(file1, &sb1);

    my_unlink(link);

    my_rmdir(newdir);

}