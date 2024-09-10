void TetrahedralMesh::computeFaceNormals(){
	std::vector<Eigen::Vector3d> tri(3);
	std::vector<Eigen::Vector3d> normals(4);
	face_normals_.resize(tets_.size());
	for(int i=0; i<(int)tets_.size(); i++){
		for(int j=0; j<4; j++){
			tri[0] = points_[tets_[i][faces[j][0]]];
      tri[1] = points_[tets_[i][faces[j][1]]];
      tri[2] = points_[tets_[i][faces[j][2]]];			
      Eigen::Vector3d n = (tri[1]-tri[0]).cross(tri[2]-tri[0]);
      n.normalize();
      normals[j] = n;
		}
		face_normals_[i] = normals;
	}
}