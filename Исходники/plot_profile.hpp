        /**
         *  Finds the nth entry from the fasta file and returns the associated sequence
         **/
        static int getEntryFromFasta(const path& fasta_path, uint32_t n, string& header, string& sequence)
        {
            // Setup stream to sequence file and check all is well
            std::ifstream inputStream (fasta_path.c_str());

            if (!inputStream.is_open())
            {
                std::cerr << "ERROR: Could not open the sequence file: " << fasta_path << endl;
                return 0;
            }


            std::string id;
            std::string seq;
            uint32_t i = 1;

            // Read a record
            while(inputStream.good() && readRecord(inputStream, id, seq) == 0)
            {
                if (i == n)
                {
                    inputStream.close();

                    header.swap(id);
                    sequence = seq;
                    return 0;
                }

                seq.clear();
                i++;
            }

            inputStream.close();
            return -1;
        }