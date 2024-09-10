void RotatePanorama::rotatePano(PanoramaData& panorama, const Matrix3& transformMat)
{
    for (unsigned int i = 0; i < panorama.getNrOfImages(); i++)
    {
        const SrcPanoImage & image = panorama.getImage(i);
        SrcPanoImage copy = image;
        double y = image.getYaw();
        double p = image.getPitch();
        double r = image.getRoll();
        Matrix3 mat;
        mat.SetRotationPT(DEG_TO_RAD(y), DEG_TO_RAD(p), DEG_TO_RAD(r));
        DEBUG_DEBUG("rotation matrix (PT) for img " << i << " << ypr:" << y << " " << p << " " << r << std::endl << mat);
        Matrix3 rotated;
        rotated = transformMat * mat;
        DEBUG_DEBUG("rotation matrix after transform: " << rotated);
        rotated.GetRotationPT(y,p,r);
        y = RAD_TO_DEG(y);
        p = RAD_TO_DEG(p);
        r = RAD_TO_DEG(r);
        DEBUG_DEBUG("rotated angles of img " << i << ": " << y << " " << p << " " << r);
        
        // Don't update a variable linked to a variable we already updated.
        conditional_set(Yaw, y);
        conditional_set(Pitch, p);
        conditional_set(Roll, r);
        if(image.getX()!=0.0 || image.getY()!=0.0 || image.getZ()!=0.0)
        {
            // rotate translation vector
            Vector3 vecRot=transformMat.Inverse().TransformVector(Vector3(image.getZ(), image.getX(), image.getY()));
            conditional_set(X, vecRot.y);
            conditional_set(Y, vecRot.z);
            conditional_set(Z, vecRot.x);
            // rotate translation plane
            mat.SetRotationPT(DEG_TO_RAD(image.getTranslationPlaneYaw()), DEG_TO_RAD(image.getTranslationPlanePitch()), 0.0);
            rotated = transformMat * mat;
            rotated.GetRotationPT(y,p,r);
            conditional_set(TranslationPlaneYaw, RAD_TO_DEG(y));
            conditional_set(TranslationPlanePitch, RAD_TO_DEG(p));
        };
        panorama.setImage(i, copy);
        panorama.imageChanged(i);
    }
}