Fl_Font_Browser::Fl_Font_Browser():Fl_Window(100,100,550-60,332-5,"Font Browser") 
{
      lst_Font = new Fl_Browser(15, 55-5, 195, 159);
      lst_Font->labelsize(12);
      lst_Font->textsize(12);
      lst_Font->callback((Fl_Callback*)cb_FontName_Selected, (void*)(lst_Font->parent()));
      lst_Font->type(FL_HOLD_BROWSER);
    
      txt_InputFont = new Fl_Input(15, 31-5, 195, 24, "Font:");
      txt_InputFont->labelsize(12);
      txt_InputFont->textsize(12);
      txt_InputFont->align(FL_ALIGN_TOP_LEFT);
      txt_InputFont->when(FL_WHEN_ENTER_KEY);
      txt_InputFont->callback((Fl_Callback*)cb_txtInputFontName, (void*)(txt_InputFont->parent()));
    
      lst_Style = new Fl_Browser(215, 56-5, 155-60, 159);
      lst_Style->labelsize(12);
      lst_Style->type(FL_HOLD_BROWSER);
      lst_Style->textsize(12); 
      lst_Style->callback((Fl_Callback*)cb_StyleSelected, (void*)(lst_Style->parent()));   
       
      txt_InputStyle = new Fl_Input(215, 32-5, 155-60, 24, "Syle:");
      txt_InputStyle->labelsize(12);
      txt_InputStyle->align(FL_ALIGN_TOP_LEFT);
      txt_InputStyle->textsize(12);    
      txt_InputStyle->callback((Fl_Callback*)cb_txtInputFontStyle, (void*)(txt_InputStyle->parent()));
      
      lst_Size = new Fl_Browser(375-60, 56-5, 75, 159);
      lst_Size->labelsize(12);
      lst_Size->type(FL_HOLD_BROWSER);
      lst_Size->textsize(12); 
      lst_Size->callback((Fl_Callback*)cb_FontSize_Selected, (void*)(lst_Size->parent()));   
      
      txt_InputSize = new Fl_Input(375-60, 32-5, 75, 24, "Size:");
      txt_InputSize->labelsize(12);
      txt_InputSize->align(FL_ALIGN_TOP_LEFT);
      txt_InputSize->textsize(12);    
      txt_InputSize->callback((Fl_Callback*)cb_txtInputFontSize, (void*)(txt_InputSize->parent()));
      
      btn_OK =new Fl_Button(475-60, 35-5, 64, 20, "&OK");
      btn_OK->shortcut(0x8006f);
      btn_OK->labelfont(1);
      btn_OK->labelsize(12);
      btn_OK->callback((Fl_Callback*)cb_okBtn_Red );
         
      btn_Cancel =new Fl_Button(475-60, 60-5, 64, 20, "Cancel");
      btn_Cancel->labelsize(12);
      btn_Cancel->callback((Fl_Callback*)cb_Cancel, (void *)(btn_Cancel->parent()));
    
    
       Fl_Box* o = new Fl_Box(15, 220-5, 20, 10, "Properties");
       
       o->box(FL_BORDER_FRAME);
       o->labelsize(12);
       o->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
      
        btn_Check1= new Fl_Check_Button(40-20, 250-5-5, 100, 15, "Strikethrough");
        btn_Check1->down_box(FL_DOWN_BOX);
        btn_Check1->labelsize(12);
        btn_Check1->callback((Fl_Callback*)cb_Strikethrough, (void *)(btn_Check1->parent()));
      
        btn_Check2 = new Fl_Check_Button(40-20, 270-5-5, 100, 15, "Underline");
        btn_Check2->down_box(FL_DOWN_BOX);
        btn_Check2->labelsize(12);
        btn_Check2->callback((Fl_Callback*)cb_UnderLine, (void *)(btn_Check2->parent()));
    
        btn_Color = new Fl_Button(40-20, 307-10-5, 90, 23, "Color:");
        btn_Color->down_box(FL_BORDER_BOX);
        btn_Color->labelsize(12);
        btn_Color->align(FL_ALIGN_TOP_LEFT);
        btn_Color->color(FL_BLACK);
        btn_Color->callback((Fl_Callback*)cb_Color_Select, (void *)(lst_Size->parent()));

     
    { Fl_Group* o = new Fl_Group(130, 220-5, 256+180, 82, "Example");
      o->box(FL_BORDER_FRAME);
      o->labelsize(12);
      o->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
      { box_Example = new Fl_Font_Preview_Box(132-10, 241-5, 227+50+35+10, 48, "AaBbCcDdEeFfGgHhIi");
        box_Example->box(FL_DOWN_BOX);
        box_Example->labelsize(12);
        box_Example->align(FL_ALIGN_WRAP|FL_ALIGN_CLIP|FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      }
      o->end();
    }
     set_modal();
     end();
 // Initializations 
  pickedsize = 14; // Font Size to be used
          //
  int k =   Fl::set_fonts(0); // Nr of fonts available on the server
  
  for(int i= 0; i < k; i++) 
  {
    int t;
    const char *name = Fl::get_font_name((Fl_Font)i,&t);
    char buffer[128];

// Load the font list .. Ignore the bold and italic types of the font
     if(!((t & FL_BOLD) ||(t & FL_ITALIC)))
     {
        sprintf(buffer, "%s",name);
        lst_Font->add(buffer);
     }
  }
     /* FL_Browser uses the symbol "@" as a formating char. There are some fonts that there 
      names starts with char "@".       We need to disable this     
   */  
     lst_Font->format_char(0);
       
  
  // Sort the font Alphabetically
  ForwardSort(lst_Font);
  
  lst_Font->value(1); // Select the first font in the list
  lst_Style->value(1);  
  lst_Font->do_callback();  // Do font selected callback .. to draw the preview
  lst_Style->do_callback();
  this->callback_ = 0;  // Initialize Widgets callback 
  this->data_ = 0;      // And the data
}