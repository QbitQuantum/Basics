Foam::solidBodyMotionFvMesh::solidBodyMotionFvMesh(const IOobject& io)
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
    SBMFPtr_(solidBodyMotionFunction::New(dynamicMeshCoeffs_, io.time())),
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
    ),
    pointIDs_(),
    moveAllCells_(false),
    UName_(dynamicMeshCoeffs_.lookupOrDefault<word>("UName", "U"))
{
    if (undisplacedPoints_.size() != nPoints())
    {
        FatalIOErrorIn
        (
            "solidBodyMotionFvMesh::solidBodyMotionFvMesh(const IOobject&)",
            dynamicMeshCoeffs_
        )   << "Read " << undisplacedPoints_.size()
            << " undisplaced points from " << undisplacedPoints_.objectPath()
            << " but the current mesh has " << nPoints()
            << exit(FatalIOError);
    }

    word cellZoneName =
        dynamicMeshCoeffs_.lookupOrDefault<word>("cellZone", "none");

    word cellSetName =
        dynamicMeshCoeffs_.lookupOrDefault<word>("cellSet", "none");

    if ((cellZoneName != "none") && (cellSetName != "none"))
    {
        FatalIOErrorIn
        (
            "solidBodyMotionFvMesh::solidBodyMotionFvMesh(const IOobject&)",
            dynamicMeshCoeffs_
        )
            << "Either cellZone OR cellSet can be supplied, but not both. "
            << "If neither is supplied, all cells will be included"
            << exit(FatalIOError);
    }


    labelList cellIDs;
    if (cellZoneName != "none")
    {
        Info<< "Applying solid body motion to cellZone " << cellZoneName
            << endl;

        label zoneID = cellZones().findZoneID(cellZoneName);

        if (zoneID == -1)
        {
            FatalErrorIn
            (
                "solidBodyMotionFvMesh::solidBodyMotionFvMesh(const IOobject&)"
            )
                << "Unable to find cellZone " << cellZoneName
                << ".  Valid celLZones are:"
                << cellZones().names()
                << exit(FatalError);
        }

        cellIDs = cellZones()[zoneID];
    }

    if (cellSetName != "none")
    {
        Info<< "Applying solid body motion to cellSet " << cellSetName
            << endl;

        cellSet set(*this, cellSetName);

        cellIDs = set.toc();
    }

    label nCells = returnReduce(cellIDs.size(), sumOp<label>());
    moveAllCells_ = nCells == 0;

    if (moveAllCells_)
    {
        Info<< "Applying solid body motion to entire mesh" << endl;
    }
    else
    {
        // collect point IDs of points in cell zone

        boolList movePts(nPoints(), false);

        forAll(cellIDs, i)
        {
            label cellI = cellIDs[i];
            const cell& c = cells()[cellI];
            forAll(c, j)
            {
                const face& f = faces()[c[j]];
                forAll(f, k)
                {
                    label pointI = f[k];
                    movePts[pointI] = true;
                }
            }
        }