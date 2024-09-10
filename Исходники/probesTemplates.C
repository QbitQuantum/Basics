void Foam::probes::sampleAndWrite
(
    const GeometricField<Type, fvPatchField, volMesh>& vField
)
{
    Field<Type> values(sample(vField));

    if (Pstream::master())
    {
        unsigned int w = IOstream::defaultPrecision() + 7;
        OFstream& os = *probeFilePtrs_[vField.name()];

        os  << setw(w) << vField.time().timeToUserTime(vField.time().value());

        forAll(values, probeI)
        {
            os  << ' ' << setw(w) << values[probeI];
        }
        os  << endl;
    }