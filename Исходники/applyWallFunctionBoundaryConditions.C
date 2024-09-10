void replaceBoundaryType
(
    const fvMesh& mesh,
    const word& fieldName,
    const word& boundaryType,
    const string& boundaryValue
)
{
    IOobject header
    (
        fieldName,
        mesh.time().timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    );

    if (!header.headerOk())
    {
        return;
    }

    Info<< "Updating boundary types for field " << header.name() << endl;

    const word oldTypeName = IOdictionary::typeName;
    const_cast<word&>(IOdictionary::typeName) = word::null;

    IOdictionary dict(header);

    const_cast<word&>(IOdictionary::typeName) = oldTypeName;
    const_cast<word&>(dict.type()) = dict.headerClassName();

    // Make a backup of the old field
    word backupName(dict.name() + ".old");
    Info<< "    copying " << dict.name() << " to "
        << backupName << endl;
    IOdictionary dictOld = dict;
    dictOld.rename(backupName);
    dictOld.regIOobject::write();

    // Loop through boundary patches and update
    const polyBoundaryMesh& bMesh = mesh.boundaryMesh();
    dictionary& boundaryDict = dict.subDict("boundaryField");
    forAll(bMesh, patchI)
    {
        if (bMesh[patchI].isWall())
        {
            word patchName = bMesh[patchI].name();
            dictionary& oldPatch = boundaryDict.subDict(patchName);

            dictionary newPatch(dictionary::null);
            newPatch.add("type", boundaryType);
            newPatch.add("value", ("uniform " + boundaryValue).c_str());

            oldPatch = newPatch;
        }
    }

    Info<< "    writing updated " << dict.name() << nl << endl;
    dict.regIOobject::write();
}