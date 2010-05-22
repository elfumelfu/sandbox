//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "apartamente.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "main.h"

TfrmAp *frmAp;
//---------------------------------------------------------------------------
__fastcall TfrmAp::TfrmAp(TComponent* Owner)
	: TForm(Owner)
{
operatie = "add";
id = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAp::btnSalveazaClick(TObject *Sender)
{
UnicodeString tmp, tmp_mod, tmp_exp;
UnicodeString Balcon,Gresie,Faianta,Termopan,Parchet,Usa_metalica,Centrala_termica;
UnicodeString Aer_conditionat, Apometre, Repartitoare;
UnicodeString Mobilat;

Balcon = IntToStr((int)CheckListBox1->Checked[0] );
Gresie = IntToStr((int)CheckListBox1->Checked[1] );
Faianta = IntToStr((int)CheckListBox1->Checked[2] );
Termopan = IntToStr((int)CheckListBox1->Checked[3] );
Parchet = IntToStr((int)CheckListBox1->Checked[4] );
Usa_metalica = IntToStr((int)CheckListBox1->Checked[5] );
Centrala_termica = IntToStr((int)CheckListBox1->Checked[6] );
Aer_conditionat = IntToStr((int)CheckListBox1->Checked[7] );
Apometre = IntToStr((int)CheckListBox1->Checked[8] );
Repartitoare = IntToStr((int)CheckListBox1->Checked[9] );

Mobilat = RadioGroup1->Items->Strings[RadioGroup1->ItemIndex];


DateTimeToString(tmp, "YY/MM/dd",Date());
DateTimeToString(tmp_mod, "YY/MM/dd",Date());
DateTimeToString(tmp_exp, "YY/MM/dd",txtDataExpirarii->Date);

SQL->DatabaseName=frmMain->Database->DatabaseName;
SQL->InsertSQL->Text = "INSERT INTO apartamente (judet, localitate, nrcam, zona, \
		bloc, ap, etaj, pret, moneda, grupsanitar, dsc, data, data_modificarii, data_expirarii, \
		altele, balcon, gresie, faianta, termopan,parchet,um,ct,ac,apometre,repartitoare, \
		mobilat, nume, telefon, info_prop ) VALUES ( " \
		"'GALATI', 'GALATI', " +
		txtNrcam->Text + ", '" +
		txtZona->Text + "','" +
		txtBloc->Text + "','" +
		txtAp->Text + "','" +
		txtEtaj->Text + "', " +
		txtPret->Text + ",'" +
		txtMoneda->Text + "'," +
		txtGs->Text + ",'" +
		txtDsc->Text + "', '" +
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
		Apometre + "," +
		Repartitoare + ",'" +
		Mobilat + "','" +
		txtNume->Text + "','" +
		txtTel->Text + "','" +
		memInfo->Text + "')";
        //TODO update judet, localitate,
SQL->ModifySQL->Text = "UPDATE apartamente SET  \
		nrcam = " + txtNrcam->Text + "," +
		"zona = '" + txtZona->Text + "'," +
		"bloc = '" + txtBloc->Text + "'," +
		"ap = '"   + txtAp->Text + "'," +
		"etaj = '" + txtEtaj->Text + "'," +
		"pret = " + txtPret->Text + "," +
		"moneda = '" + txtMoneda->Text + "'," +
		"grupsanitar = " + txtGs->Text + "," +
		"dsc = '" + txtDsc->Text + "'," +
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
		"apometre = " + Apometre + "," +
		"repartitoare = " + Repartitoare + "," +
		"mobilat = '" + Mobilat + "'," +
		"nume = '" + txtNume->Text + "'," +
		"telefon = '" + txtTel->Text + "'," +
		"info_prop = '" + memInfo->Text + "' " +
		"WHERE id = " + IntToStr(frmAp->id);
if (frmAp->operatie == "add")
	SQL->InsertSQL->SaveToFile("myLog.txt" );
else  if (frmAp->operatie == "mod")
	SQL->ModifySQL->SaveToFile("myLog.txt" );
try {
	if (frmAp->operatie == "add")
		SQL->ExecSQL(ukInsert);
	else if (frmAp->operatie == "mod")
        SQL->ExecSQL(ukModify);

	} catch (EDatabaseError &OtherDatabaseError) {
		if (frmAp->operatie == "add")
			ShowMessage(SQL->InsertSQL->Text);
		else if (frmAp->operatie == "mod")
			ShowMessage(SQL->ModifySQL->Text);

			ShowMessage(OtherDatabaseError.ToString());
		}

frmMain->Query1->Close();
frmMain->Query1->Open();
frmAp->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAp::btnStergeTotClick(TObject *Sender)
{
txtNrcam->Text= "";
txtZona->Text= "";
txtBloc->Text= "";
txtAp->Text= "";
txtEtaj->Text= "";
txtPret->Text= "";
txtMoneda->Text= "";
txtGs->Text= "";
txtDsc->Text= "";
memAltele->Lines->Clear();
CheckListBox1->CheckAll(cbUnchecked, False, False);
RadioGroup1->ItemIndex=2;
txtNume->Text = "";
txtTel->Text = "";
memInfo->Text = "";
txtDataExpirarii->DateTime=Date();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAp::btnRenuntaClick(TObject *Sender)
{
btnStergeTotClick(Sender);
frmAp->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAp::FormShow(TObject *Sender)
{
UnicodeString Mobilat;
btnStergeTotClick(Sender);
if (frmAp->operatie == "mod")
	{
	txtNrcam->Text=frmMain->sqlSelect->FieldByName("nrcam")->AsAnsiString;
	txtZona->Text= frmMain->sqlSelect->FieldByName("zona")->AsAnsiString;
	txtBloc->Text= frmMain->sqlSelect->FieldByName("bloc")->AsAnsiString;
	txtAp->Text= frmMain->sqlSelect->FieldByName("ap")->AsAnsiString;
	txtEtaj->Text= frmMain->sqlSelect->FieldByName("etaj")->AsAnsiString;
	txtPret->Text= frmMain->sqlSelect->FieldByName("pret")->AsAnsiString;
	txtMoneda->Text= frmMain->sqlSelect->FieldByName("moneda")->AsAnsiString;
	txtGs->Text= frmMain->sqlSelect->FieldByName("grupsanitar")->AsAnsiString;
	txtDsc->Text= frmMain->sqlSelect->FieldByName("dsc")->AsAnsiString;
	memAltele->Text = frmMain->sqlSelect->FieldByName("altele")->AsAnsiString;
	CheckListBox1->Checked[0]=frmMain->sqlSelect->FieldByName("balcon")->AsInteger;
	CheckListBox1->Checked[1]=frmMain->sqlSelect->FieldByName("gresie")->AsInteger;
	CheckListBox1->Checked[2]=frmMain->sqlSelect->FieldByName("faianta")->AsInteger;
	CheckListBox1->Checked[3]=frmMain->sqlSelect->FieldByName("termopan")->AsInteger;
	CheckListBox1->Checked[4]=frmMain->sqlSelect->FieldByName("parchet")->AsInteger;
	CheckListBox1->Checked[5]=frmMain->sqlSelect->FieldByName("um")->AsInteger;
	CheckListBox1->Checked[6]=frmMain->sqlSelect->FieldByName("ct")->AsInteger;
	CheckListBox1->Checked[7]=frmMain->sqlSelect->FieldByName("ac")->AsInteger;
	CheckListBox1->Checked[8]=frmMain->sqlSelect->FieldByName("apometre")->AsInteger;
	CheckListBox1->Checked[9]=frmMain->sqlSelect->FieldByName("repartitoare")->AsInteger;

	Mobilat = frmMain->sqlSelect->FieldByName("mobilat")->AsAnsiString;
	if (Mobilat == "Mobilat")
	{
		RadioGroup1->ItemIndex=0;
	}
	else if (Mobilat == "Semimobilat")
	{
        RadioGroup1->ItemIndex=1;
	}
	else
		RadioGroup1->ItemIndex=2; //TODO

	txtNume->Text = frmMain->sqlSelect->FieldByName("nume")->AsAnsiString;;
	txtTel->Text = frmMain->sqlSelect->FieldByName("telefon")->AsAnsiString;;
	memInfo->Text = frmMain->sqlSelect->FieldByName("info_prop")->AsAnsiString;;
	txtDataExpirarii->DateTime=frmMain->sqlSelect->FieldByName("data_expirarii")->AsDateTime;
	}
}
//---------------------------------------------------------------------------

