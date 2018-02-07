#include <iostream>
#include <windows.h> 
#include <wininet.h>
#include <string>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {

	DWORD lpdwFlags = 0;
	TCHAR   lpszConnectionName[512];
	/*
		INTERNET_CONNECTION_CONFIGURED 0x40 Local system has a valid connection to the Internet, but it might or might not be currently connected.
		INTERNET_CONNECTION_LAN		   0x02 Local system uses a local area network to connect to the Internet.
		INTERNET_CONNECTION_MODEM	   0x01 Local system uses a modem to connect to the Internet.
		INTERNET_CONNECTION_OFFLINE    0x20 Local system is in offline mode.
		INTERNET_CONNECTION_PROXY      0x04 Local system uses a proxy server to connect to the Internet.

		INTERNET_CONNECTION_MODEM_BUSY 0x08 No longer used.
	*/

	int  input = 0;

	while (true)
	{
		bool connectedStatEx = (InternetGetConnectedStateEx(&lpdwFlags, lpszConnectionName, _countof(lpszConnectionName), NULL) ? true : false);

		std::string conName = "<empty>";
		int size = _countof(lpszConnectionName);
		if (size > 0) conName = "";
		for (int s = 0; s <= size; ++s)
		{
			conName += static_cast<char>(lpszConnectionName[s]);
		}

		printf("InternetGetConnectedStateEx                  : %s\n", connectedStatEx ? "True" : "false");
		printf("InternetGetConnectedStateEx Flag(HEX)        : %02x\n", lpdwFlags);
		printf("InternetGetConnectedStateEx ConName          : %s\n\n", conName.c_str());

		switch (lpdwFlags)
		{
		case INTERNET_CONNECTION_LAN: 		 std::cout << "InterGetConStateEx Flag : LAN\n";  break;
		case INTERNET_CONNECTION_MODEM:		 std::cout << "InterGetConStateEx Flag : Modem\n";  break;
		case INTERNET_CONNECTION_CONFIGURED:	std::cout << "InterGetConStateEx Flag : Configured\n";  break;
		case INTERNET_CONNECTION_OFFLINE: 		std::cout << "InterGetConStateEx Flag : Offline\n";  break;
		case INTERNET_CONNECTION_PROXY: 		std::cout << "InterGetConStateEx Flag : Proxy\n";  break;
		case (INTERNET_RAS_INSTALLED): 		std::cout << "InterGetConStateEx : RAS\n";  break;
		case (INTERNET_CONNECTION_LAN | INTERNET_RAS_INSTALLED): 		std::cout << "InterGetConStateEx : LAN/RAS\n";  break;
		case (INTERNET_CONNECTION_MODEM | INTERNET_RAS_INSTALLED): 		std::cout << "InterGetConStateEx : Modem/RAS\n";  break;
		default:
			std::cout << "InternetGetConnectedStateEx : UNKNOWN\n";  break;
			break;
		}

		bool connected = (InternetCheckConnection(L"http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0) ? true : false);
		if (connected)
		{
			std::cout << "\nconnected to internet\n";
		}
		else
		{
			std::cout << "\nNot Connected\n";
		}

		DWORD connDesc = 0;
		bool blnResult = false;

		blnResult = InternetGetConnectedState(&connDesc, 0) ? true : false;
		printf("InternetGetConnectedState                  : %s\n", blnResult ? "True" : "false");
		printf("InternetGetConnectedState Flag(HEX)        : %02x\n", connDesc);

		switch (lpdwFlags)
		{
		case INTERNET_CONNECTION_LAN: 		 std::cout << "InternetGetConnectedState Flag : LAN\n";  break;
		case INTERNET_CONNECTION_MODEM:		 std::cout << "InternetGetConnectedState Flag : Modem\n";  break;
		case INTERNET_CONNECTION_CONFIGURED:	std::cout << "InternetGetConnectedState Flag : Configured\n";  break;
		case INTERNET_CONNECTION_OFFLINE: 		std::cout << "InternetGetConnectedState Flag : Offline\n";  break;
		case INTERNET_CONNECTION_PROXY: 		std::cout << "InternetGetConnectedState Flag : Proxy\n";  break;
		case (INTERNET_RAS_INSTALLED): 		std::cout << "InternetGetConnectedState : RAS\n";  break;
		case (INTERNET_CONNECTION_LAN | INTERNET_RAS_INSTALLED): 		std::cout << "InternetGetConnectedState : LAN/RAS\n";  break;
		case (INTERNET_CONNECTION_MODEM | INTERNET_RAS_INSTALLED): 		std::cout << "InternetGetConnectedState : Modem/RAS\n";  break;
		default:
			std::cout << "InternetGetConnectedState : UNKNOWN\n";  break;
			break;
		}

		std::cin >> input;
		if (input == 1) break;
	}

	return 0;
}