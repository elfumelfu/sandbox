//$$---- EXE CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("clienti_apartamente.cpp", frmClientiAp);
USEFORM("apartamente.cpp", frmAp);
USEFORM("main.cpp", frmMain);
USEFORM("case.cpp", frmCase);
USEFORM("agentii.cpp", frmAgentii);
USEFORM("login.cpp", frmLogin);
USEFORM("imagine.cpp", frmImagine);
USEFORM("setari.cpp", frmSetari);
USEFORM("spatii.cpp", frmSpatii);
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
		Application->CreateForm(__classid(TfrmCase), &frmCase);
		Application->CreateForm(__classid(TfrmSpatii), &frmSpatii);
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
