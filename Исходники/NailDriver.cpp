int NailDriver::checkContact(int numContacts, dContact* contacts, double dotThreshold, double distanceThreshold)
{
    Link* link_ = link();
    Vector3 muzzle = link_->p() + link_->R() * position;
    Vector3 norm = link_->R() * normal;

    int n = 0;
    for (int i=0; i < numContacts; ++i) {
	Vector3 pos(contacts[i].geom.pos);
	Vector3 v(contacts[i].geom.normal);

	float isParallel = (link_->R() * normal).dot(v);

	// Distance gripper (P: muzzle) and contact (A:pos)
	Vector3 pa;
	pa[0] = pos[0] - muzzle[0];
	pa[1] = pos[1] - muzzle[1];
	pa[2] = pos[2] - muzzle[2];

	float distance = fabs(norm.dot(pa));
        if (isParallel < dotThreshold && distance < distanceThreshold) {
	    n++;
	}
    }
    return n;
}