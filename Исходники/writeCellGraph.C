void writeCellGraph
(
    const volScalarField& vsf,
    const word& graphFormat
)
{
    fileName path(vsf.time().path()/"graphs"/vsf.time().timeName());
    mkDir(path);

    graph
    (
        vsf.name(),
        "x",
        vsf.name(),
        vsf.mesh().C().primitiveField().component(vector::X),
        vsf.primitiveField()
    ).write(path/vsf.name(), graphFormat);
}