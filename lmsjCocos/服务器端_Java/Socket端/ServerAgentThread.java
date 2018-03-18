package zhuwai;

import static zhuwai.IOUtil.readInt;
import static zhuwai.IOUtil.readStr;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.ArrayList;

import zhuwai.GameData;
import zhuwai.ServerThread;
import zhuwai.CodeChange;
import zhuwai.IOUtil;

/**
 * 代理线程类，负责每个玩家客户端的通信
 * @author xavier
 *
 */

public class ServerAgentThread extends Thread
{
	boolean flag=true;
	Socket sc;
	DataInputStream din;		
	DataOutputStream dout;
	ServerThread st;
	String name;
	int Cnum;
	int whoIsU;
	int timeout=1000;
	
	String receiveContent;			//服务器收到的内容
	
	public ServerAgentThread(Socket sc,ServerThread st,int Cnum,String name) throws Exception  //收	
	{
		this.sc=sc;
		this.st=st;	
		this.Cnum=Cnum;
		this.name=name;
		din=new DataInputStream(sc.getInputStream());
		dout=new DataOutputStream(sc.getOutputStream());
	}

	public void run()
	{
		
		
		while(flag)
		{
			try
			{
				
				//每一轮先接收标志位整数 
				int code=readInt(din);
				System.out.println("\n receive state code :"+code);
				
				if(code==666)									
				{   
					whoIsU=0;
					if(GameData.gamming.size()<=2){
						GameData.gamming.add(Cnum);
					}
					System.out.println("\n ---------------->code=666 :");
					GameData.peoplePrepareState.put(Cnum,name);
					System.out.println("-------->AddressIndex=:"+Cnum);					
				}
				
				if(code==667)									
				{   
					whoIsU=1;
					if(GameData.gamming.size()<=2){
						GameData.gamming.add(Cnum);
					}
					System.out.println("\n ------>code=667 :");
				
					GameData.peoplePrepareState.put(Cnum,name);
					System.out.println("-------->AddressIndex=:"+Cnum);
					
				}
				
			/*	if(GameData.peoplePrepareState.size()>=1&&GameData.tufuPrepareState.size()>=1){
					IOUtil.sendInt(dout,200001);
					System.out.println("----------->waitting...send,200001");
					
					if(whoIsU==1){
						GameData.tufuPrepareState.remove(Cnum);
					}else{
						GameData.peoplePrepareState.remove(Cnum);
					}
				}
			*/
				
				if(code==10000){
					GameData.position.put(GameData.clientList.get(Cnum)+"x", readInt(din));
					GameData.position.put(GameData.clientList.get(Cnum)+"y", readInt(din));
					
					System.out.println("read "+name+"positionx : "+GameData.position.get(GameData.clientList.get(Cnum)+"x"));
					System.out.println("read "+name+"positiony : "+GameData.position.get(GameData.clientList.get(Cnum)+"y"));
					System.out.println("-------->gammingsize:"+GameData.gamming.size());				
				}
				System.out.println("GameData.position.size:"+GameData.position.size());
				
				if(GameData.gamming.size()>=2)
				{
					System.out.println("GameData.clientList.size:"+GameData.clientList.size());
					for(int i=0;i<GameData.gamming.size();i++)
					{
						//String address=sc.getInetAddress().toString().trim();
						if(GameData.gamming.get(i)!=Cnum)
						{
							System.out.println("send getAddressIndex() :"+i);
							IOUtil.sendInt(dout,100001);
							IOUtil.sendInt(dout,GameData.position.get(GameData.clientList.get(i)+"x"));
							IOUtil.sendInt(dout,GameData.position.get(GameData.clientList.get(i)+"y"));
						}
						}
				}
				
			//	IOUtil.sendInt(dout,777);
				//IOUtil.sendStr(dout,"1");
				
				sc.setSoTimeout(timeout);//1000seconds 
			  
					
			}
			catch(java.net.SocketTimeoutException   ie){   
				ie.printStackTrace();
				System.out.println("----------------->timeout");
				GameData.gameState=0;  
				  break;    
				  } 
			
			catch(java.net.SocketException se){
				System.out.println("----------------->timeout");
				GameData.gameState=0;  
				break; 
				
			}
			catch(Exception e)
			{
				e.printStackTrace();
				GameData.gameState=0;  
				System.out.println("----------------->exception");
				break;
			}
			
		}		
		
		
	//	cmap.put(address+Cnum,sat);	
		GameData.gameState=0;  
		GameData.position.remove(GameData.clientList.get(Cnum)+"x");
		GameData.position.remove(GameData.clientList.get(Cnum)+"y");
		GameData.peoplePrepareState.remove(Cnum);
		GameData.tufuPrepareState.remove(Cnum);
		GameData.gamming.remove(Cnum);
		GameData.clientList.remove(Cnum);		//添加IP地址到列表中	
	}
	
	private void dataReset()
	{

		GameData.prepareCount=0;
		GameData.peoplePrepareState.clear();
		GameData.tufuPrepareState.clear();
		GameData.num=0;

	}
	private int getAddressIndex() 						//获取地址的索引
	{
		String address=sc.getInetAddress().toString().trim();
		
		for(int i=0;i<GameData.clientList.size();i++)
		{
			for(int j=0;j<GameData.clientList.size();j++)
			{				
				if(GameData.clientList.get(i).equals(address+j))
				{
					return j;
				}
			}
		}
		return 0;
	}
	
}
