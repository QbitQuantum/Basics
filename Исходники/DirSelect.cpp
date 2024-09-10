  Object* DirSelect::CreateButton()
  {
    Button *button;

    button=new Button();
    button->SetFlex(false,true);
    button->SetParent(this);
    button->SetWindow(GetWindow());

    return button;
  }