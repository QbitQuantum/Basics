int PoeditApp::OnExit()
{
    TranslationMemory::CleanUp();

#ifdef USE_SPARKLE
    Sparkle_Cleanup();
#endif // USE_SPARKLE
#ifdef __WXMSW__
    win_sparkle_cleanup();
#endif

    u_cleanup();

    return wxApp::OnExit();
}