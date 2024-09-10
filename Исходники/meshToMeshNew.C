void Foam::meshToMeshNew::writeConnectivity
(
    const polyMesh& src,
    const polyMesh& tgt,
    const labelListList& srcToTargetAddr
) const
{
    Pout<< "Source size = " << src.nCells() << endl;
    Pout<< "Target size = " << tgt.nCells() << endl;

    word fName("addressing_" + src.name() + "_to_" + tgt.name());

    if (Pstream::parRun())
    {
        fName = fName +  "_proc" + Foam::name(Pstream::myProcNo());
    }

    OFstream os(src.time().path()/fName + ".obj");

    label vertI = 0;
    forAll(srcToTargetAddr, i)
    {
        const labelList& tgtAddress = srcToTargetAddr[i];
        forAll(tgtAddress, j)
        {
            label tgtI = tgtAddress[j];
            const vector& c0 = src.cellCentres()[i];

            const cell& c = tgt.cells()[tgtI];
            const pointField pts(c.points(tgt.faces(), tgt.points()));
            forAll(pts, j)
            {
                const point& p = pts[j];
                os  << "v " << p.x() << ' ' << p.y() << ' ' << p.z() << nl;
                vertI++;
                os  << "v " << c0.x() << ' ' << c0.y() << ' ' << c0.z()
                    << nl;
                vertI++;
                os  << "l " << vertI - 1 << ' ' << vertI << nl;
            }
        }
    }