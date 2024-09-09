//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProjectJSONModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject* Sender)
{
    // Set filter for dialog (only JSON files)
    OpenDialog1->Filter = "JSON files (*.json)|*.json";

    // Set initial directory (optional)
    OpenDialog1->InitialDir = "C:\\";

    // Show dialog
    if (OpenDialog1->Execute())
    {
        // If user selected a file, get its name
        UnicodeString selectedFileName = OpenDialog1->FileName;
        int dotPos = selectedFileName.LastDelimiter(L".");

        // Check if dot is found
        if (dotPos > 0)
        {
            UnicodeString fileExtension = selectedFileName.SubString(dotPos + 1, selectedFileName.Length() - dotPos);

            // Check if file extension is "json"
            if (fileExtension.LowerCase() == "json")
            {
                Label1->Caption = selectedFileName;
                Memo1->Lines->LoadFromFile(selectedFileName);
                Memo1->ReadOnly = true;
            }
            else
            {
                // Show error message if extension does not match
                ShowMessage("The selected file is not a JSON file.");
            }
        }
        else
        {
            // Show error message if dot is not found
            ShowMessage("The selected file does not have an extension.");
        }
    }
}
//---------------------------------------------------------------------------