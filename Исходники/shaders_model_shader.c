int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - model shader");

    // Define the camera to look into our 3d world
    Camera camera = {{ 3.0, 3.0, 3.0 }, { 0.0, 1.5, 0.0 }, { 0.0, 1.0, 0.0 }};

    Model dwarf = LoadModel("resources/model/dwarf.obj");                   // Load OBJ model
    Texture2D texture = LoadTexture("resources/model/dwarf_diffuse.png");   // Load model texture
    Shader shader = LoadShader("resources/shaders/base.vs",
                               "resources/shaders/grayscale.fs");           // Load model shader

    SetModelShader(&dwarf, shader);         // Set shader effect to 3d model
    SetModelTexture(&dwarf, texture);       // Bind texture to model

    Vector3 position = { 0.0, 0.0, 0.0 };   // Set model position

    // Setup orbital camera
    SetCameraMode(CAMERA_ORBITAL);          // Set an orbital camera mode
    SetCameraPosition(camera.position);     // Set internal camera position to match our camera position
    SetCameraTarget(camera.target);         // Set internal camera target to match our camera target

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);              // Update internal camera and our camera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Begin3dMode(camera);

        DrawModel(dwarf, position, 2.0f, WHITE);   // Draw 3d model with texture

        DrawGrid(10.0, 1.0);     // Draw a grid

        End3dMode();

        DrawText("(c) Dwarf 3D model by David Moreno", screenWidth - 200, screenHeight - 20, 10, GRAY);

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);       // Unload shader
    UnloadTexture(texture);     // Unload texture
    UnloadModel(dwarf);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}