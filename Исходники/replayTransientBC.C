bool loadFieldFunction(
    fvMesh &mesh,
    const word &fName,
    SLPtrList<FieldType> &fieldList
) {
    const Time &runTime=mesh.time();

    IOobject f
        (
            fName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        );
    f.headerOk();
    word className=f.headerClassName();

    if(className==FieldType::typeName) {
        Info << "Reading field " << fName << " of type "
            << FieldType::typeName << endl;
        fieldList.append(
            new FieldType
            (
                IOobject
                (
                    fName,
                    runTime.timeName(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                mesh
            )
        );
        return true;
    } else {
        return false;
    }
}