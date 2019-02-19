import java.io.*;
public class DataStreamTest
{
	public static void main(String[] args)
	{
		try
		{
			FileOutputStream fos=new FileOutputStream("e:\\Datastream.txt");
			BufferedOutputStream bos=new BufferedOutputStream(fos);
			DataOutputStream dos=new DataOutputStream(bos);
			dos.writeInt(36);
			dos.writeUTF("ab2 �й�");
			
	
			dos.writeBytes("ab3 �й�");
	        //dos.writeBytes("we are");
			dos.writeChars("ab4 �й�");
			dos.close();
			
			FileInputStream fis=new FileInputStream("e:\\Datastream.txt");
			BufferedInputStream bis=new BufferedInputStream(fis);
			DataInputStream dis=new DataInputStream(bis);
			System.out.println(dis.readInt());
		    System.out.println(dis.readUTF());

		    
			byte[] buf="we are".getBytes();
			int len=dis.read(buf);
			System.out.println(new String(buf,0,len));
			
            for (int i=0; i<"ab4 �й�".length(); i++)
            System.out.println(dis.readChar());	
			fis.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}