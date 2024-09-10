/** \return true if TRR/TRJ file. */
bool Traj_GmxTrX::ID_TrajFormat(CpptrajFile& infile) {
    // File must already be set up for read
    if (infile.OpenFile()) return false;
    bool istrx = IsTRX(infile);
    infile.CloseFile();
    return istrx;
}