//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "setari.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSetari *frmSetari;

#include "main.h"
//---------------------------------------------------------------------------
__fastcall TfrmSetari::TfrmSetari(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetari::imgSiglaClick(TObject *Sender)
{
ShellExecute(0, "open", "http://www.se-inchiriaza.ro", "", "",
		SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetari::txtEuroKeyPress(TObject *Sender, wchar_t &Key)
{
if( !((int)Key >= 48 && (int)Key<=57) && Key != VK_BACK &&
	 ( Key == '.' &&
	 ( (((TLabeledEdit *)Sender)->Text.Pos('.')>0) ||
	   (((TLabeledEdit *)Sender)->Text.Length()==0) )) )
	Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetari::FormShow(TObject *Sender)
{
txtEuro->Text=FloatToStrF(frmMain->setari.curs_eur,ffGeneral,7,4);
txtUsd->Text=FloatToStrF(frmMain->setari.curs_usd,ffGeneral,7,4);
txtMarja->Text=IntToStr(frmMain->setari.marja_cautare);
txtMoneda->ItemIndex=txtMoneda->Items->IndexOf(frmMain->setari.moneda_marja_cautare);
frmMain->ComboList(txtJudet, "den", "judete", false, "");
txtJudet->ItemIndex=txtJudet->Items->IndexOf(frmMain->setari.judet);
txtJudetChange(Sender);
txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf(frmMain->setari.localitate);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetari::txtJudetChange(TObject *Sender)
{
frmMain->ComboList(txtLocalitate, "den", "localitati", false, (" where judet = (SELECT id from judete where den = '"+ txtJudet->Text+ "')").t_str() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetari::btnLocalitateClick(TObject *Sender)
{
UnicodeString loc;
if (InputQuery("Adaugare localitate", "Introduceti localitatea:", loc) == true){

	insertQuery->DatabaseName=frmMain->Database->DatabaseName;
	insertQuery->InsertSQL->Text = "INSERT INTO localitati \
		(den, judet) VALUES ( '"  + loc +
		"', (SELECT id from judete where den = '" + txtJudet->Text +  "'))" ;
	insertQuery->ExecSQL(ukInsert);
	txtJudetChange(Sender);
	txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf(loc);
}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetari::btnSalveazaClick(TObject *Sender)
{
frmMain->setari.curs_eur = StrToFloat(txtEuro->Text);
frmMain->setari.curs_usd = StrToFloat(txtUsd->Text);
frmMain->setari.marja_cautare = StrToInt(txtMarja->Text);
frmMain->setari.moneda_marja_cautare = txtMoneda->Text;
frmMain->setari.judet = txtJudet->Text;
frmMain->setari.localitate = txtLocalitate->Text;

frmMain->setari.SaveToFile(SETARI_INI_FILE);
frmMain->ckbMarja->Caption = "± " + IntToStr(frmMain->setari.marja_cautare) + " " + frmMain->setari.moneda_marja_cautare;
frmMain->ckbClApMarja->Caption = "± " + IntToStr(frmMain->setari.marja_cautare) + " " + frmMain->setari.moneda_marja_cautare;
frmSetari->Close();
}
//---------------------------------------------------------------------------

