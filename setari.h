//---------------------------------------------------------------------------

#ifndef setariH
#define setariH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <AppEvnts.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TfrmSetari : public TForm
{
__published:	// IDE-managed Components
	TPanel *panStanga;
	TPanel *panContinut;
	TTreeView *TreeView1;
	TImage *imgSigla;
	TGroupBox *GroupBox1;
	TLabeledEdit *txtEuro;
	TLabeledEdit *txtUsd;
	TGroupBox *GroupBox2;
	TLabeledEdit *txtMarja;
	TComboBox *txtMoneda;
	TLabel *Label4;
	TGroupBox *GroupBox3;
	TComboBox *txtLocalitate;
	TLabel *Label11;
	TComboBox *txtJudet;
	TLabel *Label10;
	TButton *btnLocalitate;
	TPanel *panDreapta;
	TPanel *panButoane;
	TButton *btnSalveaza;
	TUpdateSQL *insertQuery;
	void __fastcall imgSiglaClick(TObject *Sender);
	void __fastcall txtEuroKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall txtJudetChange(TObject *Sender);
	void __fastcall btnLocalitateClick(TObject *Sender);
	void __fastcall btnSalveazaClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmSetari(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetari *frmSetari;
//---------------------------------------------------------------------------
#endif
