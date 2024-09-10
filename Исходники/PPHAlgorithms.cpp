std::vector<Line2D> generateCrossSectionBounds(int edge,int frame,const Compound* compound,const Matrix3x3& polyBasisToStdBasis,bool symmetrize)
{
    Line refEdge=compound->getPolyhedron(frame)->getEdgeLine(edge);
    Point midpoint=refEdge.getMidpoint();
    Matrix3x3 stdBasisToPolyBasis=polyBasisToStdBasis.inverse();
    Plane z0=planeThroughPointPerpendicularToLine(midpoint, refEdge);
    
    Point zero(0,0,0);
    Line zeroLine(zero,zero);
    
    //make vectors containing cross section lines
    std::vector<Line2D> crossSection2D; //cross section lines expressed in poly basis (in 2D, z-component is ignored since the cross section is the same along the axis of the edge)
    double compoundCylinder=compound->computeWidth();
    
    for (int i=0;i<compound->getNumberOfPolyhedra();i++)
    {
        if (i==frame) {continue;}
        const Polyhedron* poly=compound->getPolyhedron(i);
        for (int j=0;j<poly->getEdgeNum();j++)
        {
            Line edge=poly->getEdgeLine(j);
            Line closeApproach=lineOfClosestApproach(edge, refEdge);
            if (closeApproach==zeroLine) {continue;} //REDO THIS: closest approach occurs outside the line segments + oa buffers
            
            Point mid=closeApproach.getMidpoint();
            Plane thePlane=planeThroughPointPerpendicularToLine(mid, closeApproach); //plane separating the two line segments
            Line intersection=planePlaneIntersection(z0, thePlane); //intersection of this plane with the xy-plane of the poly basis
            
            if (intersection==zeroLine) {continue;} //the two planes are parallel
            
            Point v1=intersection.getPointA()-midpoint;
            Point v2=intersection.getPointB()-midpoint;
            Point basis1=vectorInBasis(stdBasisToPolyBasis, v1);
            Point basis2=vectorInBasis(stdBasisToPolyBasis, v2);
            Line basisLine=Line(basis1,basis2); //find the intersection line in poly basis
            
            Line2D basisLine2d=lineToLine2D(basisLine); //intersection line in poly basis without z-component (z should be 0 anyway)
            if (closeApproach.getDistance()<compoundCylinder)
            {
                std::cout << "Error: cross section line is closer than cylinder radius. oa most likely too large\n";
                double closeDist=segmentSegmentDist(edge, refEdge);
                std::string different=(fabs(closeDist-closeApproach.getDistance())>EPS)?"???":"";
                std::cout << i << " " << j << " ";
                std::cout << lineOfClosestApproach(edge, refEdge,true).getDistance() << " ";
                std::cout << closeDist << " ";
                std::cout << different << " ";
                std::cout << basisLine2d.toString() << "\n\n";
            }
            
            crossSection2D.push_back(lineToLine2D(basisLine));
            if (symmetrize)
            {
                double newm=-1*basisLine2d.getSlope();
                double newb=basisLine2d.getYIntercept();
                Line2D reflect(newm,newb);
                crossSection2D.push_back(reflect);
            }
        }
    }
    return crossSection2D;
}