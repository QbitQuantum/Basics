static int flash_bml_partition(const MtdPartition* pSrcPart, const MtdPartition* pReservoirPart,
                               const unsigned short* blockMapping, const char* filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "error opening %s", filename);
        return -1;
    }
    BmlOverMtdWriteContext* pSrcWrite = bml_over_mtd_write_partition(pSrcPart);
    if (pSrcWrite == NULL)
    {
        close(fd);
        fprintf(stderr, "flash_bml_partition: Error opening src part for writing.\n");
        return -1;
    }

#ifdef DUMMY_WRITING
    close(pSrcWrite->fd);
    pSrcWrite->fd = open("/sdcard/srcPartWriteDummy.bin", O_WRONLY|O_CREAT|O_TRUNC, 0666);
#endif

    BmlOverMtdWriteContext* pResWrite = bml_over_mtd_write_partition(pReservoirPart);
    if (pResWrite == NULL)
    {
        close(fd);
        bml_over_mtd_write_close(pSrcWrite);
        fprintf(stderr, "flash_bml_partition: Error opening reservoir part for writing.\n");
        return -1;
    }
#ifdef DUMMY_WRITING
    close(pResWrite->fd);
    pResWrite->fd = open("/sdcard/resPartWriteDummy.bin", O_WRONLY|O_CREAT|O_TRUNC, 0666);
#endif

    struct stat fileStat;
    if (fstat(fd, &fileStat) != 0)
    {
        close(fd);
        bml_over_mtd_write_close(pSrcWrite);
        bml_over_mtd_write_close(pResWrite);
        fprintf(stderr, "flash_bml_partition: Failed to stat source file.\n");
        return -1;

    }
    if (fileStat.st_size > pSrcPart->size)
    {
        close(fd);
        bml_over_mtd_write_close(pSrcWrite);
        bml_over_mtd_write_close(pResWrite);
        fprintf(stderr, "flash_bml_partition: Source file too large for target partition.\n");
        return -1;
    }

    int numBlocks = (fileStat.st_size +  pSrcPart->erase_size - 1) / pSrcPart->erase_size;
    int currblock;
    for (currblock = 0 ; currblock < numBlocks; ++currblock)
    {
        memset(pSrcWrite->buffer, 0xFF, pSrcPart->erase_size);
        size_t blockBytesRead = 0;
        while (blockBytesRead < pSrcPart->erase_size)
        {
            ssize_t len = read(fd, pSrcWrite->buffer + blockBytesRead,
                               pSrcPart->erase_size - blockBytesRead);
            if (len < 0)
            {
                close(fd);
                bml_over_mtd_write_close(pSrcWrite);
                bml_over_mtd_write_close(pResWrite);
                fprintf(stderr, "flash_bml_partition: read source file failed\n");
                return -1;
            }
            if (len == 0)
            {
                //End of file
                break;
            }

            blockBytesRead += len;
        }



        int srcFd = -1;
        if (blockMapping[currblock] == 0xffff)
        {
            //Good block, use src partition
            srcFd = pSrcWrite->fd;
            if (lseek64(pSrcWrite->fd, currblock*pSrcPart->erase_size, SEEK_SET)==-1)
            {
                close(fd);
                bml_over_mtd_write_close(pSrcWrite);
                bml_over_mtd_write_close(pResWrite);
                fprintf(stderr, "flash_bml_partition: lseek in src partition failed\n");
                return -1;
            }
        } else
        {
            //Bad block, use mapped block in reservoir partition
            srcFd = pResWrite->fd;
            if (lseek64(pResWrite->fd, blockMapping[currblock]*pSrcPart->erase_size, SEEK_SET)==-1)
            {
                close(fd);
                bml_over_mtd_write_close(pSrcWrite);
                bml_over_mtd_write_close(pResWrite);
                fprintf(stderr, "flash_bml_partition: lseek in reservoir partition failed\n");
                return -1;
            }
        }
        size_t blockBytesWritten = 0;
        while (blockBytesWritten < pSrcPart->erase_size)
        {
#ifdef DUMMY_WRITING
            ssize_t len = write(srcFd, pSrcWrite->buffer + blockBytesWritten,
                                pSrcPart->erase_size - blockBytesWritten);
#else
            ssize_t len = bml_over_mtd_write_block(srcFd, pSrcPart->erase_size, pSrcWrite->buffer);
#endif
            if (len <= 0)
            {
                close(fd);
                bml_over_mtd_write_close(pSrcWrite);
                bml_over_mtd_write_close(pResWrite);
                fprintf(stderr, "flash_bml_partition: writing to partition failed\n");
                return -1;
            }
            blockBytesWritten += len;
        }


    }

    bml_over_mtd_write_close(pSrcWrite);
    bml_over_mtd_write_close(pResWrite);

    if (close(fd)) {
        printf("error closing %s", filename);
        return -1;
    }

    return 0;
}