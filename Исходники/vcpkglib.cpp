    static void upgrade_to_slash_terminated_sorted_format(Files::Filesystem& fs,
                                                          std::vector<std::string>* lines,
                                                          const fs::path& listfile_path)
    {
        static bool was_tracked = false;

        if (lines->empty())
        {
            return;
        }

        if (lines->at(0).back() == '/')
        {
            return; // File already in the new format
        }

        if (!was_tracked)
        {
            was_tracked = true;
            Metrics::track_property("listfile", "update to new format");
        }

        // The files are sorted such that directories are placed just before the files they contain
        // (They are not necessarily sorted alphabetically, e.g. libflac)
        // Therefore we can detect the entries that represent directories by comparing every element with the next one
        // and checking if the next has a slash immediately after the current one's length
        for (size_t i = 0; i < lines->size() - 1; i++)
        {
            std::string& current_string = lines->at(i);
            const std::string& next_string = lines->at(i + 1);

            const size_t potential_slash_char_index = current_string.length();
            // Make sure the index exists first
            if (next_string.size() > potential_slash_char_index && next_string.at(potential_slash_char_index) == '/')
            {
                current_string += '/'; // Mark as a directory
            }
        }

        // After suffixing the directories with a slash, we can now sort.
        // We cannot sort before adding the suffixes because the following (actual example):
        /*
            x86-windows/include/FLAC <<<<<< This would be separated from its group due to sorting
            x86-windows/include/FLAC/all.h
            x86-windows/include/FLAC/assert.h
            x86-windows/include/FLAC/callback.h
            x86-windows/include/FLAC++
            x86-windows/include/FLAC++/all.h
            x86-windows/include/FLAC++/decoder.h
            x86-windows/include/FLAC++/encoder.h
         *
            x86-windows/include/FLAC/ <<<<<< This will now be kept with its group when sorting
            x86-windows/include/FLAC/all.h
            x86-windows/include/FLAC/assert.h
            x86-windows/include/FLAC/callback.h
            x86-windows/include/FLAC++/
            x86-windows/include/FLAC++/all.h
            x86-windows/include/FLAC++/decoder.h
            x86-windows/include/FLAC++/encoder.h
        */
        // Note that after sorting, the FLAC++/ group will be placed before the FLAC/ group
        // The new format is lexicographically sorted
        std::sort(lines->begin(), lines->end());

        // Replace the listfile on disk
        const fs::path updated_listfile_path = listfile_path.generic_string() + "_updated";
        fs.write_lines(updated_listfile_path, *lines);
        fs.rename(updated_listfile_path, listfile_path);
    }