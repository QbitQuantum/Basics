/** @brief Process mode with auto navigation guidance */
void NavigationManager::executeAutoNavMode()
{
	/* Execute guidance */
	_guidMgr.execute();

	/* Compute the command */
	_ctrl.execute();

	/* Move the force into body frame */
	math::Vector3f ctrlFrcDemB =
			system::system.dataPool.estAtt_IB.rotateQconjVQ(
					system::system.dataPool.ctrlFrcDemI);

	/* Scale the force and convert is to integer */
	system::system.dataPool.ctrlFrcDemB(
			ldexpf(ctrlFrcDemB.x, SCALE_TORSOR),
			ldexpf(ctrlFrcDemB.y, SCALE_TORSOR),
			ldexpf(ctrlFrcDemB.z, SCALE_TORSOR));

}