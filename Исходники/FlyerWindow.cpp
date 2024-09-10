/**
 * Displays window and updates camera, processes events until
 * window is closed
 */
void FlyerWindow::run()
{
    App.SetActive();
    while(App.IsOpened())
    {
        // Move camera forward
        float const elapsedTime = App.GetFrameTime();
        cam.moveForward(speed * elapsedTime);

        // Handle any events that have occured
        sf::Event Event;
        while(App.GetEvent(Event))
        {
            processEvent(Event);
        }

        // Update screen
        cam.look();
        paint();
        App.Display();
    }
}