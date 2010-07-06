//---------------------------------------------------------------------------

#ifndef clienti_apartamenteH
#define clienti_apartamenteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <DBTables.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmClientiAp : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabeledEdit *txtNume;
	TMemo *memInfo;
	TLabeledEdit *txtTel;
	TGroupBox *GroupBox2;
	TCheckListBox *cblImbunatatiri;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label10;
	TLabel *Label11;
	TLabeledEdit *txtPretMin;
	TComboBox *txtMoneda;
	TComboBox *txtDsc;
	TComboBox *txtJudet;
	TComboBox *txtLocalitate;
	TButton *btnLocalitate;
	TListBox *txtZonePreferate;
	TListBox *txtNrcam;
	TLabel *Label1;
	TLabeledEdit *txtNrPersoane;
	TLabeledEdit *txtPretMax;
	TListBox *txtZoneExcluse;
	TLabeledEdit *txtPerContract;
	TLabel *Label2;
	TLabel *Label6;
	TGroupBox *GroupBox4;
	TCheckListBox *cblMobilat;
	TLabel *Label7;
	TLabel *Label8;
	TGroupBox *GroupBox5;
	TCheckListBox *cblUtilat;
	TButton *btnStergeTot;
	TButton *btnInchiriat;
	TButton *btnSalveaza;
	TButton *btnRenunta;
	TUpdateSQL *insertQuery;
	TUpdateSQL *SQL;
	TQuery *getLocId;
	void __fastcall btnStergeTotClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall txtJudetChange(TObject *Sender);
	void __fastcall txtLocalitateChange(TObject *Sender);
	void __fastcall btnLocalitateClick(TObject *Sender);
	void __fastcall btnRenuntaClick(TObject *Sender);
	void __fastcall btnInchiriatClick(TObject *Sender);
	void __fastcall btnSalveazaClick(TObject *Sender);
	void __fastcall Label2Click(TObject *Sender);
	void __fastcall txtPerContractKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmClientiAp(TComponent* Owner);
	UnicodeString operatie;
	int 		  id;
	int 		  inchiriat;
	int			  locID;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClientiAp *frmClientiAp;
//---------------------------------------------------------------------------
#endif
