                lbl->Top = hgh;
                lft = lft + lbl->Width;

                count += 9;
                hgh += 15;
                i++;
            }

        }
        else{
            clabel = clabel->next;
        }
    }
    this->Frame71->Label212->Width = 225;
    lft = CB->Width + 10;
    lft = lft + this->Frame71->Label212->Width;
    this->Frame71->Label213->Width = 125;
    this->Frame71->Label213->Left = lft;
    lft = lft + this->Frame71->Label212->Width;
    lft = lft + this->Frame71->Label213->Width;

    if (this->clabel == NULL){
        this->Next_btn->Enabled = false;
    }
    update = true;
    /*  */
}

//---------------------------------------------------------------------------
void __fastcall TOutputFrm::Print_btnClick(TObject *Sender){
    if(Sender == NULL)
        return;
    
    TPrinter *prntr = Printer();
    TRect rect = Rect(10, 10, prntr->PageWidth - 10, prntr->PageHeight - 10);
    int CPH, RPH, C, R;
    label *lblptr;

    lblptr = HEAD;
    C = 615;
    R = 145;

    Application->CreateForm(__classid(TPrintview_frm), &Printview_frm);
    Printview_frm->Show();
    Printview_frm->Width = 315;
    Printview_frm->Height = 157;

    Printview_frm->Frame131->Height = 157;
    Printview_frm->Frame131->Width = 315;

    prntr->BeginDoc();
    prntr->Canvas->FillRect(rect);
    prntr->Canvas->Brush->Color = clBlack;
    RPH = 130;

    while(RPH <= (200 * 20)){
        CPH = 60;

        while((lblptr != NULL) && (!lblptr->Is_select))
            lblptr = lblptr->next;

        if(lblptr != NULL){
            // Row
            Printview_frm->Frame131->Label1->Caption = lblptr->header;
            Printview_frm->Frame131->Label2->Caption = lblptr->Artist;
            Printview_frm->Frame131->Label3->Caption = lblptr->title;
            Printview_frm->Frame131->Label4->Caption = lblptr->PDate;
            Printview_frm->PaintTo(prntr->Handle, CPH, RPH);
            CPH += C;