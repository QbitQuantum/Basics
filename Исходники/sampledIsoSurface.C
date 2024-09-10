Foam::tmp<Foam::volScalarField> Foam::sampledIsoSurface::average
(
    const fvMesh& mesh,
    const pointScalarField& pfld
) const
{
    tmp<volScalarField> tcellAvg
    (
        new volScalarField
        (
            IOobject
            (
                "cellAvg",
                mesh.time().timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                false
            ),
            mesh,
            dimensionedScalar("zero", dimless, scalar(0.0))
        )
    );
    volScalarField& cellAvg = tcellAvg();

    labelField nPointCells(mesh.nCells(), 0);
    {
        for (label pointI = 0; pointI < mesh.nPoints(); pointI++)
        {
            const labelList& pCells = mesh.pointCells(pointI);

            forAll(pCells, i)
            {
                label cellI = pCells[i];

                cellAvg[cellI] += pfld[pointI];
                nPointCells[cellI]++;
            }
        }
    }