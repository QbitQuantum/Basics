    void verifyFile(const FlashEntry& fe) {

        uint8_t filePage[MyFlash::PAGE_SIZE],flashPage[MyFlash::PAGE_SIZE];
        scoped_ptr<File> file;
        uint32_t remaining,actuallyRead,address;

        *_usartStream << "Verifying " << fe.filename << "\r\n";

        if(!_fs->openFile(fe.filename,file.address()))
            error("Failed to open file");

        address=fe.offset;

        for(remaining=fe.length; remaining; remaining-=actuallyRead) {

            // read a page from the file

            if(!file->read(filePage,sizeof(filePage),actuallyRead))
                error("Failed to read from file");

            // cannot hit EOF here

            if(!actuallyRead)
                error("Unexpected end of file");

            // read the page from the flash device

            if(!_flash->fastRead(address,flashPage,actuallyRead))
                error("Failed to read from the flash device");

            // compare it

            if(memcmp(filePage,flashPage,actuallyRead)!=0)
                error("Verify error: programming failed");

            // update for next

            address+=actuallyRead;
        }
    }