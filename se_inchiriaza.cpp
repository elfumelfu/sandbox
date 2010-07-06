//$$---- EXE CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("apartamente.cpp", frmAp);
USEFORM("login.cpp", frmLogin);
USEFORM("clienti_apartamente.cpp", frmClientiAp);
USEFORM("agentii.cpp", frmAgentii);
USEFORM("main.cpp", frmMain);
USEFORM("imagine.cpp", frmImagine);
USEFORM("setari.cpp", frmSetari);
//---------------------------------------------------------------------------
#include "login.h"
#include "main.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Se-inchiriaza.ro";
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmLogin), &frmLogin);
		Application->CreateForm(__classid(TfrmAp), &frmAp);
		Application->CreateForm(__classid(TfrmAgentii), &frmAgentii);
		Application->CreateForm(__classid(TfrmImagine), &frmImagine);
		Application->CreateForm(__classid(TfrmClientiAp), &frmClientiAp);
		Application->CreateForm(__classid(TfrmSetari), &frmSetari);
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
