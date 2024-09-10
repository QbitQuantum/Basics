void writeWeights(const polyMesh& mesh)
{
    const polyBoundaryMesh& pbm = mesh.boundaryMesh();

    const word tmName(mesh.time().timeName());

    forAll(pbm, patchI)
    {
        if (isA<cyclicAMIPolyPatch>(pbm[patchI]))
        {
            const cyclicAMIPolyPatch& cpp =
                refCast<const cyclicAMIPolyPatch>(pbm[patchI]);

            if (cpp.owner())
            {
                Info<< "Calculating AMI weights between owner patch: "
                    << cpp.name() << " and neighbour patch: "
                    << cpp.neighbPatch().name() << endl;

                const AMIPatchToPatchInterpolation& ami =
                    cpp.AMI();

                writeWeights
                (
                    ami.tgtWeightsSum(),
                    cpp.neighbPatch(),
                    "postProcessing",
                    "tgt",
                    tmName
                );
                writeWeights
                (
                    ami.srcWeightsSum(),
                    cpp,
                    "postProcessing",
                    "src",
                    tmName
                );
            }
        }
    }
}