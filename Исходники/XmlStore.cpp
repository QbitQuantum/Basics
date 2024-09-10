    static int write(void* context, const char* buffer, int len)
    {
        WriteFile* file = (WriteFile*) context;

        try {
            if(file->write(buffer, len, 1) != 1) {
                LOGGER.warning("Write error while saving xml");
                return 0;
            }
        } catch(...) {
            LOGGER.warning("Write error while saving xml");
            return 0;
        }
        return len;
    }