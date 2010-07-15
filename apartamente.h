//---------------------------------------------------------------------------

#ifndef apartamenteH
#define apartamenteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <Keyboard.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <DB.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
#include "ButtonWithColor.hpp"
//---------------------------------------------------------------------------
class TfrmAp : public TForm
{
__published:	// IDE-managed Components
	TButton *btnSalveaza;
	TGroupBox *GroupBox1;
	TLabeledEdit *txtBloc;
	TLabeledEdit *txtAp;
	TLabeledEdit *txtEtaj;
	TLabeledEdit *txtGs;
	TLabeledEdit *txtPret;
	TGroupBox *GroupBox2;
	TCheckListBox *CheckListBox1;
	TRadioGroup *rgMobilat;
	TLabel *Label1;
	TMemo *memAltele;
	TDateTimePicker *txtDataExpirarii;
	TGroupBox *GroupBox3;
	TLabeledEdit *txtNume;
	TMemo *memInfo;
	TLabeledEdit *txtTel;
	TUpdateSQL *SQL;
	TLabel *Label2;
	TLabel *Label3;
	TButton *btnStergeTot;
	TButton *btnRenunta;
	TComboBox *txtMoneda;
	TLabel *Label4;
	TComboBox *txtDsc;
	TLabel *Label5;
	TRadioGroup *rgUtilat;
	TImage *imgPoza1;
	TImage *imgPoza2;
	TImage *imgPoza3;
	TImage *imgPoza4;
	TComboBox *txtNrcam;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TImage *imgFaraPoza;
	TOpenPictureDialog *OpenPictureDialog1;
	TQuery *getID;
	TComboBox *txtZona;
	TLabel *Label9;
	TComboBox *txtJudet;
	TLabel *Label10;
	TLabel *Label11;
	TComboBox *txtLocalitate;
	TButton *btnLocalitate;
	TUpdateSQL *insertQuery;
	TButton *btnZona;
	TBitBtnWithColor *btnInchiriat;
	void __fastcall btnSalveazaClick(TObject *Sender);
	void __fastcall btnStergeTotClick(TObject *Sender);
	void __fastcall btnRenuntaClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnInchiriatClick(TObject *Sender);
	void __fastcall txtGsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall imgPoza1Click(TObject *Sender);
	void __fastcall imgPoza2Click(TObject *Sender);
	void __fastcall imgPoza3Click(TObject *Sender);
	void __fastcall imgPoza4Click(TObject *Sender);
	void __fastcall imgPoza1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall txtJudetChange(TObject *Sender);
	void __fastcall btnLocalitateClick(TObject *Sender);
	void __fastcall btnZonaClick(TObject *Sender);
	void __fastcall txtLocalitateChange(TObject *Sender);
	void __fastcall txtDataExpirariiChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAp(TComponent* Owner);
	UnicodeString operatie;
	int 		  id;
	int 		  inchiriat;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAp *frmAp;
//---------------------------------------------------------------------------
#endif
