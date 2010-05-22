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
//---------------------------------------------------------------------------
class TfrmAp : public TForm
{
__published:	// IDE-managed Components
	TButton *btnSalveaza;
	TGroupBox *GroupBox1;
	TLabeledEdit *txtNrcam;
	TLabeledEdit *txtZona;
	TLabeledEdit *txtBloc;
	TLabeledEdit *txtAp;
	TLabeledEdit *txtEtaj;
	TLabeledEdit *txtDsc;
	TLabeledEdit *txtGs;
	TLabeledEdit *txtMoneda;
	TLabeledEdit *txtPret;
	TGroupBox *GroupBox2;
	TCheckListBox *CheckListBox1;
	TRadioGroup *RadioGroup1;
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
	void __fastcall btnSalveazaClick(TObject *Sender);
	void __fastcall btnStergeTotClick(TObject *Sender);
	void __fastcall btnRenuntaClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAp(TComponent* Owner);
	UnicodeString operatie;
	int 		  id;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAp *frmAp;
//---------------------------------------------------------------------------
#endif
