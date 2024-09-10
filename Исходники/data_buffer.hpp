    /**
     * The file.
     */
    void set_file(const std::shared_ptr<file> & f)
    {
        /**
         * Set the file.
         */
        file_ = f;

        if (file_)
        {
            /**
             * Set the file offset.
             */
            file_offset_ = f->ftell();
        }
    }