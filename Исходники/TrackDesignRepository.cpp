void track_repository_scan()
{
    ITrackDesignRepository * repo = GetContext()->GetTrackDesignRepository();
    repo->Scan(LocalisationService_GetCurrentLanguage());
}