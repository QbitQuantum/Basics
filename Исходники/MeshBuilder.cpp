void MeshBuilder::computeBounds(Vector3& min, Vector3& max) {
    min = Vector3::inf(); 
    max = -min;

    int v;
    for (v = 0; v < triList.size(); ++v) {
        min = min.min(triList[v]);
        max = max.max(triList[v]);
    }
}