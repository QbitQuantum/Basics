void Foam::equationReader::evalDimsY1DimCheck
(
    const equationReader * eqnReader,
    const label index,
    const label i,
    const label storageOffset,
    label& storeIndex,
    dimensionSet& xDims,
    dimensionSet sourceDims
) const
{
    if
    (
        !xDims.dimensionless() && dimensionSet::debug
    )
    {
        WarningIn("equationReader::evalDimsY1DimCheck")
            << "Dimension error thrown for operation ["
            << equationOperation::opName
            (
                operator[](index)[i].operation()
            )
            << "] in equation " << operator[](index).name()
            << ", given by:" << token::NL << token::TAB
            << operator[](index).rawText();
    }
    dimensionedScalar ds("temp", xDims, 1.0);
    xDims.reset(y1(ds).dimensions());
    operator[](index)[i].assignOpDimsFunction
    (
        &Foam::equationReader::evalDimsY1
    );
}