int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - music playing (streaming)");

    InitAudioDevice();              // Initialize audio device

    PlayMusicStream("resources/audio/guitar_noodling.ogg");         // Play music stream

    int framesCounter = 0;
    float timePlayed = 0.0f;
    //float volume = 1.0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;

        // Testing music fading from one file to another
/*
        if (framesCounter > 600)    // Wait for 10 seconds (600 frames)
        {
            volume -= 0.01;         // Decrement music volume level

            // When music volume level equal or lower than 0,
            // restore volume level and init another music file
            if (volume <= 0)
            {
                volume = 1.0;
                framesCounter = 0;
                PlayMusicStream("resources/audio/another_file.ogg");
            }

            SetMusicVolume(volume);
        }
*/
        if (IsWindowMinimized()) PauseMusicStream();
        else ResumeMusicStream();

        timePlayed = GetMusicTimePlayed()/GetMusicTimeLength()*100*4; // We scale by 4 to fit 400 pixels
        
        UpdateMusicStream();        // Update music buffer with new stream data
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("MUSIC SHOULD BE PLAYING!", 255, 200, 20, LIGHTGRAY);

            DrawRectangle(200, 250, 400, 12, LIGHTGRAY);
            DrawRectangle(200, 250, (int)timePlayed, 12, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}