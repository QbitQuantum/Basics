void SceneAndUILoad::CreateUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Set up global UI style into the root UI element
    XMLFile* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    ui->GetRoot()->SetDefaultStyle(style);

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will interact with the UI
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto();
    ui->SetCursor(cursor);
    // Set starting position of the cursor at the rendering window center
    Graphics* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);

    // Load UI content prepared in the editor and add to the UI hierarchy
    SharedPtr<UIElement> layoutRoot = ui->LoadLayout(cache->GetResource<XMLFile>("UI/UILoadExample.xml"));
    ui->GetRoot()->AddChild(layoutRoot);

    // Subscribe to button actions (toggle scene lights when pressed then released)
    Button* button = static_cast<Button*>(layoutRoot->GetChild("ToggleLight1", true));
    if (button)
        SubscribeToEvent(button, E_RELEASED, URHO3D_HANDLER(SceneAndUILoad, ToggleLight1));
    button = static_cast<Button*>(layoutRoot->GetChild("ToggleLight2", true));
    if (button)
        SubscribeToEvent(button, E_RELEASED, URHO3D_HANDLER(SceneAndUILoad, ToggleLight2));
}