void GameHostX11::Impl::Run(Game & game)
{
    game.Initialize();

    while (!exitRequest) {
        clock.Tick();
        MessagePump();
        constexpr int64_t gamepadDetectionInterval = 240;
        if (((clock.GetFrameNumber() % gamepadDetectionInterval) == 1) && (clock.GetFrameRate() >= 30.0f)) {
            gamepad->EnumerateDevices();
        }
        gamepad->PollEvents();

        game.Update();
        RenderFrame(game);

        auto elapsedTime = clock.GetElapsedTime();

        if (elapsedTime < presentationInterval) {
            auto sleepTime = (presentationInterval - elapsedTime);
            std::this_thread::sleep_for(sleepTime);
        }
    }
}