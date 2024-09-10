// Check writing tolerance before doing any serious work
scalar getMergeDistance(const polyMesh& mesh, const scalar mergeTol)
{
    const boundBox& meshBb = mesh.bounds();
    scalar mergeDist = mergeTol * meshBb.mag();
    scalar writeTol = std::pow
    (
        scalar(10.0),
       -scalar(IOstream::defaultPrecision())
    );

    Info<< nl
        << "Overall mesh bounding box  : " << meshBb << nl
        << "Relative tolerance         : " << mergeTol << nl
        << "Absolute matching distance : " << mergeDist << nl
        << endl;

    if (mesh.time().writeFormat() == IOstream::ASCII && mergeTol < writeTol)
    {
        FatalErrorIn("getMergeDistance(const polyMesh&, const scalar)")
            << "Your current settings specify ASCII writing with "
            << IOstream::defaultPrecision() << " digits precision." << endl
            << "Your merging tolerance (" << mergeTol << ") is finer than this."
            << endl
            << "Please change your writeFormat to binary"
            << " or increase the writePrecision" << endl
            << "or adjust the merge tolerance (-mergeTol)."
            << exit(FatalError);
    }

    return mergeDist;
}