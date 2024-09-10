            std::string xaml_device::get_raster_file_path() {
                // TODO: change this to use same folder/name as _filename
                // but with an incrementing integer suffix, and a .bmp extension
                char folderpath[1024];
                char filepath[1024];
                GetTempPathA(1024, folderpath);
                GetTempFileNameA(folderpath, "rt", 0, filepath);

                return std::string(filepath);
            }