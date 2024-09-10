tmp<fvMatrix<Type> >
div
(
    const tmp<surfaceScalarField>& tflux,
    const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    tmp<fvMatrix<Type> > Div(fvm::div(tflux(), vf));
    tflux.clear();
    return Div;
}