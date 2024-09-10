    void extract_mesh(const C3t3& c3t3,
            MatrixFr& vertices, MatrixIr& faces, MatrixIr& voxels) {
        const Tr& tr = c3t3.triangulation();
        size_t num_vertices = tr.number_of_vertices();
        size_t num_faces = c3t3.number_of_facets_in_complex();
        size_t num_voxels = c3t3.number_of_cells_in_complex();

        vertices.resize(num_vertices, 3);
        faces.resize(num_faces, 3);
        voxels.resize(num_voxels, 4);

        std::map<Tr::Vertex_handle, int> V;
        size_t inum = 0;
        for(auto vit = tr.finite_vertices_begin();
                vit != tr.finite_vertices_end(); ++vit) {
            V[vit] = inum;
            const auto& p = vit->point();
            vertices.row(inum) = Vector3F(p.x(), p.y(), p.z()).transpose();
            assert(inum < num_vertices);
            inum++;
        }
        assert(inum == num_vertices);

        size_t face_count = 0;
        for(auto fit = c3t3.facets_in_complex_begin();
                fit != c3t3.facets_in_complex_end(); ++fit) {
            assert(face_count < num_faces);
            for (int i=0; i<3; i++) {
                if (i != fit->second) {
                    const auto& vh = (*fit).first->vertex(i);
                    assert(V.find(vh) != V.end());
                    const int vid = V[vh];
                    faces(face_count, i) = vid;
                }
            }
            face_count++;
        }
        assert(face_count == num_faces);

        size_t voxel_count = 0;
        for(auto cit = c3t3.cells_in_complex_begin() ;
                cit != c3t3.cells_in_complex_end(); ++cit ) {
            assert(voxel_count < num_voxels);
            for (int i=0; i<4; i++) {
                assert(V.find(cit->vertex(i)) != V.end());
                const size_t vid = V[cit->vertex(i)];
                voxels(voxel_count, i) = vid;
            }
            voxel_count++;
        }
        assert(voxel_count == num_voxels);
    }