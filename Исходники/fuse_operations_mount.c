static int fuse_operations_mount_fcntl(struct MountsPublicInterface* this_, int fd, int cmd, ...) {
    ZRT_LOG(L_INFO, "cmd=%s", STR_FCNTL_CMD(cmd));
    SET_ERRNO(ENOSYS);
    return -1;
}