void checkFieldFrm::makeGUI(wxString text){

    switch(field_index){
        case 1:
            index++;
            lblField[index] = new wxStaticText(this, ID_WXSTATICTEXT1, text, wxPoint(Xpos,Ypos), wxDefaultSize, 0, wxT("WxStaticText1"));                
            Xpos +=60;
            break;
        case 2:
            if(text=="CHAR" || text=="INT"){
                txtInput[index] = new wxTextCtrl(this, ID_WXEDIT1, wxT(""), wxPoint(Xpos,Ypos), wxSize(121, 19), 0, wxDefaultValidator);
                a.Printf("%d",index);
                txtInput[index]->SetValue(a);
                txtInput[index]->Enable(false);
                Ypos+=30;
                Xpos=30;
            }
            else{
            	txtInput[index] = new wxTextCtrl(this, ID_WXMEMO1, wxT(""), wxPoint(Xpos, Ypos), wxSize(185, 89), wxTE_MULTILINE, wxDefaultValidator, wxT("WxMemo1"));
                a.Printf("%d",index);
                txtInput[index]->SetValue(a);
            	txtInput[index]->SetMaxLength(0);
            	txtInput[index]->SetFocus();
            	txtInput[index]->SetInsertionPointEnd();
            	txtInput[index]->Enable(false);
            	Ypos+=100;
            	Xpos=30;
            }

            break;
        case 3:
            int length=0,integer,i=0;
            while(text[i]!='\0'){
                if((integer = ((int)text[i]-48))<10)    //checking for number
                    length=length*10+integer;
                i++;
            }
                txtInput[index]->SetMaxLength(length);
                break;
        }
}