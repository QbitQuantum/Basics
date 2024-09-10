void Foam::patchRtis::sampleAndWrite
(
    const GeometricField<Type, fvPatchField, volMesh>& vField
)
{
    Field<Type> values(sample(vField));

    if (Pstream::master())
    {
        unsigned int w = IOstream::defaultPrecision() + 7;
        OFstream& rtiStream = *rtiFilePtrs_[vField.name()];

        rtiStream << setw(w) << vField.time().value();

        forAll(values, rtiI)
        {
            rtiStream << ' ' << setw(w) << values[rtiI];
        }
        rtiStream << endl;
    }