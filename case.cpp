//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "case.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ButtonWithColor"
#pragma resource "*.dfm"

#include "main.h"
#include "imagine.h"

TfrmCase *frmCase;

UnicodeString poza1, poza2, poza3, poza4;
UnicodeString imgPath = ExtractFileDir(Application->ExeName) + "\\poze\\";

//---------------------------------------------------------------------------
__fastcall TfrmCase::TfrmCase(TComponent* Owner)
	: TForm(Owner)
{
operatie = "add";
id = -1;
inchiriat = 0;
poza1=NULL;
poza2=NULL;
poza3=NULL;
poza4=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCase::btnStergeTotClick(TObject *Sender)
{
txtJudet->ItemIndex=txtJudet->Items->IndexOf(frmMain->setari.judet);
txtJudetChange(Sender);
txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf(frmMain->setari.localitate);
txtLocalitateChange(Sender);
txtNrcam->ItemIndex= -1;
txtZona->ItemIndex= -1;
txtStrada->Text= "";
txtPret->Text= "";
txtMoneda->ItemIndex=-1;
txtGs->Text= "";
memAltele->Lines->Clear();
CheckListBox1->CheckAll(cbUnchecked, False, False);
rgMobilat->ItemIndex=-1;
rgUtilat->ItemIndex=-1;
txtNume->Text = "";
txtTel->Text = "";
memInfo->Text = "";
txtDataExpirarii->DateTime=Date();
imgPoza1->Picture->Bitmap->FreeImage();
imgPoza2->Picture->Bitmap->FreeImage();
imgPoza3->Picture->Bitmap->FreeImage();
imgPoza4->Picture->Bitmap->FreeImage();
imgPoza1->Picture=imgFaraPoza->Picture;
imgPoza2->Picture=imgFaraPoza->Picture;
imgPoza3->Picture=imgFaraPoza->Picture;
imgPoza4->Picture=imgFaraPoza->Picture;
poza1=NULL;
poza2=NULL;
poza3=NULL;
poza4=NULL;

}
//---------------------------------------------------------------------------

void __fastcall TfrmCase::btnRenuntaClick(TObject *Sender)
{
btnStergeTotClick(Sender);
frmCase->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCase::FormShow(TObject *Sender)
{
UnicodeString Mobilat, Utilat;
btnStergeTotClick(Sender);
frmCase->Caption = "Adauga casa";
Label7->Visible=false;
Label8->Visible=false;
frmMain->ComboList(txtJudet, "den", "judete", false, "");
txtJudet->ItemIndex=txtJudet->Items->IndexOf(frmMain->setari.judet);
txtJudetChange(Sender);
txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf(frmMain->setari.localitate);
txtLocalitateChange(Sender);
txtZona->ItemIndex=-1;

if (frmCase->operatie == "mod")
	{

	frmCase->Caption = "Modifica casa";

	txtNrcam->ItemIndex=txtNrcam->Items->IndexOf(frmMain->sqlSelect->FieldByName("nrcam")->AsAnsiString);

	txtJudet->ItemIndex=txtJudet->Items->IndexOf(Trim(frmMain->sqlSelect->FieldByName("judet")->AsAnsiString));
	txtJudetChange(Sender);
	txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf( Trim(frmMain->sqlSelect->FieldByName("localitate")->AsAnsiString));
	txtLocalitateChange(Sender);
	txtZona->ItemIndex=txtZona->Items->IndexOf(frmMain->sqlSelect->FieldByName("zona")->AsAnsiString);
	txtStrada->Text= frmMain->sqlSelect->FieldByName("strada")->AsAnsiString;
	txtPret->Text= frmMain->sqlSelect->FieldByName("pret")->AsAnsiString;
	if (txtPret->Text == "0") {
		txtPret->Text = "";
	}
	txtMoneda->ItemIndex = txtMoneda->Items->IndexOf(frmMain->sqlSelect->FieldByName("moneda")->AsAnsiString);
	txtGs->Text= frmMain->sqlSelect->FieldByName("grupsanitar")->AsAnsiString;
	if (txtGs->Text == "0") {
		txtGs->Text = "";
	}
	memAltele->Text = frmMain->sqlSelect->FieldByName("altele")->AsAnsiString;
	CheckListBox1->Checked[0]=frmMain->sqlSelect->FieldByName("balcon")->AsInteger;
	CheckListBox1->Checked[1]=frmMain->sqlSelect->FieldByName("gresie")->AsInteger;
	CheckListBox1->Checked[2]=frmMain->sqlSelect->FieldByName("faianta")->AsInteger;
	CheckListBox1->Checked[3]=frmMain->sqlSelect->FieldByName("termopan")->AsInteger;
	CheckListBox1->Checked[4]=frmMain->sqlSelect->FieldByName("parchet")->AsInteger;
	CheckListBox1->Checked[5]=frmMain->sqlSelect->FieldByName("um")->AsInteger;
	CheckListBox1->Checked[6]=frmMain->sqlSelect->FieldByName("ct")->AsInteger;
	CheckListBox1->Checked[7]=frmMain->sqlSelect->FieldByName("ac")->AsInteger;
	CheckListBox1->Checked[8]=frmMain->sqlSelect->FieldByName("boiler")->AsInteger;
	CheckListBox1->Checked[9]=frmMain->sqlSelect->FieldByName("gaze")->AsInteger;
	CheckListBox1->Checked[10]=frmMain->sqlSelect->FieldByName("apa")->AsInteger;
	CheckListBox1->Checked[11]=frmMain->sqlSelect->FieldByName("canalizare")->AsInteger;

	rgMobilat->ItemIndex = rgMobilat->Items->IndexOf(frmMain->sqlSelect->FieldByName("mobilat")->AsAnsiString);
   /*	Mobilat = frmMain->sqlSelect->FieldByName("mobilat")->AsAnsiString;
	if (Mobilat == "Mobilat")
	{
		rgMobilat->ItemIndex=0;
	}
	else if (Mobilat == "Semimobilat")
	{
		rgMobilat->ItemIndex=1;
	}
	else if (Mobilat == "Nemobilat")
		rgMobilat->ItemIndex=2;
	else
		rgMobilat->ItemIndex=-1;
	 */
	rgUtilat->ItemIndex = rgUtilat->Items->IndexOf(frmMain->sqlSelect->FieldByName("utilat")->AsAnsiString);
   /*	Mobilat = frmMain->sqlSelect->FieldByName("mobilat")->AsAnsiString;
	if (Mobilat == "Mobilat")
	{
		rgMobilat->ItemIndex=0;
	}
	else if (Mobilat == "Semimobilat")
	{
		rgMobilat->ItemIndex=1;
	}
	else if (Mobilat == "Nemobilat")
		rgMobilat->ItemIndex=2;
	else
		rgMobilat->ItemIndex=-1;
   /*	Utilat = frmMain->sqlSelect->FieldByName("utilat")->AsAnsiString;
	if (Utilat == "Utilat")
	{
		rgUtilat->ItemIndex=0;
	}
	else if (Utilat == "Semiutilat")
	{
		rgUtilat->ItemIndex=1;
	}
	else if (Utilat == "Neutilat")
		rgUtilat->ItemIndex=2;
	else
		rgUtilat->ItemIndex=-1;     */

	txtNume->Text = frmMain->sqlSelect->FieldByName("nume")->AsAnsiString;;
	txtTel->Text = frmMain->sqlSelect->FieldByName("telefon")->AsAnsiString;;
	memInfo->Text = frmMain->sqlSelect->FieldByName("info_prop")->AsAnsiString;;
	txtDataExpirarii->DateTime=frmMain->sqlSelect->FieldByName("data_expirarii")->AsDateTime;
	inchiriat=frmMain->sqlSelect->FieldByName("inchiriat")->AsInteger;
	if (inchiriat) {
		btnInchiriat->Caption="Neinchiriat";
        btnInchiriat->Color = clYellow;
	} else {
		btnInchiriat->Caption="Inchiriat";
		btnInchiriat->Color = clBtnFace;
	}

	Label7->Visible=true;
	Label8->Visible=true;
	Label8->Caption = frmMain->sqlSelect->FieldByName("data_modificarii")->AsString;
/*
	poza1=frmMain->sqlSelect->FieldByName("poza1")->AsString;
	poza2=frmMain->sqlSelect->FieldByName("poza2")->AsString;
	poza3=frmMain->sqlSelect->FieldByName("poza3")->AsString;
	poza4=frmMain->sqlSelect->FieldByName("poza4")->AsString;

	if (poza1 != NULL && FileExists(imgPath+poza1)) {
		imgPoza1->Picture->LoadFromFile(imgPath+poza1);
		poza1 = imgPath+poza1;
	}


	if (poza2 != NULL && FileExists(imgPath+poza2) ) {
		imgPoza2->Picture->LoadFromFile(imgPath+poza2);
		poza2 = imgPath+poza2;
	}


	if (poza3 != NULL && FileExists(imgPath+poza3)) {
		imgPoza3->Picture->LoadFromFile(imgPath+poza3);
		poza3 = imgPath+poza3;
	}


	if (poza4 != NULL && FileExists(imgPath+poza4)) {
		imgPoza4->Picture->LoadFromFile(imgPath+poza4);
		poza4 = imgPath+poza4;
	}
                       */
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCase::btnInchiriatClick(TObject *Sender)
{
if (operatie == "mod")
	inchiriat = !inchiriat;

btnSalveazaClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCase::txtGsKeyPress(TObject *Sender, wchar_t &Key)
{
if( !((int)Key >= 48 && (int)Key<=57) && Key != VK_BACK ) {
		Key = 0;
}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCase::txtJudetChange(TObject *Sender)
{
frmMain->ComboList(txtLocalitate, "den", "localitati", false, (" where judet = (SELECT id from judete where den = '"+ txtJudet->Text+ "')").t_str() );
}
//---------------------------------------------------------------------------


void __fastcall TfrmCase::txtLocalitateChange(TObject *Sender)
{
frmMain->ComboList(txtZona, "den", "zone", false, (" where localitate = (SELECT id from localitati where den = '"+ txtLocalitate->Text+ "')").t_str() );
}
//---------------------------------------------------------------------------


void __fastcall TfrmCase::btnLocalitateClick(TObject *Sender)
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

void __fastcall TfrmCase::btnZonaClick(TObject *Sender)
{
UnicodeString zona;
if (txtLocalitate->Text != "") {

	if (InputQuery("Adaugare Zona", "Introduceti zona:", zona) == true){

		insertQuery->DatabaseName=frmMain->Database->DatabaseName;
		insertQuery->InsertSQL->Text = "INSERT INTO zone \
			(den, localitate) VALUES ( '"  + zona +
			"', (SELECT id from localitati where den = '" + txtLocalitate->Text +  "'))" ;
		insertQuery->ExecSQL(ukInsert);
		txtLocalitateChange(Sender);
		txtZona->ItemIndex=txtLocalitate->Items->IndexOf(zona);
	}
}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCase::btnSalveazaClick(TObject *Sender)
{
UnicodeString tmp, tmp_mod, tmp_exp;
UnicodeString Balcon,Gresie,Faianta,Termopan,Parchet,Usa_metalica,Centrala_termica;
UnicodeString Aer_conditionat, boiler, gaze, apa, canalizare;
UnicodeString Mobilat, Utilat;

if (txtTel->Text.Length() < 10 ) {
    ShowMessage("Introduceti numarul de telefon!!!");
	return ;
}

Balcon = IntToStr((int)CheckListBox1->Checked[0] );
Gresie = IntToStr((int)CheckListBox1->Checked[1] );
Faianta = IntToStr((int)CheckListBox1->Checked[2] );
Termopan = IntToStr((int)CheckListBox1->Checked[3] );
Parchet = IntToStr((int)CheckListBox1->Checked[4] );
Usa_metalica = IntToStr((int)CheckListBox1->Checked[5] );
Centrala_termica = IntToStr((int)CheckListBox1->Checked[6] );
Aer_conditionat = IntToStr((int)CheckListBox1->Checked[7] );
boiler = IntToStr((int)CheckListBox1->Checked[8] );
gaze = IntToStr((int)CheckListBox1->Checked[9] );
apa = IntToStr((int)CheckListBox1->Checked[10] );
canalizare = IntToStr((int)CheckListBox1->Checked[11] );

if (rgMobilat->ItemIndex >= 0)
	Mobilat = rgMobilat->Items->Strings[rgMobilat->ItemIndex];
else
	Mobilat = "";
if (rgUtilat->ItemIndex >= 0)
	Utilat = rgUtilat->Items->Strings[rgUtilat->ItemIndex];
else
    Utilat ="";

if (txtNrcam->Text == "") {
	txtNrcam->Text="0";
}
if (txtPret->Text == "") {
	txtPret->Text="0";
}
if (txtGs->Text == "") {
	txtGs->Text="0";
}


DateTimeToString(tmp, "YYYY-MM-dd hh:nn:ss",Now());
DateTimeToString(tmp_mod, "YYYY-MM-dd hh:nn:ss",Now());
DateTimeToString(tmp_exp, "YYYY-MM-dd",txtDataExpirarii->Date);

SQL->DatabaseName=frmMain->Database->DatabaseName;


UnicodeString index;
if (operatie == "add")
	{
	if (getID->Active == True)
		getID->Close();
	getID->DatabaseName=frmMain->Database->DatabaseName;
	getID->Open();
	index = getID->FieldByName("auto_increment")->AsString;
	getID->Close();
	}
else
	index = IntToStr(id);

 {
	if (! DirectoryExists(imgPath))
		CreateDir(imgPath);

	if (poza1 != NULL)
		{
		if (poza1 != imgPath+ ExtractFileName(poza1))
			{
			UnicodeString dest = imgPath+index + "_" + ExtractFileName(poza1);
			CopyFileA(poza1.t_str(), dest.t_str(), false);
			poza1 = index + "_" + ExtractFileName(poza1);
			}
		else
			poza1 = ExtractFileName(poza1);
		}

	if (poza2 != NULL)
		{
		if (poza2 != imgPath+ ExtractFileName(poza2))
			{
			UnicodeString dest = imgPath+index + "_" + ExtractFileName(poza2);
			CopyFileA(poza2.t_str(), dest.t_str(), false);
			poza2 = index + "_" + ExtractFileName(poza2);
			}
		else
			poza2 = ExtractFileName(poza2);
		}

	if (poza3 != NULL)
		{
		if (poza3 != imgPath+ ExtractFileName(poza3))
			{
			UnicodeString dest = imgPath+index + "_" + ExtractFileName(poza3);
			CopyFileA(poza3.t_str(), dest.t_str(), false);
			poza3 = index + "_" + ExtractFileName(poza3);
			}
		else
			poza3 = ExtractFileName(poza3);
		}

	if (poza4 != NULL)
		{
		if (poza4 != imgPath+ ExtractFileName(poza4))
			{
			UnicodeString dest = imgPath+index + "_" + ExtractFileName(poza4);
			CopyFileA(poza4.t_str(), dest.t_str(), false);
			poza4 = index + "_" + ExtractFileName(poza4);
			}
		else
			poza4 = ExtractFileName(poza4);
		}

}

SQL->InsertSQL->Text = "INSERT INTO casa (judet, localitate, nrcam, zona, \
		strada, pret, moneda, grupsanitar, data, data_modificarii, data_expirarii, \
		altele, balcon, gresie, faianta, termopan,parchet,um,ct,ac,apa,canalizare, \
		mobilat, utilat, nume, telefon, info_prop, boiler, gaze, inchiriat ) VALUES ( " \
		"'" +
		txtJudet->Text + "', '" +
		txtLocalitate->Text +"','" +
		txtNrcam->Text.Trim() + "', '" +
		txtZona->Text.Trim() + "','" +
		txtStrada->Text.Trim() + "'," +
		txtPret->Text + ",'" +
		txtMoneda->Text + "'," +
		txtGs->Text + ",'" +
		tmp + "','" +
		tmp_mod + "', '" +
		tmp_exp + "', '" +
		memAltele->Text + "'," +
		Balcon + "," +
		Gresie + "," +
		Faianta + "," +
		Termopan + "," +
		Parchet + "," +
		Usa_metalica + "," +
		Centrala_termica + "," +
		Aer_conditionat + "," +
		apa + "," +
		canalizare + ",'" +
		Mobilat + "','" +
		Utilat + "','" +
		txtNume->Text + "','" +
		txtTel->Text + "','" +
		memInfo->Text + "'," +
		boiler + "," +
		gaze + "," +
		IntToStr(inchiriat) + ")";

		//TODO update judet, localitate,
SQL->ModifySQL->Text = "UPDATE casa SET  \
		nrcam = '" + txtNrcam->Text + "'," +
		"judet = '" + txtJudet->Text + "'," +
		"localitate = '" + txtLocalitate->Text + "'," +
		"zona = '" + txtZona->Text + "'," +
		"strada = '" + txtStrada->Text + "'," +
		"pret = " + txtPret->Text + "," +
		"moneda = '" + txtMoneda->Text + "'," +
		"grupsanitar = " + txtGs->Text + "," +
		"data_modificarii = '" + tmp_mod + "',"+
		"data_expirarii = '" + tmp_exp + "',"+
		"altele = '" + memAltele->Text + "'," +
		"balcon = " + Balcon + "," +
		"gresie = " + Gresie + "," +
		"faianta = " + Faianta + "," +
		"termopan = " + Termopan + "," +
		"parchet = " + Parchet + "," +
		"um = " + Usa_metalica + "," +
		"ct = " + Centrala_termica + "," +
		"ac = " + Aer_conditionat + "," +
		"apa = " + apa + "," +
		"canalizare = " + canalizare + "," +
		"boiler = " + boiler + "," +
		"gaze = " + gaze + "," +
		"mobilat = '" + Mobilat + "'," +
		"utilat = '" + Utilat + "'," +
		"nume = '" + txtNume->Text + "'," +
		"telefon = '" + txtTel->Text + "'," +
		"info_prop = '" + memInfo->Text + "', " +
		"inchiriat = " + IntToStr(inchiriat) + " " +
	  /*	"poza1 = '" + poza1 + "', " +
		"poza2 = '" + poza2 + "', " +
		"poza3 = '" + poza3 + "', " +
		"poza4 = '" + poza4 + "' " +*/
		"WHERE id = " + IntToStr(frmCase->id);


if (frmCase->operatie == "add")
	SQL->InsertSQL->SaveToFile("myLog.txt" );
else  if (frmCase->operatie == "mod")
	SQL->ModifySQL->SaveToFile("myLog.txt" );
try {
	if (frmCase->operatie == "add")
		SQL->ExecSQL(ukInsert);
	else if (frmCase->operatie == "mod")
        SQL->ExecSQL(ukModify);

	} catch (EDatabaseError &OtherDatabaseError) {
		if (frmCase->operatie == "add")
			ShowMessage(SQL->InsertSQL->Text);
		else if (frmCase->operatie == "mod")
			ShowMessage(SQL->ModifySQL->Text);

			ShowMessage(OtherDatabaseError.ToString());
		}

frmMain->update = 0;
frmMain->Query1->Close();
frmMain->Query1->Open();
frmMain->update = 1;
frmCase->Close();
}
//---------------------------------------------------------------------------

