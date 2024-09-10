void
ideinit(void)
{
  memdisk = _binary_fs_img_start;
  disksize = div(((uint)_binary_fs_img_end - (uint)_binary_fs_img_start), 512);
}