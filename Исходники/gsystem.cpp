void GSystem::calcDerivative_PositionCOMGlobal_Dq_2(RMatrix &DpDq_)
{
	int i;
	std::list<GCoordinate *>::iterator iter_pcoord;
	Vec3 DpDqi;

	DpDq_.SetZero(3, getNumCoordinates());
	for (i=0, iter_pcoord = pCoordinates.begin(); iter_pcoord != pCoordinates.end(); i++, iter_pcoord++) {
		DpDqi = getDerivative_PositionCOMGlobal_Dq_2(*iter_pcoord);
		DpDq_(0,i) = DpDqi[0];
		DpDq_(1,i) = DpDqi[1];
		DpDq_(2,i) = DpDqi[2];
	}
}