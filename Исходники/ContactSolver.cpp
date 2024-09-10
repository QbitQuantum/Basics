// Compute the two unit orthogonal vectors "t1" and "t2" that span the tangential friction plane
// for a contact manifold. The two vectors have to be such that : t1 x t2 = contactNormal.
void ContactSolver::computeFrictionVectors(const Vector3& deltaVelocity,
                                           ContactManifoldSolver& contact) const {

    assert(contact.normal.length() > 0.0);

    // Compute the velocity difference vector in the tangential plane
    Vector3 normalVelocity = deltaVelocity.dot(contact.normal) * contact.normal;
    Vector3 tangentVelocity = deltaVelocity - normalVelocity;

    // If the velocty difference in the tangential plane is not zero
    decimal lengthTangenVelocity = tangentVelocity.length();
    if (lengthTangenVelocity > MACHINE_EPSILON) {

        // Compute the first friction vector in the direction of the tangent
        // velocity difference
        contact.frictionVector1 = tangentVelocity / lengthTangenVelocity;
    }
    else {

        // Get any orthogonal vector to the normal as the first friction vector
        contact.frictionVector1 = contact.normal.getOneUnitOrthogonalVector();
    }

    // The second friction vector is computed by the cross product of the firs
    // friction vector and the contact normal
    contact.frictionVector2 = contact.normal.cross(contact.frictionVector1).getUnit();
}