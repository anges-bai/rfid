1.2.1、运行代码-----ISO/IEC 14443A：
#include "stdafx.h"
#include "REX2_API.h"
#pragma comment(lib, "REX2_API.lib")
int _tmain(int argc, _TCHAR* argv[])
{
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");

	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	//
	int nResult = REX2_RegisterISO14443A(&readerObj);

	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO14443A Success.\r\n"));
	}
	else
	{
		_tprintf(_T("Register ISO 14443A Failed. Error Code : %X\r\n"), nResult);
	}

	//
	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
1.2.2、运行代码-----02_ISO14443A_REQA.
#include "stdafx.h"
#include "REX2_API.h"
#pragma comment(lib, REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	REX2Reader readerObj;
	int nResult;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO14443A(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO 14443A Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}
	
	BYTE atqa[2];
	nResult = REX2_ISO14443A_REQA(&readerObj, atqa);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A REQA Success. ATQA = %02X%02X\r\n"), atqa[0], atqa[1]);
	}
	else
	{
		_tprintf(_T("ISO14443A REQA Failed!! Error Code : %X\r\n"), nResult);
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
1.2.3、运行代码------03_ISO14443A_Cascade
#include "stdafx.h"

#include "REX2_API.h"

#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	REX2Reader readerObj;
	int nResult;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO14443A(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO 14443A Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}
	
	BYTE atqa[2];
	nResult = REX2_ISO14443A_REQA(&readerObj, atqa);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A REQA Success. ATQA = %02X%02X\r\n"), atqa[0], atqa[1]);
	}
	else
	{
		_tprintf(_T("ISO14443A REQA Failed!! Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	BYTE cascadeLevel = 1; // level
	BYTE bcc, sak;
	REX2UID uid;
	nResult = REX2_ISO14443A_Cascade(&readerObj, cascadeLevel, &uid, &bcc, &sak);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A Cascade Level %d Failed. Error Code: %X\r\n"), cascadeLevel, nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	_tprintf(_T("ISO14443A Cascade Level %d Success. UID="), cascadeLevel);
	for(BYTE i=0; i<uid.length; i++)
	{
		_tprintf(_T(" %02X"), uid.data[i]);
	}
	_tprintf(_T(", BCC=%02X, SAK=%02X\r\n"), bcc, sak);

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
1.2.4、运行代码------04_ISO14443A_HLTA.
#include "stdafx.h"
#include "REX2_API.h"
#pragma comment(lib, ".REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	REX2Reader readerObj;
	int nResult;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO14443A(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO 14443A Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}
		
	BYTE atqa[2];
	nResult = REX2_ISO14443A_REQA(&readerObj, atqa);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A REQA Success. ATQA = %02X%02X\r\n"), atqa[0], atqa[1]);
	}
	else
	{
		_tprintf(_T("ISO14443A REQA Failed!! Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	BYTE cascadeLevel = 1; // level
	BYTE bcc, sak;
	REX2UID uid;
	nResult = REX2_ISO14443A_Cascade(&readerObj, cascadeLevel, &uid, &bcc, &sak);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A Cascade Level %d Failed. Error Code: %X\r\n"), cascadeLevel, nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	_tprintf(_T("ISO14443A Cascade Level %d Success. UID="), cascadeLevel);
	for(BYTE i=0; i<uid.length; i++)
	{
		_tprintf(_T(" %02X"), uid.data[i]);
	}
	_tprintf(_T(", BCC=%02X, SAK=%02X\r\n"), bcc, sak);


	nResult = REX2_ISO14443A_HLTA(&readerObj);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A HLTA Success.\r\n"));
	}
	else
	{
		_tprintf(_T("ISO14443A HLTA Failed!!\r\n"), nResult);
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
1.2.5、运行代码------05_ISO14443A_WUPA
#include "stdafx.h"

#include REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	REX2Reader readerObj;
	int nResult;

	TCHAR szPort[] = _T("COM4”);

	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO14443A(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO 14443A Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}
	
	BYTE atqa[2];
	nResult = REX2_ISO14443A_WUPA(&readerObj, atqa);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO14443A WUPA Success. ATQA = %02X%02X\r\n"), atqa[0], atqa[1]);
	}
	else
	{
		_tprintf(_T("ISO14443A WUPA Failed!!\r\n"), nResult);
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
1.2.6、运行代码------06_ISO14443A_UID
#include "stdafx.h"
#include "REX2_API.h"
#pragma comment(lib, ".REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	REX2Reader readerObj;
	int nResult;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	BYTE uidCnt;
	REX2UID uids[10];
	nResult = REX2_ISO14443A_UID(&readerObj, uids, &uidCnt);
	if(nResult!=REX2_ERROR_OK) {
		_tprintf(_T("ISO14443A UID Failed!! Error Code : %02X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}
	_tprintf(_T("ISO14443A UID Success.\r\n"));

	for(BYTE i=0; i<uidCnt; i++)
	{
		_tprintf(_T("UID %d = "), i+1);
		for(BYTE j=0; j<uids[i].length; j++)
		{
			_tprintf(_T("%02X "), uids[i].data[j]);
		}
		_tprintf(_T("\r\n"));
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
