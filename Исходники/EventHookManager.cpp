bool EventHookManager::RemoveHook(HWND const & targetWindow, UINT const & eventMin, UINT const & eventMax)
{
	// Check map for existing entry
	auto hash = std::hash<HWND>()(targetWindow) ^ std::hash<UINT>()(eventMin) ^ std::hash<UINT>()(eventMax);
	auto it = hooks.find(hash);
	if (it == hooks.end()) return false;

	// Erase
	if (it->second.winEventHook) UnhookWinEvent(it->second.winEventHook);
	auto erased = hooks.erase(hash);
	return erased == 1;
}