conservativeMeshToMesh::conservativeMeshToMesh
(
    const fvMesh& srcMesh,
    const fvMesh& tgtMesh,
    const label nThreads,
    const bool forceRecalculation,
    const bool writeAddressing
)
:
    meshSrc_(srcMesh),
    meshTgt_(tgtMesh),
    addressing_
    (
        IOobject
        (
            "addressing",
            tgtMesh.time().timeName(),
            tgtMesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        tgtMesh.nCells()
    ),
    weights_
    (
        IOobject
        (
            "weights",
            tgtMesh.time().timeName(),
            tgtMesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        tgtMesh.nCells()
    ),
    centres_
    (
        IOobject
        (
            "centres",
            tgtMesh.time().timeName(),
            tgtMesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        tgtMesh.nCells()
    ),
    cellAddressing_(tgtMesh.nCells()),
    counter_(0),
    boundaryAddressing_(tgtMesh.boundaryMesh().size())
{
    if (addressing_.headerOk() && weights_.headerOk() && centres_.headerOk())
    {
        // Check if sizes match. Otherwise, re-calculate.
        if
        (
            addressing_.size() == tgtMesh.nCells() &&
            weights_.size() == tgtMesh.nCells() &&
            centres_.size() == tgtMesh.nCells() &&
           !forceRecalculation
        )
        {
            Info<< " Reading addressing from file." << endl;

            return;
        }

        Info<< " Recalculating addressing." << endl;
    }
    else
    {
        Info<< " Calculating addressing." << endl;
    }

    // Check if the source mesh has a calculated addressing
    // If yes, try and invert that.
    IOobject srcHeader
    (
        "addressing",
        srcMesh.time().timeName(),
        srcMesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    );

    if (srcHeader.headerOk() && !addressing_.headerOk())
    {
        Info<< " Found addressing in source directory."
            << " Checking for compatibility." << endl;

        if (invertAddressing())
        {
            Info<< " Inversion successful. " << endl;
            return;
        }
    }

    // Track calculation time
    clockTime calcTimer;

    // Compute nearest cell addressing
    calcCellAddressing();

    if (nThreads == 1)
    {
        calcAddressingAndWeights(0, tgtMesh.nCells(), true);
    }
    else
    {
        // Prior to multi-threaded operation,
        // force calculation of demand-driven data
        tgtMesh.cells();
        srcMesh.cells();
        srcMesh.cellCentres();
        srcMesh.cellCells();

        multiThreader threader(nThreads);

        // Set one handler per thread
        PtrList<handler> hdl(threader.getNumThreads());

        forAll(hdl, i)
        {
            hdl.set(i, new handler(*this, threader));
        }

        // Simple, but inefficient load-balancing scheme
        labelList tStarts(threader.getNumThreads(), 0);
        labelList tSizes(threader.getNumThreads(), 0);

        label index = tgtMesh.nCells(), j = 0;

        while (index--)
        {
            tSizes[(j = tSizes.fcIndex(j))]++;
        }

        label total = 0;

        for (label i = 1; i < tStarts.size(); i++)
        {
            tStarts[i] = tSizes[i-1] + total;

            total += tSizes[i-1];
        }

        if (debug)
        {
            Info<< " Load starts: " << tStarts << endl;
            Info<< " Load sizes: " << tSizes << endl;
        }

        // Set the argument list for each thread
        forAll(hdl, i)
        {
            // Size up the argument list
            hdl[i].setSize(2);

            // Set the start/end cell indices
            hdl[i].set(0, &tStarts[i]);
            hdl[i].set(1, &tSizes[i]);

            // Lock the slave thread first
            hdl[i].lock(handler::START);
            hdl[i].unsetPredicate(handler::START);

            hdl[i].lock(handler::STOP);
            hdl[i].unsetPredicate(handler::STOP);
        }