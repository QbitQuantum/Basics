/**
 * @brief Predict the efficiecy loss of an existing miner if another one is constructed closeby.
 * @return Efficiency loss as negative value.
 */
static float RGSPredictEfficiencyLoss(Entity& miner, vec3_t newMinerOrigin) {
	float distance               = Distance(miner.oldEnt->s.origin, newMinerOrigin);
	float oldPredictedEfficiency = miner.Get<MiningComponent>()->Efficiency(true);
	float newPredictedEfficiency = oldPredictedEfficiency * MiningComponent::InterferenceMod(distance);
	float efficiencyLoss         = newPredictedEfficiency - oldPredictedEfficiency;

	buildpointLogger.Debug("Predicted efficiency loss of existing miner: %f - %f = %f.",
	                       oldPredictedEfficiency, newPredictedEfficiency, efficiencyLoss);

	return efficiencyLoss;
}