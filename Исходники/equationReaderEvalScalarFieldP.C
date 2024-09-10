void Foam::equationReader::evalScalarFieldY0
(
    const equationReader * eqnReader,
    const label index,
    const label i,
    const label storageOffset,
    label& storeIndex,
    scalarField& x,
    const scalarField& source
) const
{
    y0(x, x);
}