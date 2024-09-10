void WaveController::update(sf::Time const& elapsedTime) {
	mTimeSinceWave += elapsedTime.asSeconds();

	if (!mWaveQueue.empty() && isTimeToSpawnWave()) {
		spawnWave();
	}
}