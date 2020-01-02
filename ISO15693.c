2.2.1、运行代码------ 01_ISO15693_RegisterISO15693
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

	int nResult = REX2_RegisterISO15693(&readerObj);

	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Success.\r\n"));
	}
	else
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
2.2.2、运行代码------02_ISO15693_Inventory

#include "stdafx.h"

#include "REX2_API.h" 

#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO15693(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	REX2UID uid;
	nResult = REX2_ISO15693_Inventory(&readerObj, &uid);
	if(nResult!=REX2_ERROR_OK) {
		_tprintf(_T("ISO15693 Inventory Failed!! Error Code : %02X\r\n"), nResult);
		return 0;
	}

	_tprintf(_T("ISO15693 Inventory Success. UID="));
	for(BYTE i=0; i<uid.length; i++)
	{
		_tprintf(_T(" %02X"), uid.data[i]);
	}
	_tprintf(_T("\r\n"));

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
2.2.3、运行代码------03_ISO15693_ReadSingleBlock

#include "stdafx.h"

#include "REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO15693(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	BYTE byAddr = 1; // block 
	BYTE data[4];
	nResult = REX2_ISO15693_ReadSingleBlock(&readerObj, byAddr, data);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("ISO15693 Read Single Block Failed!! Error Code : %02X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	_tprintf(_T("ISO15693 Read Single Block Success. Block %d's data ="), byAddr);
	for(BYTE i=0; i<4; i++)
	{
		_tprintf(_T(" %02X"), data[i]);
	}
	_tprintf(_T("\r\n"));

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}

2.2.4、运行代码------ 04_ISO15693_WriteSingleBlock
#include "stdafx.h"

#include "REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO15693(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	BYTE byAddr = 1; // block 
	BYTE writeData[] = {0xAA,0xBB,0xCC,0xDD};

	nResult = REX2_ISO15693_WriteSingleBlock(&readerObj, byAddr, writeData);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("ISO15693 Write Single Block Failed!! Error Code : %02X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	BYTE readData[4];
	nResult = REX2_ISO15693_ReadSingleBlock(&readerObj, byAddr, readData);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("ISO15693 Read Single Block Failed!! Error Code : %02X\r\n"), nResult);
		return 0;
	}

	_tprintf(_T("ISO15693 Read Single Block Success. Block %d's data ="), byAddr);
	for(BYTE i=0; i<4; i++)
	{
		_tprintf(_T(" %02X"), readData[i]);
	}
	_tprintf(_T("\r\n"));

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}
 2.2.5、运行代码------05_ISO15693_ReadMultipleBlocks 
#include "stdafx.h"

#include REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO15693(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	BYTE data[16]; // 4(per block) * 4(blocks)
	BYTE byAddr = 0;
	BYTE byNumOfBlock = 4;

	nResult = REX2_ISO15693_ReadMultiBlock(&readerObj, byAddr, byNumOfBlock, data);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("ISO15693 Read Multiple Blocks Failed!! Error Code : %02X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	_tprintf(_T("ISO15693 Read Multiple Blocks Success. %d to %d block's data ="), byAddr, byNumOfBlock);
	for(BYTE i=0; i<(4*byNumOfBlock); i++)
	{
		_tprintf(_T(" %02X"), data[i]);
	}
	_tprintf(_T("\r\n"));

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}

2.2.6、运行代码------06_ISO15693_StayQuiet

#include "stdafx.h"

#include "REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO15693(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	REX2UID uid;
	nResult = REX2_ISO15693_Inventory(&readerObj, &uid);
	if(nResult!=REX2_ERROR_OK) {
		_tprintf(_T("ISO15693 Inventory Failed!! Error Code : %02X\r\n"), nResult);
		return 0;
	}

	_tprintf(_T("ISO15693 Inventory Success. UID="));
	for(BYTE i=0; i<uid.length; i++)
	{
		_tprintf(_T(" %02X"), uid.data[i]);
	}
	_tprintf(_T("\r\n"));

	nResult = REX2_ISO15693_StayQuiet(&readerObj);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO15693 Stay Quiet Success.\r\n"));
	}
	else
	{
		_tprintf(_T("ISO15693 Stay Quiet Failed!! Error Code : %02X\r\n"), nResult);
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}

2.2.7、运行代码------07_ISO15693_ResetToReady

#include "stdafx.h"

#include "REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4");
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	nResult = REX2_RegisterISO15693(&readerObj);
	if(nResult!=REX2_ERROR_OK)
	{
		_tprintf(_T("Register ISO15693 Failed. Error Code : %X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	nResult = REX2_ISO15693_ResetToReady(&readerObj);
	if(nResult==REX2_ERROR_OK)
	{
		_tprintf(_T("ISO15693 Reset To Ready Success.\r\n"));
	}
	else
	{
		_tprintf(_T("ISO15693 Reset To Ready Failed!! Error Code : %02X\r\n"), nResult);
	}

	if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);

	return 0;
}

2.2.8、运行代码------08_ISO15693_UID
#include "stdafx.h"

#include "REX2_API.h"
#pragma comment(lib, "REX2_API.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	REX2Reader readerObj;

	TCHAR szPort[] = _T("COM4”);
	if(REX2_Open(&readerObj, szPort, 9600)==FALSE)
	{
		_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		return 0;
	}

	BYTE uidCnt;
	REX2UID uids[10];
	nResult = REX2_ISO15693_UID(&readerObj, uids, &uidCnt);
	if(nResult!=REX2_ERROR_OK) {
		_tprintf(_T("ISO15693 UID Failed!! Error Code : %02X\r\n"), nResult);
		if(REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		return 0;
	}

	_tprintf(_T("ISO15693 UID Success.\r\n"));
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
