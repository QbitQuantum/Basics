void Program::DoLink () {
    while (oldModList != nil) {
        InputFile* doomed = (InputFile*) oldModList;
        oldModList = (InputFile*)oldModList->nn;
        doomed->Unlink(oldModList);
        delete doomed;
    }
    Base* insertPoint = inf->nn;
    ctdt->Link(insertPoint);
    if (fullLink) {
        FullLink();
    } else {
        Relink();
    }
}