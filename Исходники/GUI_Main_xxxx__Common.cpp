//---------------------------------------------------------------------------
void GUI_Main_xxxx__Common::Fill () 
{
    //Preparing
    Updating=true;
    
    //Showing
    ZtringListList List;
    List.Separator_Set(0, EOL);
    List.Separator_Set(1, _T(","));
    List.Write(Fill_Content());

    //Elminating unuseful info from filenames
    FileName_Before.clear();
    if (List.size()==2 && !List[1].empty())
    {
        size_t ToDelete=List[1][0].rfind(PathSeparator);
        if (ToDelete!=string::npos)
        {
            FileName_Before=List[1][0].substr(0, ToDelete+1);
            List[1][0].erase(0, ToDelete+1);
        }
    }
    else if (List.size()>1 && !List[1].empty())
    {
        size_t ToDelete;
        size_t File_Pos;
        for (ToDelete=0; ToDelete<List[1][0].size(); ToDelete++)
        {
            char Char_File1=List[1][0][ToDelete];
            for (File_Pos=2; File_Pos<List.size(); File_Pos++)
                if (ToDelete>=List[File_Pos][0].size() || List[File_Pos][0][ToDelete]!=Char_File1)
                    break;
            if (File_Pos!=List.size())
                break;
        }

        ToDelete=List[1][0].rfind(PathSeparator, ToDelete);
        if (ToDelete!=string::npos)
        {
            FileName_Before=List[1][0].substr(0, ToDelete+1);
            for (File_Pos=1; File_Pos<List.size(); File_Pos++)
                List[File_Pos][0].erase(0, ToDelete+1);
        }
    }

    if (List.empty() || List[0].empty())
    {
        setRowCount(0);
        setColumnCount(0);

        //Preparing
        Updating=false;

        return;
    }

    //Forcing reset, else this seems to be some Qt bug in the table display
    setRowCount(0);
    setColumnCount(0);

    //Filling - HorizontalHeader
    setRowCount((int)List.size()-1);
    size_t ColumnMissing_Count=0;
    for (size_t Option=0; Option<Main->Preferences->Group_Options_Count_Get(Fill_Group()); Option++)
        if (!Main->Menu_Fields_CheckBoxes[Fill_Group()*options::MaxCount+Option]->isChecked())
            ColumnMissing_Count++;
    setColumnCount((int)(List[0].size()-ColumnMissing_Count));
    ColumnMissing_Count=0;
    for (size_t Data_Pos=0; Data_Pos<List[0].size(); Data_Pos++)
        if (Data_Pos==0 || Main->Menu_Fields_CheckBoxes[Fill_Group()*options::MaxCount+Data_Pos-1]->isChecked())
        {
            QTableWidgetItem* Item=new QTableWidgetItem(QString().fromUtf8(List[0][Data_Pos].To_Local().c_str()));
            Item->setToolTip(Columns_ToolTip(List[0][Data_Pos]));
            setHorizontalHeaderItem((int)(Data_Pos-ColumnMissing_Count), Item);
        }
        else
            ColumnMissing_Count++;

    //Filling - VerticalHeader and content 
    for (size_t File_Pos=1; File_Pos<List.size(); File_Pos++)
    {
        if (List[File_Pos].empty())
            List[File_Pos].resize(1); //Empty filename, we need to manualy add it.
        ColumnMissing_Count=0;
        for (size_t Data_Pos=0; Data_Pos<List[0].size(); Data_Pos++)
            if (Data_Pos==0 || Main->Menu_Fields_CheckBoxes[Fill_Group()*options::MaxCount+Data_Pos-1]->isChecked())
            {
                QTableWidgetItem* Item;
                if (Data_Pos<List[File_Pos].size())
                {
                    ZenLib::Ztring Value=List[File_Pos][Data_Pos];
                    Value.FindAndReplace(EOL, "\n", 0, Ztring_Recursive);
                    Item=new QTableWidgetItem(QString().fromUtf8(Value.To_Local().c_str()));
                    Item->setToolTip(Columns_ToolTip(List[0][Data_Pos]));
                }
                else
                    Item=new QTableWidgetItem(QString());

                if (!C->IsValid_Get(FileName_Before+List[File_Pos][0])
                 || (Data_Pos<List[File_Pos].size() && !Fill_Enabled(FileName_Before+List[File_Pos][0], List[0][Data_Pos], List[File_Pos][Data_Pos])))
                    Item->setFlags(Item->flags()&((Qt::ItemFlags)-1-Qt::ItemIsEnabled));
                setItem((int)File_Pos-1, (int)(Data_Pos-ColumnMissing_Count), Item);
            }
            else
                ColumnMissing_Count++;
    }

    //Configuring
    Colors_Update();
    resizeColumnsToContents();
    setSortingEnabled(true);

    //Preparing
    Updating=false;
}