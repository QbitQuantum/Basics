Foam::regionProperties::regionProperties(const Time& runTime)
:
    HashTable<wordList>
    (
        IOdictionary
        (
            IOobject
            (
                "regionProperties",
                runTime.time().constant(),
                runTime.db(),
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE
            )
        ).lookup("regions")
    )
{}