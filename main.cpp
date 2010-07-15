// $$---- Form CPP ----
// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvExExtCtrls"
#pragma link "JvNetscapeSplitter"
#pragma link "JvCaptionPanel"
#pragma link "JvExtComponent"
#pragma resource "*.dfm"

#include <IniFiles.hpp>

#include "apartamente.h"
#include "agentii.h"
#include "clienti_apartamente.h"
#include "setari.h"
#include "tools.h"

#define NR_TABLES 3
#define NR_CAMPURI_BOOL 13

TfrmMain *frmMain;

int blinkAlert = 0;

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
		if (((TComboBox*)(list->Items[i]))->Text != "All") {
			return 0;
		}
	}
	return 1;
}

void setValori(int val, UnicodeString moneda, int &ron, int &eur, int &usd) {
	if (moneda == "RON") {
		ron = StrToInt(val);
		eur = (int)(ron / frmMain->setari.curs_eur);
		usd = (int)(ron / frmMain->setari.curs_usd);
	}
	if (moneda == "EUR") {
		eur = StrToInt(val);
		ron = (int)(eur * frmMain->setari.curs_eur);
		usd = (int)(ron / frmMain->setari.curs_usd);
	}
	if (moneda == "USD") {
		usd = StrToInt(val);
		ron = (int)(usd * frmMain->setari.curs_usd);
		eur = (int)(ron / frmMain->setari.curs_eur);
	}

}

TSetari::TSetari(UnicodeString iniFile) {

	LoadFromFile(iniFile);
}

void TSetari::LoadFromFile(UnicodeString iniFile) {

	TIniFile * ini;

	if (FileExists(iniFile)) {
		ini = new TIniFile(iniFile);
		curs_eur = ini->ReadFloat("General", "curs_eur", 0);
		curs_usd = ini->ReadFloat("General", "curs_usd", 0);
		marja_cautare = ini->ReadInteger("General", "marja_cautare", 0);
		moneda_marja_cautare = ini->ReadString
			("General", "moneda_marja_cautare", "RON");
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

void __fastcall TfrmMain::ComboList(TComboBox *combo, char *field,
	UnicodeString table, bool addAll, const char * where) {

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

void __fastcall TfrmMain::SelectList(TListBox *list, char *field, char *table,
	bool addAll, const char * where) {
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
	DecimalSeparator = '.';
	tabela = "apartamente";
	this->setari.LoadFromFile(SETARI_INI_FILE);
	ckbMarja->Caption = "± " + IntToStr(frmMain->setari.marja_cautare)
		+ " " + frmMain->setari.moneda_marja_cautare;
	ckbClApMarja->Caption = "± " + IntToStr(frmMain->setari.marja_cautare)
		+ " " + frmMain->setari.moneda_marja_cautare;
	update = 1;
	DBGrid1->Columns->LoadFromFile(ExtractFilePath(Application->ExeName)
		+ tabela + ".grid");
	JvNetscapeSplitter1->Maximized = true;
	JvNetscapeSplitter2->Maximized = true;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DatabaseAfterConnect(TObject *Sender) {

	StatusBar->Panels->Items[1]->Text = "Conectat la '" + Database->Params->ValueFromIndex
		[0] + "@" + Database->AliasName + "'.";

	TTreeNode *node = TreeView1->TopItem->getFirstChild();
	TreeView1->Selected = node;
    sqlSelect->Close();
	sqlSelect->DatabaseName = Database->DatabaseName;
	sqlSelect->SQL->Clear();
	UnicodeString data;
	DateTimeToString(data, "YYYY-MM-dd" ,Date());
	sqlSelect->SQL->Text = "SELECT count(*) as nralerte FROM alerte WHERE data ='"+ data +"'" ;
	sqlSelect->Open();

	if (sqlSelect->FieldByName("nralerte")->AsInteger) {
		blinkAlert=1;
        timerAlerta->Enabled=true;
	}
	sqlSelect->Close();
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
    if (TreeView1->Selected->Text == "Alerte") {
		Query1->SQL->Text = "SELECT * FROM alerte";
		tabela = "alerte";
		orderby = "data";
		orderType = "DESC";
		timerAlerta->Enabled=false;
		blinkAlert = 0;
		StatusBar->Repaint();
	}

	DBGrid1->Columns->LoadFromFile(ExtractFilePath(Application->ExeName)
		+ tabela + ".grid");



	Query1->Open();
    DBGrid1CellClick(DBGrid1->Columns->Items[0]);
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

	if (tabela == "alerte") {
	   sqlSelect->SQL->Text = "SELECT * from " + DBGrid1->SelectedField->DataSet->FieldByName("tabelaoferta")->AsString + " where id=" + Trim
		(DBGrid1->SelectedField->DataSet->FieldByName("idoferta")->AsString);
	}  else {
	  sqlSelect->SQL->Text = "SELECT * from " + tabela + " where id=" + Trim
		(DBGrid1->SelectedField->DataSet->FieldByName("id")->AsString);
	}
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

	if (tabela == "alerte") {
		if (DBGrid1->SelectedField->DataSet->FieldByName("tabelaoferta")->AsString == "apartamente") {
			frmAp->operatie = "mod";
			frmAp->id = DBGrid1->SelectedField->DataSet->FieldByName("idoferta")
				->AsInteger;
			frmAp->ShowModal();
			if (DBGrid1->SelectedField->DataSet->FieldByName("idcerere")->AsInteger) {
               sqlSelect->SQL->Text = "SELECT * from " + DBGrid1->SelectedField->DataSet->FieldByName("tabelacerere")->AsString + " where id=" + Trim
				(DBGrid1->SelectedField->DataSet->FieldByName("idcerere")->AsString);
				sqlSelect->Close();
				sqlSelect->Open();
				frmClientiAp->operatie = "mod";
				frmClientiAp->id = DBGrid1->SelectedField->DataSet->FieldByName("idcerere")
				->AsInteger;
				frmClientiAp->ShowModal();
			}

		} else
		if (DBGrid1->SelectedField->DataSet->FieldByName("tabelaoferta")->AsString == "clienti_apartamente") {
            frmClientiAp->operatie = "mod";
			frmClientiAp->id = DBGrid1->SelectedField->DataSet->FieldByName("idoferta")
				->AsInteger;
			frmClientiAp->ShowModal();
			if (DBGrid1->SelectedField->DataSet->FieldByName("idcerere")->AsInteger) {
			sqlSelect->SQL->Text = "SELECT * from " + DBGrid1->SelectedField->DataSet->FieldByName("tabelacerere")->AsString + " where id=" + Trim
		(DBGrid1->SelectedField->DataSet->FieldByName("idcerere")->AsString);

		sqlSelect->Close();
		sqlSelect->Open();
		frmAp->operatie = "mod";
		frmAp->id = DBGrid1->SelectedField->DataSet->FieldByName("idcerere")
			->AsInteger;
		frmAp->ShowModal();
            }
		}



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
	/* panApartamente->Visible = false;
	panClientiApartamente->Visible = false; */
	if (tabela == "apartamente" && update) {
		// panApartamente->Visible = true;
		panApartamente->BringToFront();

		ComboList(cbNrCam, "nrcam", tabela, true, "");
		ComboList(cbZona, "zona", tabela, true, "");
		ComboList(cbDecomandat, "dsc", tabela, true, "");
		ComboList(cbEtaj, "etaj", tabela, true, "");
		ComboList(cbPret, "pret", tabela, true, "");
		ComboList(cbMoneda, "moneda", tabela, true, "");
		ComboList(cbMobilat, "mobilat", tabela, true, "");
		ComboList(cbUtilat, "utilat", tabela, true, "");

		cbNrCamChange(cbNrCam);

	}
	if (tabela == "clienti_apartamente" && update) {
		// panClientiApartamente->Visible = true;
		panClientiApartamente->BringToFront();

		ComboList(cbClApZona, "zone.den", "zone,localitati,judete", true, " WHERE zone.localitate = localitati.id and localitati.judet=judete.id \
				  and localitati.den='Galati' and judete.den='Galati' ");
		ComboList(cbClApDsc, "dsc", tabela, true, "");
		ComboList(cbClApPretMin, "pret_min", tabela, true, "");
		ComboList(cbClApPretMax, "pret_max", tabela, true, "");
		ComboList(cbClApMoneda, "moneda", tabela, true, "");
		ComboList(cbClApNrpers, "nrpers", tabela, true, "");
		ComboList(cbClApPercontract, "per_contract", tabela, true, "");
		cbNrCamChange(cbClApNrcam);

	}
	if (tabela == "agentii") {
		panCombo->Visible = false;
	}
	if (tabela == "alerte") {
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
	UnicodeString buffer;
	int incl_inchiriat = 0;
	int incl_marja = 0;
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
		fieldList->Delimiter = '|';
		fieldList->DelimitedText =
			"nrcam|zona|dsc|etaj|pret|moneda|mobilat|utilat";
		incl_inchiriat = ckbInclInchiriate->Checked;
		incl_marja = ckbMarja->Checked;
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
		fieldList->Delimiter = '|';
		fieldList->DelimitedText =
			"nrcam|zone_preferate|dsc|nrpers|per_contract|pret_min|pret_max|moneda|mobilat|utilat";
		incl_inchiriat = ckbClApInclInchiriate->Checked;
		incl_marja = ckbClApMarja->Checked;
	}

	/* for (int i = 0; i < cbList->Count; i++) {
	ShowMessage(fieldList->Strings[i]);
	ShowMessage();
	} */

	Query1->Close();
	update = 0;
	Query1->SQL->Clear();

	buffer = "SELECT * FROM ";
	buffer = UnicodeCat(buffer, tabela);

	if (!isAll(cbList) || incl_inchiriat == false)
		buffer += " WHERE ";
	for (int i = 0; i < cbList->Count; i++) {
		valoare = ((TComboBox*)(cbList->Items[i]))->Text;

		if (valoare != "All") {

			if (tabela == "apartamente") {
				int idxPret = fieldList->IndexOf("pret");
				UnicodeString pret = ((TComboBox*)(cbList->Items[idxPret]))
					->Text;
				if (fieldList->Strings[i] == "moneda" && pret != "All")
					continue;
			}
			if (tabela == "clienti_apartamente") {
				int idxPret = fieldList->IndexOf("pret_min");
				UnicodeString pret = ((TComboBox*)(cbList->Items[idxPret]))
					->Text;
				if (fieldList->Strings[i] == "moneda" && pret != "All")
					continue;
				idxPret = fieldList->IndexOf("pret_max");
				pret = ((TComboBox*)(cbList->Items[idxPret]))->Text;
				if (fieldList->Strings[i] == "moneda" && pret != "All")
					continue;
			}

			if (!first) {
				buffer += " and ";
			}

			/* creare conditie pret cu marja + conversie valutara */
			int idxMoneda = fieldList->IndexOf("moneda");
			UnicodeString moneda = ((TComboBox*)(cbList->Items[idxMoneda]))
				->Text;
			int valRon, valEur, valUsd;
			int valMarjaRon, valMarjaEur, valMarjaUsd;
			UnicodeString wherePret;
			if ((fieldList->Strings[i] == "pret" || fieldList->Strings[i]
					== "pret_min" || fieldList->Strings[i] == "pret_max") && moneda != "All") {
				setValori(StrToInt(valoare), moneda, valRon, valEur, valUsd);
				setValori(StrToInt(frmMain->setari.marja_cautare),
					frmMain->setari.moneda_marja_cautare, valMarjaRon, valMarjaEur, valMarjaUsd);

				if (incl_marja)
					wherePret = "(( ( (" + fieldList->Strings[i]
						+ " >=" + IntToStr(valRon - valMarjaRon) + " and " + fieldList->Strings[i]
						+ " <=" + IntToStr(valRon + valMarjaRon) + ") and moneda='RON') or ( (" +
						fieldList->Strings[i] + " >=" + IntToStr(valEur - valMarjaEur)
						+ " and " + fieldList->Strings[i] + " <=" + IntToStr(valEur + valMarjaEur) +
						") and moneda='EUR') or ( (" + fieldList->Strings[i]
						+ " >=" + IntToStr(valUsd - valMarjaUsd) + " and " + fieldList->Strings[i]
						+ " <=" + IntToStr(valUsd + valMarjaUsd) + ") and moneda='USD') or ((" +
						fieldList->Strings[i] + " >=" + IntToStr
						(StrToInt(valoare) - StrToInt(frmMain->setari.marja_cautare))
						+ " and " + fieldList->Strings[i] + " <=" + IntToStr(StrToInt(valoare) + StrToInt
					(frmMain->setari.marja_cautare)) + ") and moneda='') or ((" + fieldList->Strings[i] +
						"=0) and (moneda=''))) )";
				else
					wherePret = "(( (" + fieldList->Strings[i] + " =" + IntToStr
						(valRon) + " and moneda='RON') or (" +
						fieldList->Strings[i] + " =" + IntToStr(valEur) + " and moneda='EUR') or (" +
						fieldList->Strings[i] + " =" + IntToStr(valUsd) + " and moneda='USD') or (" +
						fieldList->Strings[i] + " =" + IntToStr(StrToInt(valoare))
						+ " and moneda='') or ((" + fieldList->Strings[i] + "=0) and (moneda=''))))";

				buffer += wherePret;
				goto resetFirst;
			}

			buffer +="( (";
			buffer +=fieldList->Strings[i];
			if (fieldList->Strings[i] == "mobilat" || fieldList->Strings[i]
				== "utilat") {
				buffer += " COLLATE latin1_bin";
			}
			if (fieldList->Strings[i] == "pret" || fieldList->Strings[i]
				== "pret_min" || fieldList->Strings[i] == "pret_max") {
				buffer += " =";
			}
			else
				buffer += " like '%";

			buffer += valoare;
			if (fieldList->Strings[i] == "pret" || fieldList->Strings[i]
				== "pret_min" || fieldList->Strings[i] == "pret_max") {
				buffer +=") or ( ";
			}
			else
				buffer +="%') or ( ";
			buffer += fieldList->Strings[i];
			buffer += " = '' ))";
		resetFirst:
			if (first) {
				first = 0;
			}
		}
	}

	if (incl_inchiriat == false) {
		if (!first) {
			buffer += " and ";
		}
		buffer+= "( inchiriat = ";
		buffer+= "0";
		buffer+= ")";
		if (first) {
			first = 0;
		}
	}

	// buffer[buffer.Length()+1] = '\0';
	Query1->SQL->Add(buffer);
	Query1->Open();
	update = 1;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1DrawColumnCell
	(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State) {

	if (tabela == "agentii" || tabela=="alerte") {
		return;
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

void __fastcall TfrmMain::Cauta(char *text, char *field, char *table) {
	TListItem *pItem;
	char buffer[2000];

	buffer[0] = '\0';
	cbQuery->Close();
	cbQuery->DatabaseName = Database->DatabaseName;
	cbQuery->SQL->Clear();

	strcat(buffer, "SELECT ");
	strcat(buffer, field);
	strcat(buffer, ",id");
	if ((strcmp(table,"agentii")!=0) && (strcmp(table,"alerte")!=0)){
    	strcat(buffer,",inchiriat ");
	}
	strcat(buffer," from ");
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
			if ((strcmp(table,"agentii")!=0) && (strcmp(table,"alerte")!=0))
				pItem->SubItems->Add(cbQuery->FieldByName("inchiriat")->AsString);
			else
            	pItem->SubItems->Add("0");
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

		// TODO
		/* Cauta(txtCauta->Text.t_str(), "judet", "clienti_apartamente");
		Cauta(txtCauta->Text.t_str(), "localitate", "clienti_apartamente"); */
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
		Cauta(txtCauta->Text.t_str(), "data_modificarii",
			"clienti_apartamente");

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
		(ListView1->Selected->Caption);
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

	if (DBGrid1->Dragging()) {
		DBGrid1->EndDrag(true);
	}
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
	DBGrid1->Columns->SaveToFile(ExtractFilePath(Application->ExeName)
		+ tabela + ".grid");
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

	cmd = "cmd /c \"mysqldump se_inchiriaza --host=85.121.123.134 -u" + user +
		" -p" + password + "> \"" + path + "backup_db_" + DateTimeToStr(Date())
		+ "\"\""; /* +
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

void __fastcall TfrmMain::Label19Click(TObject *Sender) {
	frmClientiAp->operatie = "add";
	frmClientiAp->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::Setari1Click(TObject *Sender) {
	frmSetari->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::ListBox1DragOver
	(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept) {
	Accept = Source->Equals(DBGrid1);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::ListBox1DragDrop
	(TObject *Sender, TObject *Source, int X, int Y) {

	txtAlertaIdOferta->Text = DBGrid1->SelectedField->DataSet->FieldByName("id")->AsAnsiString;
	txtAlertaTipOferta->Text = tabela;
	ListBox1->Items->Text=DBGrid1->SelectedField->DataSet->FieldByName("telefon")->AsString;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::JvCaptionPanel1ButtonClick
	(TObject *Sender, TJvCapBtnStyle Button)

{
	if (Button == TJvCapBtnStyle::capClose) {
		JvNetscapeSplitter1->Maximized = true;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::DBGrid1MouseMove
	(TObject *Sender, TShiftState Shift, int X, int Y) {

	if (Shift.Contains(ssLeft) && JvNetscapeSplitter1->Maximized == false) {
		DBGrid1->BeginDrag(true, 5);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGrid1CellClick(TColumn *Column) {
	UnicodeString whereNrcam, whereZona, wherePret = "";
	int valRon, valEur, valUsd;
	int valMarjaRon, valMarjaEur, valMarjaUsd;
	UnicodeString pretFormat, pretFormatAp;
	int incl_inchiriate = 1;

	if (tabela != "apartamente" && tabela != "clienti_apartamente") {
		queryClienti->Close();
		DBGridClienti->Columns->Clear();
    	return;
	}

	pretFormat = "( ((pret_min >= %d and moneda ='RON') or \
					 (pret_min >= %d and moneda ='EUR') or \
					 (pret_min >= %d and moneda ='USD') or \
					 (pret_min = 0) ) and ( \
					 (pret_max <= %d and moneda ='RON') or \
					 (pret_max <= %d and moneda ='EUR') or \
					 (pret_max <= %d and moneda ='USD') or \
					 (pret_max = 0) ) )";
	pretFormatAp = "(((pret >= %d and moneda ='RON') or \
					  (pret >= %d and moneda ='EUR') or \
					  (pret >= %d and moneda ='USD') or \
					  (pret = 0) ) and ( \
					  (pret <= %d and moneda ='RON') or \
					  (pret <= %d and moneda ='EUR') or \
					  (pret <= %d and moneda ='USD') or \
					  (pret = 0) ) )";

	setValori(StrToInt(frmMain->setari.marja_cautare),
		frmMain->setari.moneda_marja_cautare, valMarjaRon, valMarjaEur, valMarjaUsd);

	if (tabela == "apartamente") {
		setValori(DBGrid1->SelectedField->DataSet->FieldByName("pret")
			->AsInteger, DBGrid1->SelectedField->DataSet->FieldByName("moneda")->AsString,
			valRon, valEur, valUsd);

		whereNrcam = "(nrcam like'%" +
			DBGrid1->SelectedField->DataSet->FieldByName("nrcam")->AsString + "%')";
		whereZona = "( (zone_preferate like'%" +
			DBGrid1->SelectedField->DataSet->FieldByName("zona")->AsString + "%') and " +
			"(zone_excluse not like'%" + DBGrid1->SelectedField->DataSet->FieldByName
			("zona")->AsString + "%') )";
		wherePret.printf(pretFormat.w_str(), valRon - valMarjaRon,
			valEur - valMarjaEur, valUsd - valMarjaUsd, valRon + valMarjaRon,
			valEur + valMarjaEur, valUsd + valMarjaUsd);

		incl_inchiriate = ckbInclInchiriate->Checked;

	}
	if (tabela == "clienti_apartamente") {
		setValori(DBGrid1->SelectedField->DataSet->FieldByName("pret_min")
			->AsInteger, DBGrid1->SelectedField->DataSet->FieldByName("moneda")->AsString,
			valRon, valEur, valUsd);

		TStringList *zone_preferate = new TStringList;
		zone_preferate->Delimiter = '/';
		zone_preferate->QuoteChar = '|';
		zone_preferate->DelimitedText =
			DBGrid1->SelectedField->DataSet->FieldByName("zone_preferate")->AsString;
		zone_preferate->Delimiter = ',';
		zone_preferate->QuoteChar = '\'';
		UnicodeString zonepreferate;
		for (int i = 0; i < zone_preferate->Count; i++) {
			zonepreferate = zonepreferate + "'" + zone_preferate->Strings[i]
				+ "',";
		}
		zonepreferate.Delete(zonepreferate.Length(), 1);

		TStringList *zone_excluse = new TStringList;
		zone_excluse->Delimiter = '/';
		zone_excluse->QuoteChar = '|';
		zone_excluse->DelimitedText =
			DBGrid1->SelectedField->DataSet->FieldByName("zone_excluse")->AsString;
		zone_excluse->Delimiter = ',';
		zone_excluse->QuoteChar = '\'';
		UnicodeString zoneexcluse;
		for (int i = 0; i < zone_excluse->Count; i++) {
			zoneexcluse = zoneexcluse + "'" + zone_excluse->Strings[i] + "',";
		}
		zoneexcluse.Delete(zoneexcluse.Length(), 1);

		TStringList *nrcam = new TStringList;
		UnicodeString nr_cam = "";
		nrcam->Delimiter = '/';
		nrcam->DelimitedText = DBGrid1->SelectedField->DataSet->FieldByName
			("nrcam")->AsString;
		for (int i = 0; i < nrcam->Count; i++) {
			nr_cam = nr_cam + "'" + nrcam->Strings[i] + "',";
		}
		nr_cam.Delete(nr_cam.Length(), 1);
		whereNrcam = "(nrcam in (" + nr_cam + "))";
		if (Trim(zonepreferate).Length()>0) {
			whereZona = " (zona in (" + zonepreferate + ")) ";
			if (Trim(zoneexcluse).Length()>0) {
				whereZona += " and (zona not in (" + zoneexcluse + ") ) ";
			}
		} else {
			if (Trim(zoneexcluse).Length()>0) {
				whereZona += "(zona not in (" + zoneexcluse + ") ) ";
			}
		}
		int valMaxRon, valMaxEur, valMaxUsd;
		setValori(DBGrid1->SelectedField->DataSet->FieldByName("pret_min")
			->AsInteger, DBGrid1->SelectedField->DataSet->FieldByName("moneda")->AsString,
			valRon, valEur, valUsd);
		setValori(DBGrid1->SelectedField->DataSet->FieldByName("pret_max")
			->AsInteger, DBGrid1->SelectedField->DataSet->FieldByName("moneda")->AsString,
			valMaxRon, valMaxEur, valMaxUsd);
		wherePret.printf(pretFormatAp.w_str(), valRon - valMarjaRon,
			valEur - valMarjaEur, valUsd - valMarjaUsd, valMaxRon + valMarjaRon,
			valMaxEur + valMarjaEur, valMaxUsd + valMarjaUsd);

		zone_preferate->Free();
		zone_excluse->Free();
		nrcam->Free();
        incl_inchiriate = ckbClApInclInchiriate->Checked;
	}
  DBGridClienti->Columns->LoadFromFile
			(ExtractFilePath(Application->ExeName) + tabelaOpusa(tabela) +".grid" );
	queryClienti->Close();
	queryClienti->DatabaseName = Database->DatabaseName;
	queryClienti->SQL->Clear();
	queryClienti->SQL->Text = "SELECT * FROM ";

	queryClienti->SQL->Text = queryClienti->SQL->Text + tabelaOpusa(tabela);

	queryClienti->SQL->Text = queryClienti->SQL->Text + " WHERE ";

	queryClienti->SQL->Text = queryClienti->SQL->Text + whereNrcam;
	if (Trim(whereZona).Length() > 0)
		queryClienti->SQL->Text = queryClienti->SQL->Text + " and " + whereZona;
	if (Trim(wherePret).Length() > 0)
		queryClienti->SQL->Text = queryClienti->SQL->Text + " and " + wherePret;
	if ( !incl_inchiriate) {
		queryClienti->SQL->Text = queryClienti->SQL->Text + " and (inchiriat = 0)";
	}

	queryClienti->Open();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGridClientiMouseUp
	(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
	if (DBGridClienti->Dragging()) {
		DBGridClienti->EndDrag(true);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGridClientiMouseMove
	(TObject *Sender, TShiftState Shift, int X, int Y) {
	if (Shift.Contains(ssLeft)) {
		DBGridClienti->BeginDrag(true, 5);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::ListBox2DragOver
	(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept) {
	Accept = (Source == DBGridClienti);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::ListBox2DragDrop
	(TObject *Sender, TObject *Source, int X, int Y) {
	txtAlertaIdCerere->Text = DBGridClienti->SelectedField->DataSet->FieldByName("id")->AsAnsiString;
	txtAlertaTipCerere->Text = tabelaOpusa(tabela);
	ListBox2->Items->Text=DBGridClienti->SelectedField->DataSet->FieldByName("telefon")->AsString;
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::btnAlertaSalveazaClick(TObject *Sender)
{
	sqlDelete->DatabaseName = Database->DatabaseName;
	sqlDelete->InsertSQL->Clear();

	if (txtAlertaIdOferta->Text.Trim() == "" ) {
		txtAlertaIdOferta->Text=0;
	}
	if (txtAlertaIdCerere->Text.Trim() == "" ) {
		txtAlertaIdCerere->Text=0;
	}

	UnicodeString data;

    DateTimeToString(data, "YYYY-MM-dd",DateTimePicker1->Date);

	sqlDelete->InsertSQL->Text = "INSERT INTO alerte (idoferta, tabelaoferta, \
			idcerere, tabelacerere, detalii, data) VALUES (" +
			txtAlertaIdOferta->Text + ",'"+
			txtAlertaTipOferta->Text + "',"+
			txtAlertaIdCerere->Text + ",'"+
			txtAlertaTipCerere->Text + "','"+
			memDetalii->Text +"','" +
			data + "')";

	sqlDelete->ExecSQL(ukInsert);
	btnAlertaStergeTotClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAlertaStergeTotClick(TObject *Sender)
{
txtAlertaIdOferta->Text ="";
txtAlertaTipOferta->Text ="";
txtAlertaIdCerere->Text ="";
txtAlertaTipCerere->Text ="";
memDetalii->Text ="";
DateTimePicker1->Date=Date();
ListBox1->Items->Clear();
ListBox2->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGridClientiDblClick(TObject *Sender)
{
sqlSelect->Close();
	sqlSelect->DatabaseName = Database->DatabaseName;
	sqlSelect->SQL->Clear();


	  sqlSelect->SQL->Text = "SELECT * from " + tabelaOpusa(tabela) + " where id=" + Trim
		(DBGridClienti->SelectedField->DataSet->FieldByName("id")->AsString);

	sqlSelect->Open();

	if (tabelaOpusa(tabela) == "apartamente") {
		frmAp->operatie = "mod";
		frmAp->id = DBGridClienti->SelectedField->DataSet->FieldByName("id")
			->AsInteger;
		frmAp->ShowModal();
		return;
	}


	if (tabelaOpusa(tabela) == "clienti_apartamente") {
		frmClientiAp->operatie = "mod";
		frmClientiAp->id = DBGridClienti->SelectedField->DataSet->FieldByName("id")
			->AsInteger;
		frmClientiAp->ShowModal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DBGridClientiDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{

	if (Column->Field->DataSet->FieldByName("inchiriat")->AsInteger == 1)
		DBGridClienti->Canvas->Brush->Color = clYellow;

	if (State.Contains(gdSelected)) {
		DBGridClienti->Canvas->Brush->Color = clNavy;

		if (Column->Field->DataSet->FieldByName("inchiriat")->AsInteger == 1)
			DBGridClienti->Canvas->Font->Color = clYellow;
		else
			DBGridClienti->Canvas->Font->Color = clWhite;
	}
	else
		DBGridClienti->Canvas->Font->Color = clBlack;

	DBGridClienti->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
  if (Item->SubItems->Strings[3] == "1")
	ListView1->Canvas->Brush->Color = clYellow;

  if (State.Contains(gdSelected)) {
		ListView1->Canvas->Brush->Color = clNavy;

		if (Item->SubItems->Strings[3] == "1")
			ListView1->Canvas->Font->Color = clYellow;
		else
			ListView1->Canvas->Font->Color = clWhite;
	}
	else
		ListView1->Canvas->Font->Color = clBlack;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::timerAlertaTimer(TObject *Sender)
{
StatusBar->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StatusBarDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect)
{
  if (blinkAlert == 1) {
	/*StatusBar1->Canvas->Brush->Color=clRed;
	StatusBar1->Canvas->FillRect(Rect);  */
	StatusBar->Canvas->Font->Name  = "Arial";
	StatusBar->Canvas->Font->Color = clRed;
	StatusBar->Canvas->Font->Style = StatusBar->Canvas->Font->Style << fsBold;
	StatusBar->Canvas->TextRect(Rect, Rect.Width() / 2 - 15, Rect.Top, "Alerte !!!");

	blinkAlert = 2;
  } else if (blinkAlert == 2) {
   /*	StatusBar1->Canvas->Brush->Color=clBtnFace;
	StatusBar1->Canvas->FillRect(Rect);*/
	StatusBar->Canvas->Font->Name  = "Arial";
	StatusBar->Canvas->Font->Color = clBlack;
	StatusBar->Canvas->Font->Style = StatusBar->Canvas->Font->Style << fsBold;
	StatusBar->Canvas->TextRect(Rect, Rect.Width() / 2 - 15, Rect.Top, "Alerte !!!");
	blinkAlert = 1;
  } else {
	StatusBar->Canvas->Font->Name  = "Arial";
	StatusBar->Canvas->Font->Color = clBlack;
	StatusBar->Canvas->Font->Style = StatusBar->Canvas->Font->Style << fsBold;
	StatusBar->Canvas->TextRect(Rect, Rect.Width() / 2 - 15, Rect.Top, "");
  }
}
//---------------------------------------------------------------------------


