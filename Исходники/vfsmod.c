static struct dentry *sf_mount(struct file_system_type *fs_type, int flags,
                               const char *dev_name, void *data)
{
    TRACE();
    return mount_nodev(fs_type, flags, data, sf_read_super_26);
}