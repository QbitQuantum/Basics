// Analyse mesh topology and perform CFD-side CPL_init.
void CPLSocket::\
    initCFD (const Foam::Time &runTime, const Foam::fvMesh &mesh) {

    Foam::Info << "CPLSocket: Analysing processor and mesh topology"
               << Foam::endl;

    // Read from decomposePar dictionary the number of processors in each
    // direction. Must be decomposed with the "simple" method.
    Foam::IOdictionary decomposeDict
    (
        Foam::IOobject ("decomposeParDict", runTime.time().system(), runTime,
                        IOobject::MUST_READ, IOobject::NO_WRITE, false)
    );
    Foam::dictionary simpleCoeffs = decomposeDict.subDict ("simpleCoeffs");
    Foam::Vector<int> np = simpleCoeffs.lookup ("n");
    nprocs = np.x() * np.y() * np.z();

    // Define arrays needed by MPI & CPL cart create routines 
    npxyz[0] = np.x();
    npxyz[1] = np.y();
    npxyz[2] = np.z();
    periods[0] = 1;
    periods[1] = 0;
    periods[2] = 1;

    // Get info needed to calculate this processor's spatial coordinates
    Foam::pointField points = mesh.points();
    Foam::Vector<double> procMaxPoints (maxPoints (points));
    Foam::Vector<double> procMinPoints (minPoints (points));

    // Reduce all with min/max operator to find global min/max
    Foam::Vector<double> globMaxPoints (procMaxPoints);
    Foam::Vector<double> globMinPoints (procMinPoints);
    Foam::reduce (globMaxPoints, maxOp<Foam::Vector<double>>());
    Foam::reduce (globMinPoints, minOp<Foam::Vector<double>>());

    Foam::Vector<double> domainLength (globMaxPoints - globMinPoints);

//    std::cout << "domainlength " << domainLength.x() << " " << domainLength.y() << " " << domainLength.z() << std::endl;
//    std::cout << "proc_min" << procMinPoints.x() << " " << procMinPoints.y() << " " << procMinPoints.z() \
    << "glob_min" << globMinPoints.x() << " " << globMinPoints.y() << " " << globMinPoints.z() << std::endl;