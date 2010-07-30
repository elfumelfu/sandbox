// $$---- Form HDR ----
// ---------------------------------------------------------------------------

#ifndef mainH
#define mainH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
#include <Buttons.hpp>
#include <pngimage.hpp>
#include <jpeg.hpp>
#include <DBXMySql.hpp>
#include <SqlExpr.hpp>
#include <WideStrings.hpp>
#include "JvExExtCtrls.hpp"
#include "JvNetscapeSplitter.hpp"
#include "JvCaptionPanel.hpp"
#include "JvExtComponent.hpp"
#include "ButtonWithColor.hpp"


#define SETARI_INI_FILE ExtractFilePath(Application->ExeName)+"setari.ini"

// ---------------------------------------------------------------------------
class TSetari {
public:
	float curs_eur;
	float curs_usd;
	int marja_cautare;
	UnicodeString moneda_marja_cautare;
	UnicodeString judet;
	UnicodeString localitate;

	// Metode
	TSetari() {
	};
	TSetari(UnicodeString iniFile);
	void LoadFromFile(UnicodeString iniFile);
	void SaveToFile(UnicodeString iniFile);
};

// ---------------------------------------------------------------------------
class TfrmMain : public TForm {
__published: // IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Iesier1;
	TDatabase *Database;
	TStatusBar *StatusBar;
	TMenuItem *Apartamente1;
	TMenuItem *Adauga1;
	TTreeView *TreeView1;
	TDataSource *DataSource1;
	TQuery *Query1;
	TDBGrid *DBGrid1;
	TQuery *sqlSelect;
	TMenuItem *Agentii1;
	TPanel *panMain;
	TSplitter *Splitter1;
	TPanel *panApartamente;
	TComboBox *cbNrCam;
	TQuery *cbQuery;
	TLabel *Label1;
	TComboBox *cbZona;
	TLabel *Label2;
	TComboBox *cbDecomandat;
	TLabel *Label3;
	TComboBox *cbEtaj;
	TLabel *Label4;
	TComboBox *cbPret;
	TLabel *Label5;
	TComboBox *cbMoneda;
	TLabel *Label6;
	TComboBox *cbMobilat;
	TLabel *Label7;
	TComboBox *cbUtilat;
	TLabel *Label8;
	TCheckBox *ckbInclInchiriate;
	TMenuItem *Cauta1;
	TMenuItem *N1;
	TPanel *panCauta;
	TListView *ListView1;
	TEdit *txtCauta;
	TButton *btnCauta;
	TPopupMenu *pmDelete;
	TMenuItem *Sterge1;
	TMenuItem *Detalii1;
	TUpdateSQL *sqlDelete;
	TPanel *panToolbar;
	TImage *imgCauta;
	TImage *imgRefresh;
	TLabel *lblAdaugaAp;
	TMenuItem *Backup1;
	TPanel *panStanga;
	TImage *imgSigla;
	TMenuItem *AdaugaClienti1;
	TMenuItem *Apartamente2;
	TPanel *panCombo;
	TPanel *panClientiApartamente;
	TLabel *Label9;
	TComboBox *cbClApNrcam;
	TComboBox *cbClApZona;
	TLabel *Label10;
	TComboBox *cbClApDsc;
	TLabel *Label11;
	TComboBox *cbClApMoneda;
	TLabel *Label12;
	TComboBox *cbClApPretMin;
	TLabel *Label13;
	TComboBox *cbClApMobilat;
	TLabel *Label14;
	TComboBox *cbClApUtilat;
	TLabel *Label15;
	TComboBox *cbClApPretMax;
	TLabel *Label16;
	TComboBox *cbClApNrpers;
	TLabel *Label17;
	TComboBox *cbClApPercontract;
	TLabel *Label18;
	TCheckBox *ckbClApInclInchiriate;
	TLabel *Label19;
	TMenuItem *N2;
	TMenuItem *Setari1;
	TCheckBox *ckbMarja;
	TCheckBox *ckbClApMarja;
	TJvNetscapeSplitter *JvNetscapeSplitter1;
	TPanel *panAlerta;
	TJvCaptionPanel *JvCaptionPanel1;
	TDBGrid *DBGridClienti;
	TJvNetscapeSplitter *JvNetscapeSplitter2;
	TDataSource *DataSource2;
	TQuery *queryClienti;
	TDateTimePicker *DateTimePicker1;
	TGroupBox *GroupBox1;
	TListBox *ListBox1;
	TLabeledEdit *txtAlertaIdOferta;
	TLabeledEdit *txtAlertaTipOferta;
	TGroupBox *GroupBox2;
	TListBox *ListBox2;
	TLabeledEdit *txtAlertaIdCerere;
	TLabeledEdit *txtAlertaTipCerere;
	TGroupBox *GroupBox3;
	TMemo *memDetalii;
	TButton *btnAlertaSalveaza;
	TButton *btnAlertaStergeTot;
	TTimer *timerAlerta;

	void __fastcall DatabaseAfterConnect(TObject *Sender);
	void __fastcall Iesier1Click(TObject *Sender);
	void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
	void __fastcall Adauga1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall Query1AfterOpen(TDataSet *DataSet);
	void __fastcall Agentii1Click(TObject *Sender);
	void __fastcall cbNrCamChange(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall Cauta1Click(TObject *Sender);
	void __fastcall btnCautaClick(TObject *Sender);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall TreeView1Click(TObject *Sender);
	void __fastcall DBGrid1MouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall Detalii1Click(TObject *Sender);
	void __fastcall Sterge1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall imgRefreshClick(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall Query1BeforeOpen(TDataSet *DataSet);
	void __fastcall Backup1Click(TObject *Sender);
	void __fastcall imgSiglaClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Apartamente2Click(TObject *Sender);
	void __fastcall Label19Click(TObject *Sender);
	void __fastcall Setari1Click(TObject *Sender);
	void __fastcall ListBox1DragOver(TObject *Sender, TObject *Source, int X,
		int Y, TDragState State, bool &Accept);
	void __fastcall ListBox1DragDrop(TObject *Sender, TObject *Source, int X,
		int Y);
	void __fastcall JvCaptionPanel1ButtonClick
		(TObject *Sender, TJvCapBtnStyle Button);
	void __fastcall DBGrid1MouseMove(TObject *Sender, TShiftState Shift, int X,
		int Y);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall DBGridClientiMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall DBGridClientiMouseMove
		(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ListBox2DragOver(TObject *Sender, TObject *Source, int X,
		int Y, TDragState State, bool &Accept);
	void __fastcall ListBox2DragDrop(TObject *Sender, TObject *Source, int X,
		int Y);
	void __fastcall btnAlertaSalveazaClick(TObject *Sender);
	void __fastcall btnAlertaStergeTotClick(TObject *Sender);
	void __fastcall DBGridClientiDblClick(TObject *Sender);
	void __fastcall DBGridClientiDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
	void __fastcall timerAlertaTimer(TObject *Sender);
	void __fastcall StatusBarDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect);
	void __fastcall FormResize(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TfrmMain(TComponent* Owner);

	UnicodeString tabela;
	int update;
	TSetari setari;

	void __fastcall ComboList(TComboBox *combo, char *field, UnicodeString table,
		bool addAll, const char * where);
	void __fastcall SelectList(TListBox *list, char *field, char *table,
		bool addAll, const char * where);
	void __fastcall Cauta(char *text, char *field, char *table);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
// ---------------------------------------------------------------------------
#endif
