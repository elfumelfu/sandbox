//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tools.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

UnicodeString tabelaOpusa(UnicodeString Tabela)
{
	if (Tabela.Pos("clienti_") == 0)
		return "clienti_"+Tabela;
	else
		{
		int pos = Tabela.Pos("_");
		return Tabela.SubString(pos+1, Tabela.Length()-pos);
		}
}
