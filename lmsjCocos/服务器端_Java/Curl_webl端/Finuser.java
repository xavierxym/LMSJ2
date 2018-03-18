import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.sql.*;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.*;

@WebServlet("/Finuser")
public class Finuser extends HttpServlet {
	
	private static final long serialVersionUID = 1L;
	/**
	 * Constructor of the object.
	 */
	public Finuser() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		int flag=0;
		//req2RawString(request);
		// String urladd=request.getRequestURI();
		// System.out.println("------------>"+urladd);
		 response.setContentType("text/html;charset=utf-8");
		 request.setCharacterEncoding("gbk"); 
		 String username =request.getParameter("username");
		 request.setCharacterEncoding("gbk");
		 String password2 =request.getParameter("password");
		  if(username!=null && password2!=null)
				{
			
				  Connection conn=null;
				  PreparedStatement ps=null;
				  ResultSet rs=null;
				  
			try{
				
				//连接数据库
				Class.forName("com.mysql.jdbc.Driver");
				String url="jdbc:mysql://localhost:3306/cocos?useUnicode=true&characterEncoding=gbk";
				String usernamesql ="root";
				String password="xavier";
				conn = DriverManager.getConnection(url,usernamesql,password);
				
				String sql ="select * from users where uname=? and password=?";
			 	ps = conn.prepareStatement(sql);
			 	ps.setString(1,username);
			 	ps.setString(2,password2);		
			 	rs = ps.executeQuery();
					
			while(rs.next()){
				
				if((rs.getString("uname").equals(username))&&(rs.getString("password").equals(password2)) )
					{
							//返回结果
							request.setCharacterEncoding("GBK");	
							response.getWriter().write("username="+rs.getString("uname")+"\n");
							response.getWriter().write("rank="+rs.getString("rank")+"\n");
							response.getWriter().write("coins="+rs.getString("coin")+"\n");
							response.getWriter().write("mail="+rs.getString("mail")+"\n");
							response.getWriter().write("qq="+rs.getString("qq")+"\n");
							response.getWriter().write("diamonds="+rs.getString("diamonds")+"\n");
							response.getWriter().write("score="+rs.getString("score")+"\n");
							response.getWriter().write("signtime="+rs.getString("signtime")+"\n");
							flag=1;
					}
				  
			     }
			  if(flag==0)
				{
				  String sql2 ="insert users (uname,password,rank,coin,diamonds,score) values(?,'lmsj',1,100,20,0)";
				  ps = conn.prepareStatement(sql2);
				  ps.setString(1,username);
				 // rs = ps.executeQuery();
				  int row = ps.executeUpdate();
					if(row > 0){
						request.setCharacterEncoding("GBK");	
						response.getWriter().write("rank=1\n");
						response.getWriter().write("coins=100\n");
						response.getWriter().write("diamonds=20\n");
						response.getWriter().write("score=0\n");
						response.getWriter().write("noFindUname=newOne");
					}
				}

			}catch (ClassNotFoundException e){
				e.printStackTrace();
			} catch (SQLException e){
				e.printStackTrace();
				
			}finally{
				if(rs!=null)
				{
					try{
					rs.close();
					}catch(Exception e){e.printStackTrace();}
				}
				if(ps!=null)
				{
					try{
					ps.close();
					}catch(Exception e){e.printStackTrace();}
				}
				if(conn!=null)
				{
					try{
					conn.close();
					}catch(Exception e){e.printStackTrace();}
				}

				}
				
				
			
		}else{
			 response.getWriter().write("nullname=nullpassworld");
		}

	
		  
		  
		
		
		
	}
	
	//可略
	public static void req2RawString(HttpServletRequest request) {
        StringBuilder sb = new StringBuilder();
        BufferedReader reader = null;
        try {
            reader = request.getReader();
            String line;
            while ((line = reader.readLine()) != null) {
                 sb.append(line).append('\n');
            }
            if (sb.length() > 1) {
                 sb.replace(sb.length() - 1, sb.length(), "");
            }
        }
        catch (IOException e) {
            System.out.println("RequestUtil,IOException:" + e);
        }
        finally {
            if (reader != null) {
                 try {
                      reader.close();
                 }
                 catch (IOException e) {
                	 System.out.println("RequestUtil,IOException:" + e);
                 }
            }
        }
        String str = sb.toString();  
        System.out.println("---------->Request Result str :" + str);
        
     //   return str;
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doGet(request, response);

	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
		
	}

}
