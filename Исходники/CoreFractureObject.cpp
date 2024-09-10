void CoreFractureObject::fracture_indices(const Plane& plane) {
    Mesh* mesh = mesh_object_->mesh();
    
    // Create two new anonymous meshes for the pieces that splinter off
	// Vertex data will automatically be shared
	MeshPtr mesh1 = engine_->mesh(mesh);
	MeshPtr mesh2 = engine_->mesh(mesh);
    
    Box b1;
    Box b2;

	size_t index_count = 0;

    // Loop through each face, and divide them using the plane.  Some vertices
    // will go to one mesh, some will go to the other
	for (size_t g = 0; g < mesh->group_count(); g++) {
		mesh1->group(g, mesh->group(g));
		mesh2->group(g, mesh->group(g));

		for (size_t i = 2; i < mesh->index_count(g); i += 3) {
			uint32_t i0 = mesh->index(g, i-2);
			uint32_t i1 = mesh->index(g, i-1);
			uint32_t i2 = mesh->index(g, i-0);
			const Vector& v0 = mesh->vertex(i0).position;
			const Vector& v1 = mesh->vertex(i1).position;
			const Vector& v2 = mesh->vertex(i2).position;
			float d0 = plane.distance(v0);
			float d1 = plane.distance(v1);
			float d2 = plane.distance(v2);
	        
	        
			if (d0 <= 0 && d1 <= 0 && d2 <= 0) {
				// If all the vertices are on the lower half-space created by the
				// plane, then push the indices to the first buffer
				mesh1->index(g, mesh1->index_count(g), i0);
				mesh1->index(g, mesh1->index_count(g), i1);
				mesh1->index(g, mesh1->index_count(g), i2);
				b1.point(v0);
				b1.point(v1);
				b1.point(v2);
			} else {
				// If all the vertices are on the upper half-space created by the
				// plane, then push the indices to the second buffer
				mesh2->index(g, mesh2->index_count(g), i0);
				mesh2->index(g, mesh2->index_count(g), i1);
				mesh2->index(g, mesh2->index_count(g), i2);
				b2.point(v0);
				b2.point(v1);
				b2.point(v2);

				index_count += 3;
			}
		}
	}

    // Get the volume of bounding box to decide which half of the mesh is
    // bigger.  The bigger half stays with the current fracture object and the
    // smaller half goes with the new fracture object.
    float v1 = b1.volume();
    float v2 = b2.volume();

    // Sets the mass of the rigid bodies
    float mass = parent_->rigid_body()->mass();
    float m1 = v1 * mass / (v1 + v2);
    float m2 = v2 * mass / (v1 + v2);
    
    // Swap the mesh halves if v1 is smaller than v2 (mesh1 should always
    // have the largest mesh)
    if (v1 < v2) {
        swap(b1, b2);
        swap(m1, m2);
        swap(v1, v2);
        swap(mesh1, mesh2);
    }
    
    if (index_count > 20) {
        // Create a new fracture object that is an approximate "clone" of this
        // one.  Material, mesh, and other attributes should be copied, but
        // the indices will be different.
        CoreFractureObject* clone = create_clone();
        clone->mesh_object_->mesh(mesh2.get());   
        clone->parent()->rigid_body()->mass(m2);
        clone->parent()->rigid_body()->linear_velocity(parent_->rigid_body()->linear_velocity());
		parent_->fracture(clone->parent());
    }
    
    // Initialize the index buffer for this object
    mesh_object_->mesh(mesh1.get());
    parent_->rigid_body()->mass(m1);
    parent_->fracture(parent_);
}