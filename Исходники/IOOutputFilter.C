Foam::IOOutputFilter<OutputFilter>::IOOutputFilter
(
    const word& outputFilterName,
    const objectRegistry& obr,
    const fileName& dictName,
    const IOobject::readOption rOpt,
    const bool readFromFiles
)
:
    IOdictionary
    (
        IOobject
        (
            dictName,
            obr.time().system(),
            obr,
            rOpt,
            IOobject::NO_WRITE
        )
    ),
    OutputFilter(outputFilterName, obr, *this, readFromFiles)
{}