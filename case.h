//---------------------------------------------------------------------------

#ifndef caseH
#define caseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ButtonWithColor.hpp"
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
#include "JvCheckListBox.hpp"
#include "JvExCheckLst.hpp"
//---------------------------------------------------------------------------
class TfrmCase : public TForm
{
__published:	// IDE-managed Components
	TImage *imgPoza1;
	TImage *imgPoza2;
	TImage *imgPoza3;
	TImage *imgPoza4;
	TLabel *Label7;
	TLabel *Label8;
	TImage *imgFaraPoza;
	TRadioGroup *rgMobilat;
	TButton *btnSalveaza;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabeledEdit *txtStrada;
	TLabeledEdit *txtGs;
	TLabeledEdit *txtPret;
	TMemo *memAltele;
	TComboBox *txtMoneda;
	TComboBox *txtNrcam;
	TComboBox *txtZona;
	TComboBox *txtJudet;
	TComboBox *txtLocalitate;
	TButton *btnLocalitate;
	TButton *btnZona;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabeledEdit *txtNume;
	TMemo *memInfo;
	TLabeledEdit *txtTel;
	TButton *btnStergeTot;
	TButton *btnRenunta;
	TRadioGroup *rgUtilat;
	TBitBtnWithColor *btnInchiriat;
	TUpdateSQL *SQL;
	TOpenPictureDialog *OpenPictureDialog1;
	TQuery *getID;
	TUpdateSQL *insertQuery;
	TLabeledEdit *txtSpTeren;
	TLabeledEdit *txtSpConstruita;
	TLabel *Label2;
	TDateTimePicker *txtDataExpirarii;
	TJvCheckListBox *CheckListBox1;
	void __fastcall btnStergeTotClick(TObject *Sender);
	void __fastcall btnRenuntaClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnInchiriatClick(TObject *Sender);
	void __fastcall txtGsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall txtJudetChange(TObject *Sender);
	void __fastcall txtLocalitateChange(TObject *Sender);
	void __fastcall btnLocalitateClick(TObject *Sender);
	void __fastcall btnZonaClick(TObject *Sender);
	void __fastcall btnSalveazaClick(TObject *Sender);
	void __fastcall txtSpTerenKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCase(TComponent* Owner);
	UnicodeString operatie;
	int 		  id;
	int 		  inchiriat;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCase *frmCase;
//---------------------------------------------------------------------------
#endif
