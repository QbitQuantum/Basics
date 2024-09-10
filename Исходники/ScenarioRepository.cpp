void scenario_repository_scan()
{
    IScenarioRepository * repo = GetScenarioRepository();
    repo->Scan();
}