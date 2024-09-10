 Windows::UI::Xaml::Controls::Control^ EditBoxWinRT::createTextBox()
 {
   auto textBox = ref new TextBox;
   textBox->BorderThickness = 0;
   textBox->Name = EDIT_BOX_XAML_NAME;
   textBox->Width = _size.Width;
   textBox->Height = _size.Height;
   textBox->Foreground = ref new Media::SolidColorBrush(_color);
   textBox->FontSize = _fontSize;
   textBox->FontFamily = ref new Media::FontFamily(_fontFamily);
   textBox->MaxLength = _maxLength;
   textBox->AcceptsReturn = _multiline;
   textBox->TextWrapping = _multiline ? TextWrapping::Wrap : TextWrapping::NoWrap;
   textBox->Text = _initialText;
   setInputScope(textBox);
   _setTextHorizontalAlignment(textBox);
   _changeToken = textBox->TextChanged += ref new Windows::UI::Xaml::Controls::TextChangedEventHandler(this, &cocos2d::ui::EditBoxWinRT::onTextChanged);
   return textBox;
 }