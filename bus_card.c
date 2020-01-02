#include "stdafx.h"
#include "RFIDRW.cpp"
int _tmain(int argc,_TCHAR * argv[])
{
	RFIDRW * RW = new RFIDRW();
	RW->Connect();
	while (1)
		if (RW->Write() == 0)
			break;
    return 0;
}

#include "stdafx.h"
#include "REX2_API.h"
#pragma comment(lib,"REX2_API.lib")  //链接库信息

class RFIDRW {
private:
	REX2Reader readerObj;
	int nResult;
	REX2UID uid;//存储要读取的标签的UID的变量
	BYTE byAddr;
	BYTE data;//将要读出数据的地址byAddr和要存储读出的数据的BYTE数组data作为
			  //因子下达 Read Single Block命令
	int checkW,checkM=1;
	BYTE count;
public:
	RFIDRW() {
		this->byAddr = 1;
		this->nResult = 1;
		this->checkW = 1;
		count = 0x00;
	}
	void Connect() {
		TCHAR szPort[] = _T("\\\\.\\COM7"); //连接的端口号;

		if (REX2_Open(&readerObj, szPort, 9600) == TRUE) //使用对象 readerObj 试图以9600bps连接到阅读器 判断是否连接了阅读器
		{
			_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Success.\r\n"));
		}
		else
		{
			_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
		}

		if (REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);	//确认阅读器的连接状态 如果是连接状态 就关闭连接

	}

	void REX2_Register_14443A() {

		TCHAR szPort[] = _T("\\\\.\\COM7"); //连接的端口号;

		if (REX2_Open(&readerObj, szPort, 9600) == FALSE) //判断是否连接成功 若否 则输出 以及停止程序运行
		{
			_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
			return;
		}

		//连接到对象 readerObj 的阅读器存储器设定为 ISO14443A 模式.
		nResult = REX2_RegisterISO14443A(&readerObj);

		if (nResult == REX2_ERROR_OK) //REX2_ERROR_OK：#define REX2_ERROR_OK 0x0000
		{
			_tprintf(_T("Register ISO14443A Success.\r\n"));
		}
		else
		{
			_tprintf(_T("Register ISO 14443A Failed. Error Code : %X\r\n"), nResult);
		}

		//同上 判断是否连接
		if (REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
	}

	int Write() {

		TCHAR szPort[] = _T("\\\\.\\COM7");

		if (REX2_Open(&readerObj, szPort, 9600) == FALSE)
		{
			_tprintf(_T("HBE-RFID-REX2 13.56Mhz Reader Open Failed.\r\n"));
			return 1;
		}

		nResult = REX2_RegisterISO14443A(&readerObj);
		if (nResult != REX2_ERROR_OK)
		{
			_tprintf(_T("RegisterISO14443A Failed.Error Code:%X\r\n"), nResult);
			if (REX2_IsOpen(&readerObj))REX2_Close(&readerObj);
			return 1;
		}

		BYTE atqa[2];
		nResult = REX2_ISO14443A_REQA(&readerObj, atqa);
		if (nResult == REX2_ERROR_OK)
		{
			//_tprintf(_T("ISO14443A REQA Success.ATQA = %02X%02X\r\n"), atqa[0], atqa[1]);
			if (checkW) {
				data = 0x64;
				byAddr = 1;
				nResult = REX2_RegisterWrite(&readerObj, byAddr, data);
				checkW = 0;      
				data = 0x00;
				byAddr = 2;
			}
			else {
				printf("%d,%x\n", checkW, data);
				data += 0x01;
			}


			nResult = REX2_RegisterWrite(&readerObj, byAddr, data);

			if (nResult != REX2_ERROR_OK)
			{
				_tprintf(_T("ISO14443A Write Failed!! Error Code : %02X\r\n"), nResult);
				if (REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
				return 1;
			}

			BYTE readData[1];
			byAddr = 2;
			nResult = REX2_RegisterRead(&readerObj, byAddr, readData);

			if (nResult != REX2_ERROR_OK)
			{
				//_tprintf(_T("ISO14443A Read  Failed!! Error Code : %02X\r\n"), nResult);
				if (REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
				return 1;
			}

			//将二进制转int
			int mask = 0xff;
			int temp = 0;
			int n = 0;
			n <<= 8;
			temp = readData[0] & mask;
			n |= temp;
			float  LeftMoney = 100.00 - n * 1;
			if (LeftMoney <= 2) {
				printf("余额即将不足，请充值\n");
				checkM = 0;
			}
			printf("ISO14443A Read  Success. Block %d's money = %.2f\n", byAddr, LeftMoney);

			if (REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);
		}
		else
		{
			//_tprintf(_T("ISO1443A  REQA Failed.Error Code:%X\r\n"), nResult);
			if (REX2_IsOpen(&readerObj)) REX2_Close(&readerObj);			
			return 1;
		}

		return checkM;
	}
}
