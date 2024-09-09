//---------------------------------------------------------------------------

#ifndef ProjectJSONModuleH
#define ProjectJSONModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TButton *Button1;
	TLabel *Label1;
	TMemo *Memo1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
    void __fastcall ShowProgressDialog(const String& fileName); // no 
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
