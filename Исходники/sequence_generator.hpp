    const char * get(unsigned count) const
    {
        if (count == this->last_num && this->last_filename) {
            return this->last_filename;
        }

        using std::snprintf;
        switch (this->format) {
            default:
            case PATH_FILE_PID_COUNT_EXTENSION:
                snprintf( this->filename_gen, sizeof(this->filename_gen), "%s%s-%06u-%06u%s", this->path
                        , this->filename, this->pid, count, this->extension);
                break;
            case PATH_FILE_COUNT_EXTENSION:
                snprintf( this->filename_gen, sizeof(this->filename_gen), "%s%s-%06u%s", this->path
                        , this->filename, count, this->extension);
                break;
            case PATH_FILE_PID_EXTENSION:
                snprintf( this->filename_gen, sizeof(this->filename_gen), "%s%s-%06u%s", this->path
                        , this->filename, this->pid, this->extension);
                break;
            case PATH_FILE_EXTENSION:
                snprintf( this->filename_gen, sizeof(this->filename_gen), "%s%s%s", this->path
                        , this->filename, this->extension);
                break;
        }
        return this->filename_gen;
    }