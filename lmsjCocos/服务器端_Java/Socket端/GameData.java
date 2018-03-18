package zhuwai;
import java.util.*;
/**
 * 全局数据类
 * @author xavier
 *
 */
public class GameData 
{
	public static HashMap<Integer,String> clientList=new HashMap<Integer,String>();		//三个客户端的 ip地址
	public static HashMap<String,Integer> position=new HashMap<String,Integer>();
	public static ArrayList<Integer> gamming=new ArrayList<Integer>();
	public static int connectCount=0;				// 记录当前连接的客户端数量
	public static int prepareCount=0;				//记录客户端准备的数量
	public static int gamming2[];
	
	public static HashMap<Integer,String> peoplePrepareState=new HashMap<Integer,String>();	//记录准备的状态
	public static HashMap<Integer,String> tufuPrepareState=new HashMap<Integer,String>();	//记录准备的状态
	public static int gameState;
	public static int client;
	
	
	public static int num=0;
	//音效
	public static int effect_Row=-1;
	public static int effect_Col=-1;
	
	
	
}
