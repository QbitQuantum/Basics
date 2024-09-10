ChildSupervisor::ChildSupervisor(ThreadNetif &aThreadNetif) :
    ThreadNetifLocator(aThreadNetif),
    mTimer(aThreadNetif.GetInstance(), &ChildSupervisor::HandleTimer, this),
    mSupervisionInterval(kDefaultSupervisionInterval)
{
}