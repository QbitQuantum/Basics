int FWrite(char *src, int offset, int count)
{
    int i, o, fd, off, addr, sz;
    unsigned char *buf;
    struct erase_info_user ei;

    if (flash_mtd_init_info())
        return -1;

#ifdef DEBUG
    printf("%s: offset %x, src string", __func__, offset);
    for (i = 0; i < count; i++)
        printf(" %x", (unsigned char) *(src + i));
    printf("\n");
#endif
    off = offset;

    for (i = 0, addr = 0; i < NUM_INFO; i++) {
        if (addr <= off && off < addr + info[i].size) {
            sz = info[i].erasesize;
            buf = (unsigned char *)malloc(sz);
            if (buf == NULL) {
                fprintf(stderr, "failed to alloc memory for %d bytes\n",
                        sz);
                return -1;
            }
            fd = flash_mtd_open(i, O_RDWR | O_SYNC);
            if (fd < 0) {
                fprintf(stderr, "failed to open mtd%d\n", i);
                free(buf);
                return -1;
            }
            off -= addr;
            o = (off / sz) * sz;
            lseek(fd, o, SEEK_SET);
#ifdef DEBUG
            printf("  backup mtd%d, o %x(off %x), len %x\n", i, o, off, sz);
#endif
            //backup
            if (read(fd, buf, sz) != sz) {
                fprintf(stderr, "failed to read %d bytes from mtd%d\n",
                        sz, i);
                free(buf);
                close(fd);
                return -1;
            }
            //erase
            ei.start = o;
            ei.length = sz;
            if (ioctl(fd, MEMERASE, &ei) < 0) {
                fprintf(stderr, "failed to erase mtd%d\n", i);
                free(buf);
                close(fd);
                return -1;
            }
            //write
            lseek(fd, o, SEEK_SET);
#ifdef DEBUG
            for (i = 0; i < count; i++)
                printf("  buf[%x] = %x\n", off - o + i, (unsigned char)*(src + i));
            printf("\n");
#endif
//			*(buf + (off - o)) = (unsigned char)value;
            memcpy(buf + (off - o), src, count);
            if (write(fd, buf, sz) == -1) {
                fprintf(stderr, "failed to write mtd%d\n", i);
                free(buf);
                close(fd);
                return -1;
            }
            free(buf);
            close(fd);
            break;
        }
        addr += info[i].size;
    }
    buf = (unsigned char *)malloc(count);
    FRead(buf, offset, count);
    free(buf);
    return 0;
}