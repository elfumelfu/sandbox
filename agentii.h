//---------------------------------------------------------------------------

#ifndef agentiiH
#define agentiiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TfrmAgentii : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *txtNume;
	TLabeledEdit *txtTelefon;
	TButton *btnSalveaza;
	TButton *btnStergeTot;
	TButton *btnRenunta;
	TUpdateSQL *SQL;
	void __fastcall btnStergeTotClick(TObject *Sender);
	void __fastcall btnRenuntaClick(TObject *Sender);
	void __fastcall btnSalveazaClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAgentii(TComponent* Owner);

	UnicodeString operatie;
	int 		  id;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAgentii *frmAgentii;
//---------------------------------------------------------------------------
#endif
