#include"SocketTool.h"
#include"HelloWorldScene.h"

/**
	与服务器通信
*/
USING_NS_CC;

int SocketTool::arr[] = {0,0,0,0};
bool SocketTool::connectFlag = false;
int SocketTool::socketHandle = 0;

//初始化socket
void initSock() {

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return;
	}
}

//清理socket
void SocketTool::cleanSock()
{
	WSACleanup();
}

//端口连接
sockaddr_in sockAddr(int port) {
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	return addr;
}

//端口+ip连接
sockaddr_in sockAddr(int port, const char*ip) {

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	addr.sin_addr.S_un.S_addr = inet_addr(ip);

	return addr;
}

//创建socket
int SocketTool:: createSocket() {

	int err = 0;
	char buf[512];
	initSock();
	sock client = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr = sockAddr(9999, "127.0.0.1");
	err = connect(client, (sockaddr*)&addr, sizeof(addr));
	log("err= %d",err);
	sprintf(buf, "\n Hello World!");
	send(client, buf, strlen(buf) + 1, 0);
	int n = recv(client, buf, sizeof(buf), 0);
	log("client recv %d byte:%s \n", n, buf);
	closesocket(client);
	getchar();
	cleanSock();
	return 0;
}

//关闭socket
void  SocketTool::closeSocket() {
	if (connectFlag)
	{
		::closesocket(socketHandle);
		connectFlag = false;
	}
}

//发送整数
void SocketTool::sendInt(int si)
{
	log("send Int :%d", si);
	//memcpy();
	byte b[4];
	b[0] = (byte)(si);
	b[1] = (byte)(si >> 8);
	b[2] = (byte)(si >> 16);
	b[3] = (byte)(si >> 24);

	char str[4] = { b[0],b[1],b[2],b[3] };
	//sprintf(str, "%d", si);
	int k = send(socketHandle, str, 4, 0);//发送int类型                     //&si
	//log("send back:%d", k);
}

//接收字节
char* SocketTool::receiveBytes(int len)
{
	char* result = new char[len];

	int status = recv(socketHandle, result, len, 0);

	while (status != len)
	{
		int index = status;
		char *b = new char[len - status];                                                // 
		int count = recv(socketHandle, b, len - status, 0);
		status = status + count;
		if (count != 0)
		{
			for (int i = 0;i<count;i++)
			{
				result[index + i] = b[i];
			}
		}
	}
	return result;
}

//接收int类型
int SocketTool::receiveInt()
{
	char* a = receiveBytes(4);
	int ri=0;

	memset(&ri, 0, sizeof(ri));
	memcpy((char*)(&ri), a, 4);
	delete a;
	log("*****receiveint: %d\n", ri);
	return ri;
}

//获取其他玩家位置
void * SocketTool::getposition() {
	int num = 0;
	while(true)
	 { 
		if(connectFlag)
		{ 
		int code=receiveInt();
		
	   if (code == 100001) {
		   int xposition = receiveInt();
		   int yposition = receiveInt();
		   
		   if(arr[0]!=xposition|| arr[1]!= yposition)
		   {
			  arr[0] = xposition;
			  arr[1] = yposition;
			  HelloWorld::eney2RunFlag = 1;	
		   }
		  else {			
			  if (num == 3)
			  HelloWorld::eney2RunFlag = 0;
			  num++;
			  if (num >= 4)
						  num = 0;
		   }

	   }
	   else if (code == 100002) {
		   int xposition = receiveInt();
		   int yposition = receiveInt();
		   arr[2] = xposition;
		   arr[3] = yposition;
	   }
   log("------------>Arr=(%d,%d),(%d,%d)\n", arr[0], arr[1], arr[2], arr[3]);
		}
	 }
	   return nullptr;
}

//fasong
void SocketTool::sendMessage(const char* s)
{
	int k = send(socketHandle, s, strlen(s)+1, 0);//发送int类型                     //&si
	log("send back:%d", k);
}

//接受
char* SocketTool::recvMessage()
{
	char  buf[256];
	int n = recv(socketHandle, buf, sizeof(buf), 0);
	log("client recv %d byte:%s \n", n, buf);
	return buf;
}

//ip+端口 连接socket
bool SocketTool::connectServer(const char* ip, unsigned short port) {
		struct sockaddr_in sa;
		struct hostent* hp;
		hp = gethostbyname(ip);//用域名或主机名获取IP地址
		log("*********** ip is : %s ", ip);

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.S_un.S_addr = inet_addr(ip);

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		log("********err init socket !");
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		log("********err2  init socket !");
	}

  socketHandle = socket(AF_INET, SOCK_STREAM, 0);

	if (socketHandle == INVALID_SOCKET)
	{
		log("******** socket connect is error!!!!");
		return 0;
	}
	log("********before test connect ");
	if (::connect(socketHandle, (sockaddr*)&sa, sizeof(sa)) < 0)
	{
		log("******* socket connect is error2!!!!");
		::closesocket(socketHandle);
		return 0;
	}
	log("lianjie chen gong");
	//msgLabel->setString("jin ru you xi");
	connectFlag = true;
	new std::thread(&SocketTool::getposition);
}

