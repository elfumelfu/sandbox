// $$---- Form CPP ----
// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include <IniFiles.hpp>

#include "apartamente.h"
#include "agentii.h"
#include "clienti_apartamente.h"
#include "setari.h"


#define NR_TABLES 3
#define NR_CAMPURI_BOOL 13

TfrmMain *frmMain;
char *campuri_bool[50] = {
	"balcon", "gresie", "faianta", "termopan", "parchet", "um", "ct", "ac",
	"apometre", "repartitoare", "boiler", "contorgaz", "inchiriat"
};
char *den_table[50][2] = { {
		"Oferte apartamente", "apartamente"
	}, {
		"Agentii", "agentii"
	}, {
		"Clienti apartamente", "clienti_apartamente"
	}
};


UnicodeString orderby = "data_modificarii";
char * orderType = "DESC";

char * getDen(const char * table) {
	for (int i = 0; i < NR_TABLES; i++) {
		if (strcmp(den_table[i][1], table) == 0) {
			return den_table[i][0];
		}
	}
	return NULL;
}

int isCampBool(const char * field) {
	for (int i = 0; i < NR_CAMPURI_BOOL; i++) {
		if (strcmp(campuri_bool[i], field) == 0) {
			return 1;
		}
	}
	return 0;
}

int isAll(TList * list) {

	for (int i = 0; i < list->Count; i++) {
		if (((TComboBox *)(list->Items[i]))->Text != "All") {
			return 0;
		}
	}
	return 1;
}

void setValori(int val, UnicodeString moneda, int &ron, int &eur, int &usd)
{
	if (moneda == "RON") {
		ron=StrToInt(val);
		eur=(int)(ron / frmMain->setari.curs_eur);
		usd=(int)(ron / frmMain->setari.curs_usd);
	}
	if (moneda == "EUR") {
		eur=StrToInt(val);
		ron=(int)(eur * frmMain->setari.curs_eur);
		usd=(int)(ron / frmMain->setari.curs_usd);
	}
	if (moneda == "USD") {
		usd=StrToInt(val);
		ron=(int)(usd * frmMain->setari.curs_usd);
		eur=(int)(ron / frmMain->setari.curs_eur);
	}

}
TSetari::TSetari(UnicodeString iniFile){

	LoadFromFile(iniFile);
}

void TSetari::LoadFromFile(UnicodeString iniFile) {

	TIniFile * ini;

	if (FileExists(iniFile)) {
		ini = new TIniFile(iniFile);
		curs_eur = ini->ReadFloat("General", "curs_eur", 0);
		curs_usd = ini->ReadFloat("General", "curs_usd", 0);
		marja_cautare = ini->ReadInteger("General", "marja_cautare", 0);
		moneda_marja_cautare = ini->ReadString("General", "moneda_marja_cautare", "RON");
		judet = ini->ReadString("General", "judet", "Galati");
		localitate = ini->ReadString("General", "localitate", "Galati");
		delete ini;
	}
}

void TSetari::SaveToFile(UnicodeString iniFile) {

	TIniFile * ini = new TIniFile(iniFile);
	ini->WriteFloat("General", "curs_eur", curs_eur);
	ini->WriteFloat("General", "curs_usd", curs_usd);
	ini->WriteInteger("General", "marja_cautare", marja_cautare);
	ini->WriteString("General", "moneda_marja_cautare", moneda_marja_cautare);
	ini->WriteString("General", "judet", judet);
	ini->WriteString("General", "localitate", localitate);
	delete ini;
}

void __fastcall TfrmMain::ComboList(TComboBox *combo, const char *field,
	const char *table, bool addAll, const char * where) {

	cbQuery->Close();
	cbQuery->DatabaseName = Database->DatabaseName;
	cbQuery->SQL->Clear();
	cbQuery->SQL->Add("SELECT distinct (");
	cbQuery->SQL->Add(field);
	cbQuery->SQL->Add(") as selectie from ");
	cbQuery->SQL->Add(table);

	if (strcmp(where, "") != 0) {
		cbQuery->SQL->Add(where);
	}

	cbQuery->SQL->Add(" ORDER BY ");
	cbQuery->SQL->Add(field);

	cbQuery->Open();
	combo->Clear();
	if (addAll)
		combo->Items->Add("All");
	if (!cbQuery->IsEmpty()) {
		cbQuery->First();
		for (int i = 1; i <= cbQuery->RecordCount; i++) {

			if (Trim(cbQuery->FieldByName("selectie")->AsString) != "")
				combo->Items->Add(cbQuery->FieldByName("selectie")->AsString);

			if (i != cbQuery->RecordCount)
				cbQuery->Next();
		}
	}
	combo->ItemIndex = 0;
	cbQuery->Close();
}

void __fastcall TfrmMain::SelectList(TListBox *list, const char *field,
	const char *table, bool addAll, const char * where) {
	cbQuery->Close();
	cbQuery->DatabaseName = Database->DatabaseName;
	cbQuery->SQL->Clear();
	cbQuery->SQL->Add("SELECT distinct (");
	cbQuery->SQL->Add(field);
	cbQuery->SQL->Add(") from ");
	cbQuery->SQL->Add(table);

	if (strcmp(where, "") != 0) {
		cbQuery->SQL->Add(where);
	}

	cbQuery->SQL->Add(" ORDER BY ");
	cbQuery->SQL->Add(field);

	cbQuery->Open();
	list->Clear();
	if (addAll)
		list->Items->Add("All");
	if (!cbQuery->IsEmpty()) {
		cbQuery->First();
		for (int i = 1; i <= cbQuery->RecordCount; i++) {

			if (Trim(cbQuery->FieldByName(field)->AsString) != "")
				list->Items->Add(cbQuery->FieldByName(field)->AsString);

			if (i != cbQuery->RecordCount)
				cbQuery->Next();
		}
	}
	list->ItemIndex = 0;
	cbQuery->Close();
}

// ---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner) {
	DecimalSeparator='.';
	tabela = "apartamente";
	this->setari.LoadFromFile(SETARI_INI_FILE);
	ckbMarja->Caption = "� " + IntToStr(frmMain->setari.marja_cautare) + " " + frmMain->setari.moneda_marja_cautare;
	ckbClApMarja->Caption = "� " + IntToStr(frmMain->setari.marja_cautare) + " " + frmMain->setari.moneda_marja_cautare;
	update = 1;
	DBGrid1->Columns->LoadFromFile(ExtractFilePath(Application->ExeName)
		+ tabela + ".grid");
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DatabaseAfterConnect(TObject *Sender) {
	StatusBar->SimpleText = "Conectat la '" + Database->Params->ValueFromIndex
		[0] + "@" + Database->AliasName + "'.";

	TTreeNode *node = TreeView1->TopItem->getFirstChild();
	TreeView1->Selected = node;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Iesier1Click(TObject *Sender) {
	Database->Close();
	Application->Terminate();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::TreeView1Change(TObject *Sender, TTreeNode *Node) {
	panCauta->Visible = false;
	Query1->Close();
	Query1->DatabaseName = Database->DatabaseName;
	DBGrid1->Columns->SaveToFile(ExtractFilePath(Application->ExeName)
		+ tabela + ".grid");
	if (TreeView1->Selected->Text == "Apartamente" &&
		(TreeView1->Selected->GetPrev()->Text == "Oferte") || TreeView1->Selected->Text == "Oferte") {
		Query1->SQL->Text = "SELECT * FROM apartamente";
		tabela = "apartamente";
		orderby = "data_modificarii";
		orderType = "DESC";
	}
	if (TreeView1->Selected->Text == "Apartamente" &&
		(TreeView1->Selected->GetPrev()->Text == "Clienti") || TreeView1->Selected->Text == "Clienti") {
		Query1->SQL->Text = "SELECT * FROM clienti_apartamente";
		tabela = "clienti_apartamente";
		orderby = "data_modificarii";
		orderType = "DESC";
	}
	if (TreeView1->Selected->Text == "Agentii") {
		Query1->SQL->Text = "SELECT * FROM agentii";
		tabela = "agentii";
		orderby = "nume";
		orderType = "ASC";
	}
  	DBGrid1->Columns->LoadFromFile(ExtractFilePath(Application->ExeName)
		+ tabela + ".grid");
	Query1->Open();

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Adauga1Click(TObject *Sender) {
	frmAp->operatie = "add";
	frmAp->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1DblClick(TObject *Sender) {

	sqlSelect->Close();
	sqlSelect->DatabaseName = Database->DatabaseName;
	sqlSelect->SQL->Clear();


	sqlSelect->SQL->Text = "SELECT * from " + tabela + " where id=" + Trim
		(DBGrid1->SelectedField->DataSet->FieldByName("id")->AsString);
	sqlSelect->Open();

	if (tabela == "apartamente") {
		frmAp->operatie = "mod";
		frmAp->id = DBGrid1->SelectedField->DataSet->FieldByName("id")
			->AsInteger;
		frmAp->ShowModal();
		return;
	}
	if (tabela == "agentii") {
		frmAgentii->operatie = "mod";
		frmAgentii->id = DBGrid1->SelectedField->DataSet->FieldByName("id")
			->AsInteger;
		frmAgentii->ShowModal();
		return;
	}
	if (tabela == "clienti_apartamente") {
		frmClientiAp->operatie = "mod";
		frmClientiAp->id = DBGrid1->SelectedField->DataSet->FieldByName("id")
			->AsInteger;
		frmClientiAp->ShowModal();
	}

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Query1AfterOpen(TDataSet *DataSet) {

panCombo->Visible = true;
/*panApartamente->Visible = false;
panClientiApartamente->Visible = false; */
	if (tabela == "apartamente" && update) {
	   //	panApartamente->Visible = true;
		panApartamente->BringToFront();

		ComboList(cbNrCam, "nrcam", tabela.t_str(), true, "");
		ComboList(cbZona, "zona", tabela.t_str(), true, "");
		ComboList(cbDecomandat, "dsc", tabela.t_str(), true, "");
		ComboList(cbEtaj, "etaj", tabela.t_str(), true, "");
		ComboList(cbPret, "pret", tabela.t_str(), true, "");
		ComboList(cbMoneda, "moneda", tabela.t_str(), true, "");
		ComboList(cbMobilat, "mobilat", tabela.t_str(), true, "");
		ComboList(cbUtilat, "utilat", tabela.t_str(), true, "");

		cbNrCamChange(cbNrCam);

	}
	if (tabela == "clienti_apartamente" && update) {
	   //	panClientiApartamente->Visible = true;
		panClientiApartamente->BringToFront();

		ComboList(cbClApZona, "zone.den", "zone,localitati,judete", true,
				" WHERE zone.localitate = localitati.id and localitati.judet=judete.id \
				  and localitati.den='Galati' and judete.den='Galati' ");
		ComboList(cbClApDsc, "dsc", tabela.t_str(), true, "");
		ComboList(cbClApPretMin, "pret_min", tabela.t_str(), true, "");
		ComboList(cbClApPretMax, "pret_max", tabela.t_str(), true, "");
		ComboList(cbClApMoneda, "moneda", tabela.t_str(), true, "");
		ComboList(cbClApNrpers, "nrpers", tabela.t_str(), true, "");
		ComboList(cbClApPercontract, "per_contract", tabela.t_str(), true, "");
		cbNrCamChange(cbClApNrcam);

	}
	if (tabela == "agentii") {
		panCombo->Visible = false;
	}

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Agentii1Click(TObject *Sender) {
	frmAgentii->operatie = "add";
	frmAgentii->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::cbNrCamChange(TObject *Sender) {
	int first = 1;
	char buffer[2000];
	int incl_inchiriat=0;
	int incl_marja=0;
	TList *cbList = new TList();
	TStringList *fieldList = new TStringList();
	UnicodeString valoare = "";

	cbList->Clear();
	fieldList->Clear();
	if (tabela == "apartamente") {
		cbList->Add(cbNrCam);
		cbList->Add(cbZona);
		cbList->Add(cbDecomandat);
		cbList->Add(cbEtaj);
		cbList->Add(cbPret);
		cbList->Add(cbMoneda);
		cbList->Add(cbMobilat);
		cbList->Add(cbUtilat);
		fieldList->Delimiter='|';
		fieldList->DelimitedText="nrcam|zona|dsc|etaj|pret|moneda|mobilat|utilat";
		incl_inchiriat=ckbInclInchiriate->Checked;
    	incl_marja=ckbMarja->Checked;
	}
	if (tabela == "clienti_apartamente") {
		cbList->Add(cbClApNrcam);
		cbList->Add(cbClApZona);
		cbList->Add(cbClApDsc);
		cbList->Add(cbClApNrpers);
		cbList->Add(cbClApPercontract);
		cbList->Add(cbClApPretMin);
		cbList->Add(cbClApPretMax);
		cbList->Add(cbClApMoneda);
		cbList->Add(cbClApMobilat);
		cbList->Add(cbClApUtilat);
		fieldList->Delimiter='|';
		fieldList->DelimitedText="nrcam|zone_preferate|dsc|nrpers|per_contract|pret_min|pret_max|moneda|mobilat|utilat";
		incl_inchiriat=ckbClApInclInchiriate->Checked;
		incl_marja=ckbClApMarja->Checked;
	}


 /*	for (int i = 0; i < cbList->Count; i++) {
		ShowMessage(fieldList->Strings[i]);
		ShowMessage();
	}             */

	buffer[0] = '\0';
	Query1->Close();
	update = 0;
	Query1->SQL->Clear();

	strcat(buffer, "SELECT * FROM ");
	strcat(buffer, tabela.t_str());

	if ( !isAll(cbList) ||  incl_inchiriat == false)
		strcat(buffer, " where ");
	for (int i = 0; i < cbList->Count; i++) {
		valoare = ((TComboBox *)(cbList->Items[i]))->Text ;




		if (valoare != "All") {

			if (tabela == "apartamente") {
				int idxPret = fieldList->IndexOf("pret");
				UnicodeString pret = ((TComboBox *)(cbList->Items[idxPret]))->Text;
				if (fieldList->Strings[i] == "moneda" && pret != "All")
					continue;
			}
            if (tabela == "clienti_apartamente") {
				int idxPret = fieldList->IndexOf("pret_min");
				UnicodeString pret = ((TComboBox *)(cbList->Items[idxPret]))->Text;
				if (fieldList->Strings[i] == "moneda" && pret != "All")
					continue;
				idxPret = fieldList->IndexOf("pret_max");
				pret = ((TComboBox *)(cbList->Items[idxPret]))->Text;
				if (fieldList->Strings[i] == "moneda" && pret != "All")
					continue;
			}

			if (!first) {
				strcat(buffer, " and ");
			}


			/*creare conditie pret cu marja + conversie valutara*/
			int idxMoneda = fieldList->IndexOf("moneda");
			UnicodeString moneda = ((TComboBox *)(cbList->Items[idxMoneda]))->Text;
			int valRon, valEur, valUsd;
			int valMarjaRon, valMarjaEur, valMarjaUsd;
			UnicodeString wherePret;
			if ( (fieldList->Strings[i] == "pret" ||
				  fieldList->Strings[i] == "pret_min" ||
				  fieldList->Strings[i] == "pret_max" ) && moneda != "All") {
				setValori(StrToInt(valoare), moneda, valRon, valEur, valUsd);
				setValori(StrToInt(frmMain->setari.marja_cautare), frmMain->setari.moneda_marja_cautare,
									 valMarjaRon, valMarjaEur, valMarjaUsd);

				if ( incl_marja)
					wherePret = "(( ( (" +
							fieldList->Strings[i] +
							" >=" + IntToStr(valRon-valMarjaRon) +
							" and " + fieldList->Strings[i] +
							" <=" + IntToStr(valRon+valMarjaRon) +
							") and moneda='RON') or ( (" +
							fieldList->Strings[i] +
							" >=" + IntToStr(valEur-valMarjaEur) +
							" and " + fieldList->Strings[i] +
							" <=" + IntToStr(valEur+valMarjaEur) +
							") and moneda='EUR') or ( (" +
							fieldList->Strings[i] +
							" >=" + IntToStr(valUsd-valMarjaUsd) +
							" and " + fieldList->Strings[i] +
							" <=" + IntToStr(valUsd+valMarjaUsd) +
							") and moneda='USD') or ((" +
							fieldList->Strings[i] +
							" >=" + IntToStr(StrToInt(valoare)-StrToInt(frmMain->setari.marja_cautare)) +
							" and " + fieldList->Strings[i] +
							" <=" + IntToStr(StrToInt(valoare)+StrToInt(frmMain->setari.marja_cautare)) +
							") and moneda='') or ((" + fieldList->Strings[i]+"=0) and (moneda=''))) )";
				else
					wherePret = "(( (" + fieldList->Strings[i] +
							" =" + IntToStr(valRon) + " and moneda='RON') or (" +
							fieldList->Strings[i] +
							" =" + IntToStr(valEur) + " and moneda='EUR') or (" +
							fieldList->Strings[i] +
							" =" + IntToStr(valUsd) + " and moneda='USD') or (" +
							fieldList->Strings[i] +
							" =" + IntToStr(StrToInt(valoare)) + " and moneda='') or (("+fieldList->Strings[i]+"=0) and (moneda=''))))";

				strcat(buffer, wherePret.t_str());
				goto resetFirst;
			}

			strcat(buffer, "( (");
			strcat(buffer, fieldList->Strings[i].t_str());
			if (fieldList->Strings[i] == "mobilat" ||fieldList->Strings[i] == "utilat" ) {
				 strcat(buffer, " COLLATE latin1_bin");
			}
			if (fieldList->Strings[i] == "pret" ||
				fieldList->Strings[i] == "pret_min" ||
				fieldList->Strings[i] == "pret_max"
				) {
				strcat(buffer, " =");
			} else
				strcat(buffer, " like '%");

			strcat(buffer, valoare.t_str());
            if (fieldList->Strings[i] == "pret" ||
				fieldList->Strings[i] == "pret_min" ||
				fieldList->Strings[i] == "pret_max"
				) {
            	strcat(buffer, ") or ( ");
			} else
				strcat(buffer, "%') or ( ");
			strcat(buffer, fieldList->Strings[i].t_str());
			strcat(buffer, " = '' ))");
resetFirst:
			if (first) {
				first = 0;
			}
		}
	}

	if (incl_inchiriat == false) {
			if (!first) {
				strcat(buffer, " and ");
			}
			strcat(buffer, "( inchiriat = ");
			strcat(buffer, "0");
			strcat(buffer, ")");
			if (first) {
				first = 0;
			}
		}

	buffer[strlen(buffer)] = '\0';
	Query1->SQL->Add(buffer);
	Query1->Open();
	update = 1;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1DrawColumnCell
	(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State) {

	if (tabela == "agentii") {
        return ;
	}

	if (Column->Field->DataSet->FieldByName("inchiriat")->AsInteger == 1)
		DBGrid1->Canvas->Brush->Color = clYellow;


	if (State.Contains(gdSelected)) {
		DBGrid1->Canvas->Brush->Color = clNavy;

		if (Column->Field->DataSet->FieldByName("inchiriat")->AsInteger == 1)
			DBGrid1->Canvas->Font->Color = clYellow;
		else
        	DBGrid1->Canvas->Font->Color = clWhite;
	}
	else
		DBGrid1->Canvas->Font->Color = clBlack;

	DBGrid1->DefaultDrawColumnCell(Rect, DataCol, Column, State);

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Cauta1Click(TObject *Sender) {
	panCauta->Visible = true;
	panCauta->BringToFront();
	txtCauta->SetFocus();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Cauta(char *text, const char *field,
	const char *table) {
	TListItem *pItem;
	char buffer[2000];

	buffer[0] = '\0';
	cbQuery->Close();
	cbQuery->DatabaseName = Database->DatabaseName;
	cbQuery->SQL->Clear();

	strcat(buffer, "SELECT ");
	strcat(buffer, field);
	strcat(buffer, ",id from ");
	strcat(buffer, table);
	strcat(buffer, " where ");
	strcat(buffer, field);
	strcat(buffer, " like '%");
	strcat(buffer, text);
	strcat(buffer, "%'");
	buffer[strlen(buffer)] = '\0';

	// cbQuery->SQL->Add(buffer);
	cbQuery->SQL->Text = buffer;
	cbQuery->Open();

	if (!cbQuery->IsEmpty()) {

		do {
			// for (int i=1; i<=cbQuery->RecordCount; i++) {
			pItem = ListView1->Items->Add();
			pItem->Caption = cbQuery->FieldByName("id")->AsString;
			pItem->SubItems->Add(table);
			pItem->SubItems->Add(getDen(table));
			pItem->SubItems->Add(cbQuery->FieldByName(field)->AsString);

			// if (i != cbQuery->RecordCount)
			cbQuery->Next();
			// }
		}
		while (!cbQuery->Eof);
	}
	cbQuery->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCautaClick(TObject *Sender) {

	if (txtCauta->Text.Length() > 0) {
		ListView1->Clear();
		/* cauta in apartamente */
		Cauta(txtCauta->Text.t_str(), "judet", "apartamente");
		Cauta(txtCauta->Text.t_str(), "localitate", "apartamente");
		Cauta(txtCauta->Text.t_str(), "nrcam", "apartamente");
		Cauta(txtCauta->Text.t_str(), "zona", "apartamente");
		Cauta(txtCauta->Text.t_str(), "bloc", "apartamente");
		Cauta(txtCauta->Text.t_str(), "ap", "apartamente");
		Cauta(txtCauta->Text.t_str(), "etaj", "apartamente");
		Cauta(txtCauta->Text.t_str(), "dsc", "apartamente");
		Cauta(txtCauta->Text.t_str(), "grupsanitar", "apartamente");
		Cauta(txtCauta->Text.t_str(), "pret", "apartamente");
		Cauta(txtCauta->Text.t_str(), "moneda", "apartamente");

		/* De pastrat dupa ce se elimina duplicatele
		Cauta(txtCauta->Text.t_str(), "data", "apartamente");
		Cauta(txtCauta->Text.t_str(), "data_modificarii", "apartamente"); */
		Cauta(txtCauta->Text.t_str(), "data_modificarii", "apartamente");

		/* cauta in imbunatatiri (si campuri booleane) */
		if (isCampBool(txtCauta->Text.t_str())) {
			Cauta("1", txtCauta->Text.t_str(), "apartamente");
		}

		Cauta(txtCauta->Text.t_str(), "mobilat", "apartamente");
		Cauta(txtCauta->Text.t_str(), "utilat", "apartamente");
		Cauta(txtCauta->Text.t_str(), "nume", "apartamente");
		Cauta(txtCauta->Text.t_str(), "telefon", "apartamente");
		Cauta(txtCauta->Text.t_str(), "info_prop", "apartamente");
		Cauta(txtCauta->Text.t_str(), "altele", "apartamente");

		/* cauta in agentii */
		Cauta(txtCauta->Text.t_str(), "nume", "agentii");
		Cauta(txtCauta->Text.t_str(), "telefon", "agentii");

		/* cauta in clienti_apartamente */

		//TODO
	   /*	Cauta(txtCauta->Text.t_str(), "judet", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "localitate", "clienti_apartamente");  */
		Cauta(txtCauta->Text.t_str(), "nrcam", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "zone_preferate", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "zone_excluse", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "dsc", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "pret_min", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "pret_max", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "moneda", "clienti_apartamente");

		/* De pastrat dupa ce se elimina duplicatele
		Cauta(txtCauta->Text.t_str(), "data", "apartamente");
		Cauta(txtCauta->Text.t_str(), "data_modificarii", "apartamente"); */
		Cauta(txtCauta->Text.t_str(), "data_modificarii", "clienti_apartamente");

		/* cauta in imbunatatiri (si campuri booleane) */
		if (isCampBool(txtCauta->Text.t_str())) {
			Cauta("1", txtCauta->Text.t_str(), "clienti_apartamente");
		}

		Cauta(txtCauta->Text.t_str(), "mobilat", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "utilat", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "nume", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "telefon", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "informatii", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "nrpers", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "per_contract", "clienti_apartamente");

	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::ListView1DblClick(TObject *Sender) {
	UnicodeString tmpTable;

	sqlSelect->Close();
	sqlSelect->SQL->Clear();
	sqlSelect->DatabaseName = Database->DatabaseName;

	tmpTable = ListView1->Selected->SubItems->Strings[0];

	sqlSelect->SQL->Text = "SELECT * from " + tmpTable + " where id=" + Trim
		(ListView1->Selected->Caption.ToInt());
	sqlSelect->Open();
	if (tmpTable == "apartamente") {
		frmAp->operatie = "mod";
		frmAp->id = ListView1->Selected->Caption.ToInt();
		frmAp->ShowModal();
	}
	if (tmpTable == "agentii") {
		frmAgentii->operatie = "mod";
		frmAgentii->id = ListView1->Selected->Caption.ToInt();
		frmAgentii->ShowModal();
	}
	if (tmpTable == "clienti_apartamente") {
		frmClientiAp->operatie = "mod";
		frmClientiAp->id = ListView1->Selected->Caption.ToInt();
		frmClientiAp->ShowModal();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::TreeView1Click(TObject *Sender) {
	panCauta->Visible = false;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1MouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y) {

	if (Button == mbRight)
		pmDelete->Popup(Mouse->CursorPos.x, Mouse->CursorPos.y);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Detalii1Click(TObject *Sender) {
	DBGrid1DblClick(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Sterge1Click(TObject *Sender) {
	sqlDelete->DatabaseName = Database->DatabaseName;
	sqlDelete->DeleteSQL->Clear();
	sqlDelete->DeleteSQL->Text = "DELETE FROM " + tabela + " WHERE id=" + Trim
		(DBGrid1->SelectedField->DataSet->FieldByName("id")->AsString);

	UnicodeString msg =
		"Sunteti sigur ca doriti sa stergeti inregistrarea selectata??";
	UnicodeString cap = "Stergere";

	if (Application->MessageBox(msg.w_str(), cap.w_str(),
			MB_YESNO | MB_ICONWARNING) == ID_YES)
		sqlDelete->ExecSQL(ukDelete);
	Query1->Close();
	Query1->Open();

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action) {
	Database->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::imgRefreshClick(TObject *Sender) {
	Query1->Close();
	Query1->Open();
	if (tabela == "apartamente") {
    	cbNrCamChange(Sender);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1TitleClick(TColumn *Column) {

	update = 0;
	Query1->Close();
	if ((orderby == Column->FieldName) && (strcmp(orderType, "ASC") == 0))
		orderType = "DESC";
	else
		orderType = "ASC";

	orderby = Column->FieldName;
	Query1->Open();
	update = 1;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::Query1BeforeOpen(TDataSet *DataSet) {
	if (orderby != NULL) {
		int pos;
		pos = Query1->SQL->Text.Pos("ORDER");
		if (pos > 0) {
			Query1->SQL->Text = Query1->SQL->Text.SubString(0, pos - 3);
		}
		Query1->SQL->Text = Query1->SQL->Text + " ORDER BY " + orderby + " " +
			orderType;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Backup1Click(TObject *Sender) {
	UnicodeString cmd;
	UnicodeString password = Database->Params->ValueFromIndex
		[Database->Params->IndexOfName("PASSWORD")];
	UnicodeString user = Database->Params->ValueFromIndex
		[Database->Params->IndexOfName("USER NAME")];
	UnicodeString path = ExtractFilePath(Application->ExeName) + "backup\\";

	if (!DirectoryExists(path)) {
		CreateDir(path);
	}

	cmd = "cmd /c \"mysqldump se_inchiriaza --host=85.121.123.134 -u" + user + " -p" + password +
		"> \"" + path + "backup_db_" + DateTimeToStr(Date()) + "\"\""; /* +
	+
	"> " + ExtractFilePath(Application->ExeName) +
	; */

	WinExec(cmd.t_str(), SW_HIDE);

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::imgSiglaClick(TObject *Sender) {
	ShellExecute(0, "open", "http://www.se-inchiriaza.ro", "", "",
		SW_SHOWNORMAL);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender) {
	TreeView1->Items->GetFirstNode()->Expand(true);
	TreeView1->Items->GetFirstNode()->getNextSibling()->Expand(true);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Apartamente2Click(TObject *Sender) {
	frmClientiAp->operatie = "add";
	frmClientiAp->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Label19Click(TObject *Sender)
{
frmClientiAp->operatie = "add";
frmClientiAp->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Setari1Click(TObject *Sender)
{
frmSetari->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::ListBox1DragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
Accept = Source->Equals(DBGrid1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ListBox1DragDrop(TObject *Sender, TObject *Source, int X,
		  int Y)
{
ShowMessage(DBGrid1->SelectedField->DataSet->FieldByName("id")->AsString);
}
//---------------------------------------------------------------------------




