import java.io.*;
import java.net.*;
import org.json.*;



public class JavaTest
{
    public static void main(String []args)  throws Exception 
    {
	URL task = new URL("http://localhost:8080/engine-rest/task");
	HttpURLConnection task_connection =(HttpURLConnection) task.openConnection(); 
	task_connection.setRequestProperty("Acceptcharset", "en-us");
	task_connection.setRequestProperty("Accept-Language", "en-US,en;q=0.5");
	task_connection.setRequestProperty("charset", "EN-US");
	task_connection.setRequestProperty("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
	BufferedReader in = new BufferedReader(
		new InputStreamReader(
		    task_connection.getInputStream()));
	String inputLine;
	StringBuffer response = new StringBuffer();

	while ((inputLine = in.readLine()) != null) 
	{
	    response.append(inputLine);
	}

	in.close();


	//System.out.println("data recived!");
	System.out.println("=======Start======");

	JSONArray arr = new JSONArray(response.toString());
	for (int i = 0; i< arr.length(); i++)
	{
	    System.out.println("id: "+arr.getJSONObject(i).getString("id"));
	    System.out.println("name: "+arr.getJSONObject(i).getString("name"));
	    System.out.println("-------------");
	}
	System.out.println("=======End======");



    }


}
