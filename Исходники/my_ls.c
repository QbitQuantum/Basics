//获取文件属性并打印
void display_attribute(struct stat *buf, char *path)
{
    char time[32];
    struct passwd *psd;
    struct group *grp;

    //获取并打印文件类型
    if (S_ISLNK(buf->st_mode)) {
        printf("l");
    } else if (S_ISREG(buf->st_mode)) {
        printf("-");
    } else if (S_ISDIR(buf->st_mode)) {
        printf("d");
    } else if (S_ISCHR(buf->st_mode)) {
        printf("c");
    } else if (S_ISBLK(buf->st_mode)) {
        printf("b");
    } else if (S_ISFIFO(buf->st_mode)) {
        printf("f");
    } else if (S_ISSOCK(buf->st_mode)) {
        printf("s");
    }
    //获取所有者的权限
    if (buf->st_mode & S_IRUSR) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IWUSR) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IXUSR) {
        printf("x");
    } else {
        printf("-");
    }
    //获取组权限
    if (buf->st_mode & S_IRGRP) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IWGRP) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IXGRP) {
        printf("x");
    } else {
        printf("-");
    }
    //获取其他用户权限
    if (buf->st_mode & S_IROTH) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IWOTH) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf->st_mode & S_IXOTH) {
        printf("x");
    } else {
        printf("-");
    }
    printf(" ");

    printf("%5lu ", buf->st_nlink);    //打印文件连接数

    //根据uid,gid获取用户名和组名
    psd = getpwuid(buf->st_uid);
    grp = getgrgid(buf->st_gid);
    printf("%-s\t", psd -> pw_name);
    printf("%-s\t", grp -> gr_name);

    printf("%10ld ", buf->st_size);    //打印文件大小

    strcpy(time, ctime(&buf -> st_mtime));
    time[(strlen(time)) - 1] = '\0';
    printf("%s ", time);             //打印时间
    printf("%s\n", path);             //打印文件名
}