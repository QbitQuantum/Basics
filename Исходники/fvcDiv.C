tmp<GeometricField<Type, fvPatchField, volMesh> >
div
(
    const tmp<surfaceScalarField>& tflux,
    const GeometricField<Type, fvPatchField, volMesh>& vf,
    const word& name
)
{
    tmp<GeometricField<Type, fvPatchField, volMesh> > Div
    (
        fvc::div(tflux(), vf, name)
    );
    tflux.clear();
    return Div;
}