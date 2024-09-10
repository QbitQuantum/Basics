Foam::multiSolidBodyMotionFvMesh::multiSolidBodyMotionFvMesh(const IOobject& io)
:
    dynamicFvMesh(io),
    dynamicMeshCoeffs_
    (
        IOdictionary
        (
            IOobject
            (
                "dynamicMeshDict",
                io.time().constant(),
                *this,
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE,
                false
            )
        ).subDict(typeName + "Coeffs")
    ),
    undisplacedPoints_
    (
        IOobject
        (
            "points",
            io.time().constant(),
            meshSubDir,
            *this,
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false
        )
    )
{
    if (undisplacedPoints_.size() != nPoints())
    {
        FatalIOErrorInFunction
        (
            dynamicMeshCoeffs_
        )   << "Read " << undisplacedPoints_.size()
            << " undisplaced points from " << undisplacedPoints_.objectPath()
            << " but the current mesh has " << nPoints()
            << exit(FatalIOError);
    }


    zoneIDs_.setSize(dynamicMeshCoeffs_.size());
    SBMFs_.setSize(dynamicMeshCoeffs_.size());
    pointIDs_.setSize(dynamicMeshCoeffs_.size());
    label zoneI = 0;

    forAllConstIter(dictionary, dynamicMeshCoeffs_, iter)
    {
        if (iter().isDict())
        {
            zoneIDs_[zoneI] = cellZones().findZoneID(iter().keyword());

            if (zoneIDs_[zoneI] == -1)
            {
                FatalIOErrorInFunction
                (
                    dynamicMeshCoeffs_
                )   << "Cannot find cellZone named " << iter().keyword()
                    << ". Valid zones are " << cellZones().names()
                    << exit(FatalIOError);
            }

            const dictionary& subDict = iter().dict();

            SBMFs_.set
            (
                zoneI,
                solidBodyMotionFunction::New(subDict, io.time())
            );

            // Collect points of cell zone.
            const cellZone& cz = cellZones()[zoneIDs_[zoneI]];

            boolList movePts(nPoints(), false);

            forAll(cz, i)
            {
                label celli = cz[i];
                const cell& c = cells()[celli];
                forAll(c, j)
                {
                    const face& f = faces()[c[j]];
                    forAll(f, k)
                    {
                        label pointi = f[k];
                        movePts[pointi] = true;
                    }
                }
            }