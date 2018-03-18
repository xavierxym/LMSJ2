
#include<stdio.h>
#include<WinSock2.h>
#include"sys/types.h"
#include"cocos2d.h"

typedef SOCKET sock;
typedef int scokLen;

#define badSock (INVALID_SOCKET)
#pragma comment(lib,"ws2_32.lib")

USING_NS_CC;

class SocketTool
{
public:

	static bool connectFlag;
	static int socketHandle;
	static int arr[];
	
	static bool connectServer(const char* ip, unsigned short port);
	 static void cleanSock();
	static  int createSocket();
	static void closeSocket();
	static void sendMessage(const char* s);
	static char* recvMessage();

	static void sendInt(int si);
	static char* receiveBytes(int len);
	static int receiveInt();

	//static void sendposition();
	static void * getposition();
};