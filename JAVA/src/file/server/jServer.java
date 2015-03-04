package file.server;


import java.io.*;
import java.net.*;

public class jServer {

	//private final static String fileToSend = "/home/aunn/testSend";
	public static boolean runFlag = true;
	static int port = 55555;
	public static void main(String args[]) {
		jServer.run("/home/aunn/testSend");
	}

	public static void run(String fileToSend){

		ServerSocket welcomeSocket = null;
		Socket connectionSocket = null;
		BufferedOutputStream outToClient = null;
		String clientType = "J";
		try {
			welcomeSocket = new ServerSocket(port);
			System.out.println("aaa");
			while(runFlag){
				System.out.println("bbb");
				try {

					connectionSocket = welcomeSocket.accept();
					outToClient = new BufferedOutputStream(connectionSocket.getOutputStream());
					InputStream inStream = connectionSocket.getInputStream();
					int bytesRead=-1;

					byte[] aByte = new byte[1];
					bytesRead = inStream.read(aByte);
					//System.out.println(.toString());
					clientType = new String(aByte);
					System.out.println("string " + clientType);

					//					inStream.close();
				} catch (IOException ex) {
					ex.printStackTrace();
					// Do exception handling
				}
				System.out.println("Now writing file to output");
				if (outToClient != null) {
					File myFile = new File( fileToSend );
					byte[] mybytearray = new byte[(int) myFile.length()];

					FileInputStream fis = null;

					try {
						fis = new FileInputStream(myFile);
					} catch (FileNotFoundException ex) {
						// Do exception handling
					}
					BufferedInputStream bis = new BufferedInputStream(fis);
					if(clientType.compareToIgnoreCase("C")==0){

						Integer fileSize=(int) myFile.length();
						System.out.println("Hello*"+ fileSize);
						outToClient.write(fileSize);
						outToClient.flush();
					}
					try {
						bis.read(mybytearray, 0, mybytearray.length);
						outToClient.write(mybytearray, 0, mybytearray.length);
						outToClient.flush();
						outToClient.close();
						connectionSocket.close();

						// File sent, exit the main method
						//return;
					} catch (IOException ex) {
						// Do exception handling
						//welcomeSocket.close();
					}
				}
			}// while

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}
}