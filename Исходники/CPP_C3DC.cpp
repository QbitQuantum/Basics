void cAppli_MPI2Mnt::ExeCom(const std::string & aCom)
{
    if (mDebug)
        std::cout << aCom << "\n\n";
    else
        System(aCom);
}