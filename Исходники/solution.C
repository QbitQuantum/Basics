Foam::solution::solution(const objectRegistry& obr, const fileName& dictName)
:
    IOdictionary
    (
        IOobject
        (
            dictName,
            obr.time().system(),
            obr,
            IOobject::READ_IF_PRESENT,  // Allow default dictionary creation
            IOobject::NO_WRITE
        )
    ),
    relaxationFactors_
    (
        ITstream("relaxationFactors", tokenList())()
    ),
    defaultRelaxationFactor_(0),
    solvers_(ITstream("solvers", tokenList())())
{
    if (!headerOk())
    {
        if (debug)
        {
            InfoIn
            (
                "Foam::solution::solution(const objectRegistry& obr, "
                "const fileName& dictName)"
            )   << "Solution dictionary not found.  Adding default entries"
                << endl;
        }
    }

    read();
}