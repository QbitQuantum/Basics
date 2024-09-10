// Construct from mesh
Foam::edgeStats::edgeStats(const polyMesh& mesh)
:
    mesh_(mesh),
    normalDir_(3)
{
    IOobject motionObj
    (
        "motionProperties",
        mesh.time().constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    );

    if (motionObj.headerOk())
    {
        Info<< "Reading " << mesh.time().constant() / "motionProperties"
            << endl << endl;

        IOdictionary motionProperties(motionObj);

        Switch twoDMotion(motionProperties.lookup("twoDMotion"));

        if (twoDMotion)
        {
            Info<< "Correcting for 2D motion" << endl << endl;

            autoPtr<twoDPointCorrector> correct2DPtr
            (
                new twoDPointCorrector(mesh)
            );

            normalDir_ = getNormalDir(&correct2DPtr());
        }
    }
}