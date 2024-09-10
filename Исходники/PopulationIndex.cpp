void PopulationIndex::mergeIndexFiles(const std::string& file1, const std::string& file2, const std::string& outfile)
{
    std::ostream* writer = createWriter(outfile);
    
    // Copy the first index to the output unmodified but track the number of elements read
    size_t num_file_1 = 0;
    std::istream* reader = createReader(file1);
    std::string line;
    while(getline(*reader, line))
    {
        // Copy
        *writer << line << "\n";
        
        // Parse
        PopulationMember member = str2member(line);
        num_file_1 += (member.end - member.start + 1);
    }    
    delete reader;

    // Copy the second index, offsetting by the number of reads in file1
    reader = createReader(file2);
    while(getline(*reader, line))
    {
        PopulationMember member = str2member(line);
        member.start += num_file_1;
        member.end += num_file_1;

        // Copy
        *writer << member.start << "\t" << member.end << "\t" << member.name << "\n";
    } 
    delete reader;
    delete writer;
}