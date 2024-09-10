void NavMesh::AddPoly(std::vector<double>& points, std::vector<int>& segments, std::vector<double>& holes, std::vector<Vector2>& polyPoints) {
    int index = (int)points.size()/2;
    
    Vector2 holePosition = 0;
    for (int i=0; i<polyPoints.size(); i++) {
        points.push_back(polyPoints[i].x);
        points.push_back(polyPoints[i].y);
    
        segments.push_back(index + i);
        segments.push_back(index + ((i==polyPoints.size()-1) ? 0 : i + 1));
        
        holePosition += polyPoints[i];
        
    }
    holePosition *= (1.0f / polyPoints.size());
    
     for (int i=0; i<polyPoints.size(); i++) {
        Vector2 toCenter = holePosition - polyPoints[i];
        toCenter.Normalize();
        holes.push_back(polyPoints[i].x + toCenter.x * 4);
        holes.push_back(polyPoints[i].y + toCenter.y * 4);
    }
    
}