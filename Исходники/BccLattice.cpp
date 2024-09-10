void BccLattice::addNeighborTetrahedron(const Vector3F & center, float h)
{
    Vector3F corner;
    int i;
	for(i=0; i < 6; i++) {
        corner = center + Vector3F(h * HexHeighborOffset[i][0], 
        h * HexHeighborOffset[i][1], 
        h * HexHeighborOffset[i][2]);
        
        add24Tetrahedron(corner, h);
    }
}