//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//user include
#include "main.h"

TfrmLogin *frmLogin;
//---------------------------------------------------------------------------
__fastcall TfrmLogin::TfrmLogin(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmLogin::btnExitClick(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLogin::btnLoginClick(TObject *Sender)
{
frmMain->Database->Params->Clear();
frmMain->Database->Params->Add("USER NAME="+Trim((txtUtilizator->Text)));
frmMain->Database->Params->Add("PASSWORD="+Trim((txtParola->Text)));
try
	{
	frmMain->Database->Open();
	frmLogin->Close();
	}
catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmLogin::FormClose(TObject *Sender, TCloseAction &Action)
{
Action=caFree; 
}
//---------------------------------------------------------------------------
