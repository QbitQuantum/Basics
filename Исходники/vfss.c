static inline void vfss_init(VFSS_TYPE* vfss)
{
    vfss->volume.process = INVALID_HANDLE;
    vfss->io = io_create(FAT_SECTOR_SIZE + sizeof(STORAGE_STACK));
    vfss->io_size = FAT_SECTOR_SIZE;
#if (VFS_BER)
    ber_init(vfss);
#endif //VFS_BER

#if (VFS_NO_FS == 0)
#if (VFS_SFS)
    sfs_init(vfss);
#else
    fat16_init(vfss);
#endif  // VFS_SFS
#endif // VFS_NO_FS
}