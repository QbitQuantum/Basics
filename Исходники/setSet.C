// Write set to VTK readable files
void writeVTK
(
    const polyMesh& mesh,
    const topoSet& currentSet,
    const fileName& vtkName
)
{
    if (isA<faceSet>(currentSet))
    {
        // Faces of set with OpenFOAM faceID as value

        faceList setFaces(currentSet.size());
        labelList faceValues(currentSet.size());
        label setFaceI = 0;

        forAllConstIter(topoSet, currentSet, iter)
        {
            setFaces[setFaceI] = mesh.faces()[iter.key()];
            faceValues[setFaceI] = iter.key();
            setFaceI++;
        }

        primitiveFacePatch fp(setFaces, mesh.points());

        writePatch
        (
            true,
            currentSet.name(),
            fp,
            "faceID",
            faceValues,
            mesh.time().path()/vtkName
        );
    }