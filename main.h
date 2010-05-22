//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Iesier1;
	TDatabase *Database;
	TStatusBar *StatusBar;
	TMenuItem *Apartamente1;
	TMenuItem *Adauga1;
	TMenuItem *Vizualizeaza1;
	TTreeView *TreeView1;
	TDataSource *DataSource1;
	TQuery *Query1;
	TDBGrid *DBGrid1;
	TQuery *sqlSelect;
	void __fastcall DatabaseAfterConnect(TObject *Sender);
	void __fastcall Iesier1Click(TObject *Sender);
	void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
	void __fastcall Adauga1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
