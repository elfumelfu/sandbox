//$$---- EXE CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("login.cpp", frmLogin);
USEFORM("apartamente.cpp", frmAp);
USEFORM("main.cpp", frmMain);
//---------------------------------------------------------------------------
#include "login.h"
#include "main.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmLogin), &frmLogin);
		Application->CreateForm(__classid(TfrmAp), &frmAp);
		frmLogin->Hide();
		frmLogin->ShowModal();
        Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
