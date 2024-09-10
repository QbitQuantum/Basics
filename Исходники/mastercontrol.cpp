void MasterControl::CreateUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    //Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will control the camera
    world.cursor.uiCursor = new Cursor(context_);
    world.cursor.uiCursor->SetVisible(false);
    ui->SetCursor(world.cursor.uiCursor);

    //Set starting position of the cursor at the rendering window center
    world.cursor.uiCursor->SetPosition(graphics_->GetWidth()/2, graphics_->GetHeight()/2);

    //Construct new Text object, set string to display and font to use
//    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
//    instructionText->SetText("OG Tatt");
//    instructionText->SetFont(cache->GetResource<Font>("Fonts/infinite.ttf"), 23);
//    instructionText->SetColor(Color(0.666f, 1.0f, 0.23f, 0.42f));
//    //The text has multiple rows. Center them in relation to each other
//    instructionText->SetHorizontalAlignment(HA_CENTER);
//    instructionText->SetVerticalAlignment(VA_CENTER);
//    instructionText->SetPosition(0, ui->GetRoot()->GetHeight()/2.1);
}