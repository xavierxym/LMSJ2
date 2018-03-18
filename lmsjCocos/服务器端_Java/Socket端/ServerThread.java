package zhuwai;

import java.net.*;
import java.util.*;

//import zhuwai.GameData;
/**
 * 服务器类负责全体客户端连接、分配
 * @author xavier
 *
 */
public class ServerThread extends Thread
{
	boolean flag=true;
	Map<String,ServerAgentThread> cmap=new HashMap<String,ServerAgentThread>();	
	ServerSocket ss;
	int Cnum=0;
	public void run()
	{
		try{
			ss=new ServerSocket(9999);
			System.out.println("Server Listening on 9999...");
		}catch(Exception e){
			e.printStackTrace();
		}
		while(flag){
					try{
						Socket sc=ss.accept();
						String address=sc.getInetAddress().toString().trim();//获取IP地址
						ServerAgentThread sat=new ServerAgentThread(sc,this,Cnum,address+Cnum);
						sat.start();							
						System.out.println(address+Cnum+"   connect...");
						cmap.put(address+Cnum,sat);									
						GameData.clientList.put(Cnum,address+Cnum);		//添加IP地址到列表中
						for(int m=0;m<cmap.size();m++)
							System.out.println("There are  client:"+GameData.clientList.get(m));
						//	sat.broadcastConnect();					//发送已经连接
						Cnum++;
					}
					catch(Exception e){
						e.printStackTrace();
					}
		}
	}
	
	public static void main(String args[]){
		new ServerThread().start();
}}