//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "apartamente.h"


TfrmMain *frmMain;

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DatabaseAfterConnect(TObject *Sender)
{
StatusBar->SimpleText="Conectat la '"+
						Database->Params->ValueFromIndex[0] + "@" +
						Database->AliasName + "'.";	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Iesier1Click(TObject *Sender)
{
Database->Close();
Application->Terminate();	
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
Query1->DatabaseName=Database->DatabaseName;
Query1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Adauga1Click(TObject *Sender)
{
frmAp->operatie="add";
frmAp->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1DblClick(TObject *Sender)
{

sqlSelect->Close();
sqlSelect->SQL->Clear();
sqlSelect->DatabaseName=Database->DatabaseName;
sqlSelect->SQL->Text="SELECT * from apartamente where id="+Trim(DBGrid1->SelectedField->DataSet->FieldByName("id")->AsString);
sqlSelect->Open();
frmAp->operatie="mod";
frmAp->id = DBGrid1->SelectedField->DataSet->FieldByName("id")->AsInteger;
frmAp->ShowModal();
}
//---------------------------------------------------------------------------

