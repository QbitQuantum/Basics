PET_PROCESS_ICON EtProcIconCreateProcessIcon(
    __in HICON Icon
    )
{
    PET_PROCESS_ICON processIcon;

    processIcon = PhAllocate(sizeof(ET_PROCESS_ICON));
    processIcon->RefCount = 1;
    processIcon->Icon = DuplicateIcon(NULL, Icon);

    return processIcon;
}