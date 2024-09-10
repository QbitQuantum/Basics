Foam::searchableExtrudedCircle::searchableExtrudedCircle
(
    const IOobject& io,
    const dictionary& dict
)
:
    searchableSurface(io),
    eMeshPtr_
    (
        edgeMesh::New
        (
            IOobject
            (
                dict.lookup("file"),                // name
                io.time().constant(),               // instance
                "geometry",                         // local
                io.time(),                          // registry
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            ).objectPath()
        )
    ),
    radius_(readScalar(dict.lookup("radius")))
{
    const edgeMesh& eMesh = eMeshPtr_();

    const pointField& points = eMesh.points();
    const edgeList& edges = eMesh.edges();
    bounds() = boundBox(points, false);

    vector halfSpan(0.5*bounds().span());
    point ctr(bounds().midpoint());

    bounds().min() = ctr - mag(halfSpan)*vector(1, 1, 1);
    bounds().max() = ctr + mag(halfSpan)*vector(1, 1, 1);

    // Calculate bb of all points
    treeBoundBox bb(bounds());

    // Slightly extended bb. Slightly off-centred just so on symmetric
    // geometry there are less face/edge aligned items.
    bb.min() -= point(ROOTVSMALL, ROOTVSMALL, ROOTVSMALL);
    bb.max() += point(ROOTVSMALL, ROOTVSMALL, ROOTVSMALL);

    edgeTree_.reset
    (
        new indexedOctree<treeDataEdge>
        (
            treeDataEdge
            (
                false,                  // do not cache bb
                edges,
                points,
                identity(edges.size())
            ),
            bb,     // overall search domain
            8,      // maxLevel
            10,     // leafsize
            3.0     // duplicity
        )
    );
}