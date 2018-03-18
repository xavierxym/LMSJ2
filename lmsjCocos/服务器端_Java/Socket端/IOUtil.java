package zhuwai;
import java.io.*;

/**
 * I工具类
 * @author xavier
 *
 */

public class IOUtil 
{
	public static void sendFloat(DataOutputStream dout,float a) throws Exception
	{
		byte[] buf=ConvertUtil.fromFloatToBytes(a);
		dout.write(buf);		//类型
		dout.flush();			//发送数据
	}
	
	public static void sendInt(DataOutputStream dout,int a) throws Exception
	{
		System.out.println("send Int num  :"+a);
		byte[] buf=ConvertUtil.fromIntToBytes(a);
		dout.write(buf);
		dout.flush();
	}
	
	public static void sendStr(DataOutputStream dout,String str) throws Exception
	{
		System.out.println("send Str num  :"+str);
		byte[] buf=ConvertUtil.fromStringToBytes(str);
		sendInt(dout,buf.length); 	//长度
		dout.write(buf);			//类型
		dout.flush();				//发送数据
	}	
	
	//把收到的数据转换成int,float,string
	
	public static int readInt(DataInputStream din) throws Exception				//收到的的整数
	{
		byte[] buf=new byte[4];
		for(int i=0;i<4;i++)
		{
			buf[i]=1;
		}
		int count=0;
		while(count<4)
		{
			int tc=din.read(buf);
			count=count+tc;
		}	
		
		return ConvertUtil.fromBytesToInt(buf);
	}
	
	public static float readFloat(DataInputStream din) throws Exception			//收到的浮点数
	{
		byte[] buf=new byte[4];
		int count=0;
		while(count<4)
		{
			int tc=din.read(buf);
			count=count+tc;
		}		
		return ConvertUtil.fromBytesToFloat(buf);
	}
	
	public static String readStr(DataInputStream din) throws Exception			//收到的字符串
	{
		//接收字符串长度
		int len=readInt(din);	
		byte[] buf=new byte[len];
		int count=0;
		while(count<len)
		{
			int tc=din.read(buf);
			count=count+tc;
		}	
		System.out.println("Read Str :"+buf);
		return ConvertUtil.fromBytesToString(buf);
	}
}
