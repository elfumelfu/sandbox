//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spatii.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ButtonWithColor"
#pragma link "JvCheckListBox"
#pragma link "JvExCheckLst"
#pragma resource "*.dfm"
TfrmSpatii *frmSpatii;
//---------------------------------------------------------------------------
__fastcall TfrmSpatii::TfrmSpatii(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpatii::ckbVitrinaClick(TObject *Sender)
{
txtVitrina->Enabled = ckbVitrina->Checked;
}
//---------------------------------------------------------------------------
