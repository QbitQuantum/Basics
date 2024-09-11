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
    if (!OpenDialog1->Execute())
    {
        return; // User canceled the dialog
    }

    // Get the selected file name
    UnicodeString selectedFileName = OpenDialog1->FileName;

    // Check if the file has a valid extension
    if (!IsValidJsonFile(selectedFileName))
    {
        return;
    }

    // Display the selected file name
    Label1->Caption = selectedFileName;

    // Read and display the JSON content
    if (!DisplayJsonContent(selectedFileName))
    {
        return;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::IsValidJsonFile(const UnicodeString& fileName)
{
    int dotPos = fileName.LastDelimiter(L".");
    if (dotPos < 0)
    {
        ShowMessage("The selected file does not have an extension.");
        return false;
    }

    UnicodeString fileExtension = fileName.SubString(dotPos + 1, fileName.Length() - dotPos).LowerCase();
    if (fileExtension != "json")
    {
        ShowMessage("The selected file is not a JSON file.");
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::DisplayJsonContent(const UnicodeString& fileName)
{
    if (!TFile::Exists(fileName))
    {
        ShowMessage("Файл не найден");
        return false;
    }

    UnicodeString jsonContent = TFile::ReadAllText(fileName);

    TJSONValue* jsonValue = TJSONObject::ParseJSONValue(jsonContent);
    if (!jsonValue)
    {
        ShowMessage("Failed to parse JSON content.");
        return false;
    }

    if (TJSONArray* jsonArray = (TJSONArray*)(jsonValue))
    {
        for (int i = 0; i < jsonArray->Count; i++)
        {
            Memo1->Lines->Add(jsonArray->Items[i]->Format());
        }
    }
    else
    {
        ShowMessage("The JSON content is not an array.");
        delete jsonValue;
        return false;
    }

    Memo1->ReadOnly = true;
    delete jsonValue;
    return true;
}
//---------------------------------------------------------------------------