void HealthComponent::HandleHeal(float amount, gentity_t* source) {
	if (health <= 0.0f) return;
	if (health >= maxHealth) return;

	// Only heal up to maximum health.
	amount = std::min(amount, maxHealth - health);

	if (amount <= 0.0f) return;

	healthLogger.Debug("Healing: %3.1f (%3.1f → %3.1f)", amount, health, health + amount);

	health += amount;
	ScaleDamageAccounts(amount);
}