//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "agentii.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAgentii *frmAgentii;
//---------------------------------------------------------------------------
__fastcall TfrmAgentii::TfrmAgentii(TComponent* Owner)
	: TForm(Owner)
{
operatie="add";
id = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAgentii::btnStergeTotClick(TObject *Sender)
{
txtNume->Text= "";
txtTelefon->Text= "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmAgentii::btnRenuntaClick(TObject *Sender)
{
btnStergeTotClick(Sender);
frmAgentii->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAgentii::btnSalveazaClick(TObject *Sender)
{

if (txtTelefon->Text.Length() < 10 ) {
    ShowMessage("Introduceti numarul de telefon!!!");
	return ;
}

SQL->DatabaseName=frmMain->Database->DatabaseName;
SQL->InsertSQL->Text = "INSERT INTO agentii (nume, telefon ) VALUES ( '" +
		txtNume->Text + "', '" +
		txtTelefon->Text + "')";
		//TODO update judet, localitate,
SQL->ModifySQL->Text = "UPDATE agentii SET  \
		nume = '" + txtNume->Text + "'," +
		"telefon = '" + txtTelefon->Text + "' " +
		"WHERE id = " + IntToStr(frmAgentii->id);
if (frmAgentii->operatie == "add")
	SQL->InsertSQL->SaveToFile("myLog.txt" );
else  if (frmAgentii->operatie == "mod")
	SQL->ModifySQL->SaveToFile("myLog.txt" );
try {
	if (frmAgentii->operatie == "add")
		SQL->ExecSQL(ukInsert);
	else if (frmAgentii->operatie == "mod")
        SQL->ExecSQL(ukModify);

	} catch (EDatabaseError &OtherDatabaseError) {
		if (frmAgentii->operatie == "add")
			ShowMessage(SQL->InsertSQL->Text);
		else if (frmAgentii->operatie == "mod")
			ShowMessage(SQL->ModifySQL->Text);
			ShowMessage(OtherDatabaseError.ToString());
		}

frmMain->Query1->Close();
frmMain->Query1->Open();
frmAgentii->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAgentii::FormShow(TObject *Sender)
{

btnStergeTotClick(Sender);
if (operatie == "mod")
	{
	txtNume->Text=frmMain->sqlSelect->FieldByName("nume")->AsAnsiString;
	txtTelefon->Text= frmMain->sqlSelect->FieldByName("telefon")->AsAnsiString;
	}
}
//---------------------------------------------------------------------------

