//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clienti_apartamente.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmClientiAp *frmClientiAp;
//---------------------------------------------------------------------------
__fastcall TfrmClientiAp::TfrmClientiAp(TComponent* Owner)
	: TForm(Owner)
{
operatie = "add";
id = -1;
inchiriat = 0;
locID=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientiAp::btnStergeTotClick(TObject *Sender)
{
txtJudet->ItemIndex=txtJudet->Items->IndexOf(frmMain->defaultJudet);
txtJudetChange(Sender);
txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf(frmMain->defaultLocalitate);
txtLocalitateChange(Sender);
txtNrcam->ClearSelection();
txtZonePreferate->ClearSelection();
txtZoneExcluse->ClearSelection();
txtPretMin->Text= "";
txtPretMax->Text= "";
txtMoneda->ItemIndex=-1;
txtNrPersoane->Text= "";
txtPerContract->Text= "";
txtDsc->ItemIndex=-1;
cblImbunatatiri->CheckAll(cbUnchecked, False, False);
cblMobilat->CheckAll(cbUnchecked, False, False);
cblUtilat->CheckAll(cbUnchecked, False, False);
txtNume->Text = "";
txtTel->Text = "";
memInfo->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientiAp::FormShow(TObject *Sender)
{
UnicodeString Mobilat, Utilat;
btnStergeTotClick(Sender);
frmClientiAp->Caption = "Adauga client apartament";
Label7->Visible=false;
Label8->Visible=false;
frmMain->ComboList(txtJudet, "den", "judete", false, "");
txtJudet->ItemIndex=txtJudet->Items->IndexOf(frmMain->defaultJudet);
txtJudetChange(Sender);
txtLocalitate->ItemIndex=txtLocalitate->Items->IndexOf(frmMain->defaultLocalitate);
txtLocalitateChange(Sender);

if (frmClientiAp->operatie == "mod")
{
	frmClientiAp->Caption = "Modifica client apartament";

 /*	txtNrcam->ItemIndex=txtNrcam->Items->IndexOf(frmMain->sqlSelect->FieldByName("nrcam")->AsAnsiString);

	txtJudet->ItemIndex=txtJudet->Items->IndexOf(frmMain->sqlSelect->FieldByName("judet")->AsAnsiString);
	txtJudetChange(Sender);
	txtLocalitate->ItemIndex=txtJudet->Items->IndexOf(frmMain->sqlSelect->FieldByName("localitate")->AsAnsiString);
	txtLocalitateChange(Sender);
	txtZona->ItemIndex=txtZona->Items->IndexOf(frmMain->sqlSelect->FieldByName("zona")->AsAnsiString);
 */
	txtPretMin->Text= frmMain->sqlSelect->FieldByName("pret_min")->AsAnsiString;
    if (txtPretMin->Text == "0")
		txtPretMin->Text = "";
	txtPretMax->Text= frmMain->sqlSelect->FieldByName("pret_max")->AsAnsiString;
	if (txtPretMax->Text == "0")
		txtPretMax->Text = "";

	txtNrPersoane->Text= frmMain->sqlSelect->FieldByName("nrpers")->AsAnsiString;

	txtPerContract->Text= frmMain->sqlSelect->FieldByName("per_contract")->AsAnsiString;
	if (txtPerContract->Text == "0")
		txtPerContract->Text = "";

 	txtMoneda->ItemIndex = txtMoneda->Items->IndexOf(frmMain->sqlSelect->FieldByName("moneda")->AsAnsiString);
	txtDsc->ItemIndex = txtDsc->Items->IndexOf(frmMain->sqlSelect->FieldByName("dsc")->AsAnsiString);

	cblImbunatatiri->Checked[0]=frmMain->sqlSelect->FieldByName("balcon")->AsInteger;
	cblImbunatatiri->Checked[1]=frmMain->sqlSelect->FieldByName("gresie")->AsInteger;
	cblImbunatatiri->Checked[2]=frmMain->sqlSelect->FieldByName("faianta")->AsInteger;
	cblImbunatatiri->Checked[3]=frmMain->sqlSelect->FieldByName("termopan")->AsInteger;
	cblImbunatatiri->Checked[4]=frmMain->sqlSelect->FieldByName("parchet")->AsInteger;
	cblImbunatatiri->Checked[5]=frmMain->sqlSelect->FieldByName("um")->AsInteger;
	cblImbunatatiri->Checked[6]=frmMain->sqlSelect->FieldByName("ct")->AsInteger;
	cblImbunatatiri->Checked[7]=frmMain->sqlSelect->FieldByName("ac")->AsInteger;
	cblImbunatatiri->Checked[8]=frmMain->sqlSelect->FieldByName("apometre")->AsInteger;
	cblImbunatatiri->Checked[9]=frmMain->sqlSelect->FieldByName("repartitoare")->AsInteger;
	cblImbunatatiri->Checked[10]=frmMain->sqlSelect->FieldByName("boiler")->AsInteger;
	cblImbunatatiri->Checked[11]=frmMain->sqlSelect->FieldByName("contorgaz")->AsInteger;

	txtNume->Text = frmMain->sqlSelect->FieldByName("nume")->AsAnsiString;
	txtTel->Text = frmMain->sqlSelect->FieldByName("telefon")->AsAnsiString;
	memInfo->Text = frmMain->sqlSelect->FieldByName("informatii")->AsAnsiString;

    inchiriat=frmMain->sqlSelect->FieldByName("inchiriat")->AsInteger;
	if (inchiriat)
		btnInchiriat->Caption="Nu a inchiriat";
	else
		btnInchiriat->Caption="A inchiriat";

	/*Mobilat*/
	{
	TStringList *mobilat = new TStringList;
	mobilat->Delimiter = '/';
	mobilat->Clear();
	mobilat->DelimitedText=frmMain->sqlSelect->FieldByName("mobilat")->AsAnsiString;

	for (int i = 0; i < mobilat->Count; i++) {
    	cblMobilat->Checked[cblMobilat->Items->IndexOf(mobilat->Strings[i])]=true;
	}
	mobilat->Free();
	}

	/*Utilat*/
	{
	TStringList *utilat = new TStringList;
	utilat->Delimiter = '/';
	utilat->Clear();
	utilat->DelimitedText=frmMain->sqlSelect->FieldByName("utilat")->AsAnsiString;

	for (int i = 0; i < utilat->Count; i++) {
		cblUtilat->Checked[cblUtilat->Items->IndexOf(utilat->Strings[i])]=true;
	}
	utilat->Free();
	}

	/*nrcam*/
	{
	TStringList *nrcam = new TStringList;
	nrcam->Delimiter = '/';
	nrcam->Clear();
	nrcam->DelimitedText=frmMain->sqlSelect->FieldByName("nrcam")->AsAnsiString;

	for (int i = 0; i < nrcam->Count; i++) {
		txtNrcam->Selected[txtNrcam->Items->IndexOf(nrcam->Strings[i])]=true;
	}
	nrcam->Free();
	}

	locID=frmMain->sqlSelect->FieldByName("localitate")->AsInteger;

	getLocId->Close();
	getLocId->DatabaseName=frmMain->Database->DatabaseName;
	getLocId->SQL->Text="SELECT judete.den as judden, localitati.den as locden from localitati,judete \
	 WHERE localitati.judet=judete.id and localitati.id = " + IntToStr(locID);
	getLocId->Open();

	UnicodeString judet, localitate;

	judet = getLocId->FieldByName("judden")->AsAnsiString;
	localitate = getLocId->FieldByName("locden")->AsAnsiString;
	getLocId->Close();

	txtJudet->ItemIndex = txtJudet->Items->IndexOf(judet);
	txtJudetChange(Sender);
	txtLocalitate->ItemIndex = txtLocalitate->Items->IndexOf(localitate);
	txtLocalitateChange(Sender);

    /*zone_preferate*/
	{
	TStringList *zone_preferate = new TStringList;
	zone_preferate->Delimiter = '/';
	zone_preferate->QuoteChar = '|';
	zone_preferate->Clear();
	zone_preferate->DelimitedText=frmMain->sqlSelect->FieldByName("zone_preferate")->AsAnsiString;
	zone_preferate->Sort();
	for (int i=zone_preferate->Count - 1; i >= 0; i--) {
		txtZonePreferate->Items->Move(txtZonePreferate->Items->IndexOf(zone_preferate->Strings[i]),0);
	}
	for (int i = 0; i < zone_preferate->Count; i++) {
		txtZonePreferate->Selected[txtZonePreferate->Items->IndexOf(zone_preferate->Strings[i])]=true;
	}


	zone_preferate->Free();
	}

	/*zone_excluse*/
	{
	TStringList *zone_excluse = new TStringList;
	zone_excluse->Delimiter = '/';
	zone_excluse->QuoteChar = '|';
	zone_excluse->Clear();
	zone_excluse->DelimitedText=frmMain->sqlSelect->FieldByName("zone_excluse")->AsAnsiString;
	zone_excluse->Sort();
	for (int i=zone_excluse->Count - 1; i >= 0; i--) {
		txtZoneExcluse->Items->Move(txtZoneExcluse->Items->IndexOf(zone_excluse->Strings[i]),0);
	}
	for (int i = 0; i < zone_excluse->Count; i++) {
		txtZoneExcluse->Selected[txtZoneExcluse->Items->IndexOf(zone_excluse->Strings[i])]=true;
	}
	zone_excluse->Free();
	}


	Label7->Visible=true;
	Label8->Visible=true;
	Label8->Caption = frmMain->sqlSelect->FieldByName("data_modificarii")->AsString;

}

}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::txtJudetChange(TObject *Sender)
{
frmMain->ComboList(txtLocalitate, "den", "localitati", false, (" where judet = (SELECT id from judete where den = '"+ txtJudet->Text+ "')").t_str() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::txtLocalitateChange(TObject *Sender)
{
frmMain->SelectList(txtZonePreferate, "den", "zone", false, (" where localitate = (SELECT id from localitati where den = '"+ txtLocalitate->Text+ "')").t_str() );
txtZoneExcluse->Items = txtZonePreferate->Items;

getLocId->Close();
getLocId->DatabaseName=frmMain->Database->DatabaseName;
getLocId->SQL->Text="SELECT localitati.id as idloc from localitati,judete \
	 WHERE localitati.judet=judete.id and judete.den = '" + txtJudet->Text +
	 "' and localitati.den = '" +txtLocalitate->Text + "'";
getLocId->Open();
if (getLocId->RecordCount == 1) {
	getLocId->First();
	locID = getLocId->FieldByName("idloc")->AsInteger;
} else {
	locID = 0;
}

getLocId->Close();

}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::btnLocalitateClick(TObject *Sender)
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

void __fastcall TfrmClientiAp::btnRenuntaClick(TObject *Sender)
{
btnStergeTotClick(Sender);
frmClientiAp->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::btnInchiriatClick(TObject *Sender)
{
inchiriat = !inchiriat;
btnSalveazaClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::btnSalveazaClick(TObject *Sender)
{
UnicodeString tmp, tmp_mod, tmp_exp;
UnicodeString Balcon,Gresie,Faianta,Termopan,Parchet,Usa_metalica,Centrala_termica;
UnicodeString Aer_conditionat, Apometre, Repartitoare, boiler, contorgaz;
//TStringList mobilat, utilat, nrcam, zone_preferate, zone_excluse;

if (txtTel->Text.Length() < 10 ) {
	ShowMessage("Introduceti numarul de telefon!!!");
	return ;
}



Balcon = IntToStr((int)cblImbunatatiri->Checked[0] );
Gresie = IntToStr((int)cblImbunatatiri->Checked[1] );
Faianta = IntToStr((int)cblImbunatatiri->Checked[2] );
Termopan = IntToStr((int)cblImbunatatiri->Checked[3] );
Parchet = IntToStr((int)cblImbunatatiri->Checked[4] );
Usa_metalica = IntToStr((int)cblImbunatatiri->Checked[5] );
Centrala_termica = IntToStr((int)cblImbunatatiri->Checked[6] );
Aer_conditionat = IntToStr((int)cblImbunatatiri->Checked[7] );
Apometre = IntToStr((int)cblImbunatatiri->Checked[8] );
Repartitoare = IntToStr((int)cblImbunatatiri->Checked[9] );
boiler = IntToStr((int)cblImbunatatiri->Checked[10] );
contorgaz = IntToStr((int)cblImbunatatiri->Checked[11] );

TStringList *nrcam = new TStringList;
nrcam->Delimiter = '/';
nrcam->Clear();
if (txtNrcam->SelCount) {
	for (int i = 0; i < txtNrcam->Items->Count; i++) {
		if (txtNrcam->Selected[i]) {
		nrcam->Add(txtNrcam->Items->Strings[i]);
		}
	}
}

TStringList *zone_preferate = new TStringList;
zone_preferate->Delimiter = '/';
zone_preferate->QuoteChar = '|';
zone_preferate->Clear();
if (txtZonePreferate->SelCount) {
	for (int i = 0; i < txtZonePreferate->Items->Count; i++) {
		if (txtZonePreferate->Selected[i]) {
		zone_preferate->Add(txtZonePreferate->Items->Strings[i]);
		}
	}
}

TStringList *zone_excluse = new TStringList;
zone_excluse->Delimiter = '/';
zone_excluse->QuoteChar = '|';
zone_excluse->Clear();
if (txtZoneExcluse->SelCount) {
	for (int i = 0; i < txtZoneExcluse->Items->Count; i++) {
		if (txtZoneExcluse->Selected[i]) {
		zone_excluse->Add(txtZoneExcluse->Items->Strings[i]);
		}
	}
}

TStringList *mobilat = new TStringList;
mobilat->Delimiter = '/';
mobilat->Clear();

	for (int i = 0; i < cblMobilat->Items->Count; i++) {
		if (cblMobilat->Checked[i]) {
			mobilat->Add(cblMobilat->Items->Strings[i]);
		}
	}

TStringList *utilat = new TStringList;
utilat->Delimiter = '/';
utilat->Clear();

	for (int i = 0; i < cblUtilat->Items->Count; i++) {
		if (cblUtilat->Checked[i]) {
			utilat->Add(cblUtilat->Items->Strings[i]);
		}
	}

if (txtPretMin->Text == "")
	txtPretMin->Text="0";
if (txtPretMax->Text == "")
	txtPretMax->Text="0";
if (txtPerContract->Text == "")
	txtPerContract->Text="0";


DateTimeToString(tmp, "YYYY-MM-dd hh:nn:ss",Now());
DateTimeToString(tmp_mod, "YYYY-MM-dd hh:nn:ss",Now());

SQL->DatabaseName=frmMain->Database->DatabaseName;

SQL->InsertSQL->Text = "INSERT INTO clienti_apartamente (zone_preferate, zone_excluse, \
	nrcam, nrpers, per_contract, data, data_modificarii, mobilat, utilat, nume, telefon, \
	pret_min, pret_max, moneda, informatii, dsc, localitate, balcon, gresie, faianta, \
	termopan,parchet,um,ct,ac,apometre,repartitoare, boiler, contorgaz, inchiriat ) \
	VALUES ('" +
		zone_preferate->DelimitedText + "', '" +
		zone_excluse->DelimitedText +"','" +
		nrcam->DelimitedText + "', '" +
		txtNrPersoane->Text + "'," +
		txtPerContract->Text + ",'" +
		tmp + "','" +
		tmp_mod + "', '" +
		mobilat->DelimitedText + "','" +
		utilat->DelimitedText + "','" +
        txtNume->Text + "','" +
		txtTel->Text + "'," +
		txtPretMin->Text + "," +
		txtPretMax->Text + ",'" +
		txtMoneda->Text + "','" +
		memInfo->Text + "','" +
		txtDsc->Text + "', " +
		IntToStr(locID) + "," +
		Balcon + "," +
		Gresie + "," +
		Faianta + "," +
		Termopan + "," +
		Parchet + "," +
		Usa_metalica + "," +
		Centrala_termica + "," +
		Aer_conditionat + "," +
		Apometre + "," +
		Repartitoare + "," +
		boiler + "," +
		contorgaz + "," +
		IntToStr(inchiriat) + ")";

SQL->ModifySQL->Text = "UPDATE clienti_apartamente SET  \
		 zone_preferate = '" + zone_preferate->DelimitedText + "', " +
		"zone_excluse = '" + zone_excluse->DelimitedText +"'," +
		"nrcam = '" + nrcam->DelimitedText + "'," +
		"nrpers = '" + txtNrPersoane->Text + "'," +
		"per_contract = " + txtPerContract->Text + "," +
		"data_modificarii = '" + tmp_mod + "'," +
		"mobilat = '" + mobilat->DelimitedText + "'," +
		"utilat = '" + utilat->DelimitedText + "'," +
		"nume = '" + txtNume->Text + "'," +
		"telefon = '" + txtTel->Text + "'," +
		"pret_min = " + txtPretMin->Text + "," +
		"pret_max = " + txtPretMax->Text + "," +
		"moneda = '" + txtMoneda->Text + "'," +
		"informatii = '" + memInfo->Text + "'," +
		"dsc = '" + txtDsc->Text + "'," +
		"localitate = " + IntToStr(locID) + "," +
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
		"boiler = " + boiler + "," +
		"contorgaz = " + contorgaz + "," +
		"inchiriat = " + IntToStr(inchiriat) + " " +
		"WHERE id = " + IntToStr(frmClientiAp->id);

if (operatie == "add")
	SQL->InsertSQL->SaveToFile("myLog.txt" );
else  if (operatie == "mod")
	SQL->ModifySQL->SaveToFile("myLog.txt" );
try {
	if (operatie == "add")
		SQL->ExecSQL(ukInsert);
	else if (operatie == "mod")
        SQL->ExecSQL(ukModify);

	} catch (EDatabaseError &OtherDatabaseError) {
		if (operatie == "add")
			ShowMessage(SQL->InsertSQL->Text);
		else if (operatie == "mod")
			ShowMessage(SQL->ModifySQL->Text);

			ShowMessage(OtherDatabaseError.ToString());
		}

mobilat->Free();
utilat->Free();
nrcam->Free();
zone_preferate->Free();
zone_excluse->Free();

frmMain->update = 0;
frmMain->Query1->Close();
frmMain->Query1->Open();
frmMain->update = 1;
frmClientiAp->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::Label2Click(TObject *Sender)
{
UnicodeString zona;
TStringList *zone_preferate = new TStringList;
zone_preferate->Delimiter = '/';
zone_preferate->QuoteChar = '|';
zone_preferate->Clear();
if (txtZonePreferate->SelCount) {
	for (int i = 0; i < txtZonePreferate->Items->Count; i++) {
		if (txtZonePreferate->Selected[i]) {
		zone_preferate->Add(txtZonePreferate->Items->Strings[i]);
		}
	}
}

TStringList *zone_excluse = new TStringList;
zone_excluse->Delimiter = '/';
zone_excluse->QuoteChar = '|';
zone_excluse->Clear();
if (txtZoneExcluse->SelCount) {
	for (int i = 0; i < txtZoneExcluse->Items->Count; i++) {
		if (txtZoneExcluse->Selected[i]) {
		zone_excluse->Add(txtZoneExcluse->Items->Strings[i]);
		}
	}
}
if (txtLocalitate->Text != "") {

	if (InputQuery("Adaugare Zona", "Introduceti zona:", zona) == true){

		insertQuery->DatabaseName=frmMain->Database->DatabaseName;
		insertQuery->InsertSQL->Text = "INSERT INTO zone \
			(den, localitate) VALUES ( '"  + zona +
			"', (SELECT id from localitati where den = '" + txtLocalitate->Text +  "'))" ;
		insertQuery->ExecSQL(ukInsert);
		txtLocalitateChange(Sender);
		//txtZona->ItemIndex=txtLocalitate->Items->IndexOf(zona);
	}
}

for (int i = 0; i < zone_preferate->Count; i++)
	txtZonePreferate->Selected[txtZonePreferate->Items->IndexOf(zone_preferate->Strings[i])]=true;
zone_preferate->Free();

for (int i = 0; i < zone_excluse->Count; i++)
	txtZoneExcluse->Selected[txtZoneExcluse->Items->IndexOf(zone_excluse->Strings[i])]=true;
zone_excluse->Free();

}
//---------------------------------------------------------------------------

void __fastcall TfrmClientiAp::txtPerContractKeyPress(TObject *Sender, wchar_t &Key)

{
if( !((int)Key >= 48 && (int)Key<=57) && Key != VK_BACK )
		Key = 0;
}
//---------------------------------------------------------------------------

