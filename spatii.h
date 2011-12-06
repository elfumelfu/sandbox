//---------------------------------------------------------------------------

#ifndef spatiiH
#define spatiiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ButtonWithColor.hpp"
#include "JvCheckListBox.hpp"
#include "JvExCheckLst.hpp"
#include <CheckLst.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmSpatii : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label7;
	TLabel *Label8;
	TImage *imgFaraPoza;
	TRadioGroup *rgMobilat;
	TButton *btnSalveaza;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label4;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabeledEdit *txtGs;
	TLabeledEdit *txtPret;
	TMemo *memAltele;
	TComboBox *cbMoneda;
	TComboBox *txtZona;
	TComboBox *txtJudet;
	TComboBox *txtLocalitate;
	TButton *btnLocalitate;
	TButton *btnZona;
	TGroupBox *GroupBox2;
	TJvCheckListBox *clbImbunatatiri;
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
	TLabeledEdit *LabeledEdit1;
	TComboBox *cbMonedaMp;
	TLabel *Label2;
	TLabeledEdit *txtAp;
	TLabeledEdit *txtBloc;
	TLabeledEdit *LabeledEdit2;
	TCheckBox *ckbVitrina;
	TEdit *txtVitrina;
	TLabeledEdit *LabeledEdit3;
	TLabeledEdit *LabeledEdit4;
	TLabeledEdit *LabeledEdit5;
	TGroupBox *GroupBox4;
	TJvCheckListBox *clbLocalizare;
	TGroupBox *GroupBox5;
	TJvCheckListBox *clbTip;
	TCheckBox *ckbCompartimentat;
	void __fastcall ckbVitrinaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSpatii(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSpatii *frmSpatii;
//---------------------------------------------------------------------------
#endif
