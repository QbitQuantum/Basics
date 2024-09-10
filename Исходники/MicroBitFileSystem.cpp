/**
  * Read data from the file.
  *
  * Read len bytes from the current seek position in the file, into the
  * buffer. On each invocation to read, the seek position of the file
  * handle is incremented atomically, by the number of bytes returned.
  *
  * @param fd File handle, obtained with open()
  * @param buffer to store data
  * @param size number of bytes to read
  * @return number of bytes read on success, MICROBIT_NOT_SUPPORTED if the file
  *         system is not initialised, or this file was not opened with the
  *         MB_READ flag set, MICROBIT_INVALID_PARAMETER if the given file handle
  *         is invalid.
  *
  * @code
  * MicroBitFileSystem f;
  * int fd = f.open("read.txt", MB_READ);
  * if(f.read(fd, buffer, 100) != 100)
  *    print("read error");
  * @endcode
  */
int MicroBitFileSystem::read(int fd, uint8_t* buffer, int size)
{
    FileDescriptor *file;
    uint16_t block;
    uint8_t *readPointer;
    uint8_t *writePointer;

    uint32_t offset;
    uint32_t position = 0;
    int bytesCopied = 0;
    int segmentLength;

    // Protect against accidental re-initialisation
    if ((status & MBFS_STATUS_INITIALISED) == 0)
        return MICROBIT_NOT_SUPPORTED;

    // Ensure the file is open.
    file = getFileDescriptor(fd);

    if (file == NULL || buffer == NULL || size == 0)
        return MICROBIT_INVALID_PARAMETER;

    // Flush any data in the writeback cache before we change the seek pointer.
    writeBack(file);

    // Validate the read length.
    size = min(size, file->length - file->seek);

    // Find the read position.
    block = file->dirent->first_block; 

    // Walk the file table until we reach the start block
    while (file->seek - position > MBFS_BLOCK_SIZE)
    {
        block = getNextFileBlock(block);
        position += MBFS_BLOCK_SIZE;
    }

    // Once we have the correct start block, handle the byte offset.
    offset = file->seek - position;

    // Now, start copying bytes into the requested buffer.
    writePointer = buffer;
    while (bytesCopied < size)
    {
        // First, determine if we need to write a partial block.
        readPointer = (uint8_t *)getBlock(block) + offset;
        segmentLength = min(size - bytesCopied, MBFS_BLOCK_SIZE - offset);

        if(segmentLength > 0)
            memcpy(writePointer, readPointer, segmentLength);

        bytesCopied += segmentLength;
        writePointer += segmentLength;
        offset += segmentLength;

        if (offset == MBFS_BLOCK_SIZE)
        {
            block = getNextFileBlock(block);
            offset = 0;
        }
    }

    file->seek += bytesCopied;

    return bytesCopied;
}