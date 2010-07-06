//---------------------------------------------------------------------------

#ifndef imagineH
#define imagineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmImagine : public TForm
{
__published:	// IDE-managed Components
	TImage *img;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmImagine(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImagine *frmImagine;
//---------------------------------------------------------------------------
#endif
