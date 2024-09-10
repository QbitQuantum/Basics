    /*!
     Generate a coorinate system from a vector.
     This method is useful for generate a tangent space coordinate system for isotropic BRDFs.
     
     @param vector1 vector from which the coordinate system is constructed. This must be normalized.
     @param vector2 second axis obtained.
     @param vector3 third axis obtained.
     */
    inline static void generateCoodinateSystem(const Vector3D& vector1, Vector3D& vector2, Vector3D& vector3) {

        if (std::fabs(vector1.x) > std::fabs(vector1.y)) {
            
            vector2 = Vector3D(vector1.z, 0, -vector1.x);
        } else {
            
            vector2 = Vector3D(0, -vector1.z, vector1.y);
        }
        
        vector2.normalize();
        
        vector3 = vector1.cross(vector2);
        vector3.normalize();
    }