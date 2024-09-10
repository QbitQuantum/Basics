        static std::wstring GetNewFilePath(const std::wstring& dir, time_t time)
        {
            std::wostringstream filename;
            if (!dir.empty())
            {
                // Windows can tolerate forward slashes in paths.
                filename << dir << L"/";
            }

            filename << L"events.out.tfevents." 
                << std::setfill(L'0') << std::setw(10) << time
                << L"." << ToWString(GetHostName());
            return filename.str();
        }