bool Traj_Gro::ID_TrajFormat(CpptrajFile& infile) {
    // Title line, atoms line, then resnum, resname, atomname, atomnum, X, Y, Z
    if (infile.OpenFile()) return false;
    int nread = 0;
    if (infile.NextLine() != 0) { // Title
        const char* ptr = infile.NextLine(); // Natom
        if (ptr != 0) {
            // Ensure only a single value on # atoms line
            std::string natom_str( ptr );
            RemoveTrailingWhitespace( natom_str );
            if (validInteger(natom_str)) {
                ptr = infile.NextLine(); // First atom
                if (ptr != 0) {
                    char resnum[6], resname[6], atname[6], atnum[6];
                    float XYZ[3];
                    nread = sscanf(ptr, "%5c%5c%5c%5c%f %f %f", resnum, resname,
                                   atname, atnum, XYZ, XYZ+1, XYZ+2);
                }
            }
        }
    }
    infile.CloseFile();
    return (nread == 7);
}