Foam::displacementInterpolationFvMotionSolver::
displacementInterpolationFvMotionSolver
(
    const polyMesh& mesh,
    Istream& is
)
:
    displacementFvMotionSolver(mesh, is),
    dynamicMeshCoeffs_
    (
        IOdictionary
        (
            IOobject
            (
                "dynamicMeshDict",
                mesh.time().constant(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            )
        ).subDict(typeName + "Coeffs")
    )
{
    // Get zones and their interpolation tables for displacement
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    List<Pair<word> > faceZoneToTable
    (
        dynamicMeshCoeffs_.lookup("interpolationTables")
    );

    const faceZoneMesh& fZones = mesh.faceZones();

    times_.setSize(fZones.size());
    displacements_.setSize(fZones.size());

    forAll(faceZoneToTable, i)
    {
        const word& zoneName = faceZoneToTable[i][0];
        label zoneI = fZones.findZoneID(zoneName);

        if (zoneI == -1)
        {
            FatalErrorIn
            (
                "displacementInterpolationFvMotionSolver::"
                "displacementInterpolationFvMotionSolver(const polyMesh&,"
                "Istream&)"
            )   << "Cannot find zone " << zoneName << endl
                << "Valid zones are " << mesh.faceZones().names()
                << exit(FatalError);
        }

        const word& tableName = faceZoneToTable[i][1];

        IOList<Tuple2<scalar, vector> > table
        (
            IOobject
            (
                tableName,
                mesh.time().constant(),
                "tables",
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            )
        );

        // Copy table
        times_[zoneI].setSize(table.size());
        displacements_[zoneI].setSize(table.size());

        forAll(table, j)
        {
            times_[zoneI][j] = table[j].first();
            displacements_[zoneI][j] = table[j].second();
        }
    }