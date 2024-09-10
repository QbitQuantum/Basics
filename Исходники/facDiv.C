tmp<GeometricField<Type, faPatchField, areaMesh> >
div
(
    const tmp<edgeScalarField>& tflux,
    const GeometricField<Type, faPatchField, areaMesh>& vf
)
{
    tmp<GeometricField<Type, faPatchField, areaMesh> > Div
    (
        fac::div(tflux(), vf)
    );
    tflux.clear();
    return Div;
}