void Foam::calcTypes::mag::writeMagField
(
    const IOobject& header,
    const fvMesh& mesh,
    bool& processed
)
{
    typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

    if (header.headerClassName() == fieldType::typeName)
    {
        Info<< "    Reading " << header.name() << endl;
        fieldType field(header, mesh);

        Info<< "    Calculating mag" << header.name() << endl;
        volScalarField magField
        (
            IOobject
            (
                "mag" + header.name(),
                mesh.time().timeName(),
                mesh,
                IOobject::NO_READ
            ),
            Foam::mag(field)
        );

        Info << "mag(" << header.name() << "): max: "
            << gMax(magField.internalField())
            << " min: " << gMin(magField.internalField()) << endl;

        magField.write();

        processed = true;
    }
}