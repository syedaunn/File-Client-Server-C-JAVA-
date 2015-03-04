package file.client;

import java.io.*;
import java.net.*;

public class jClient {

    private final static String serverIP = "127.0.0.1";
    private final static int serverPort = 55555;
    private static String fileOutput = "/home/aunn/testRecv3";

    public static void run(String outfile) {
    	fileOutput = outfile;
    	System.out.println("Hello");
    	
        byte[] aByte = new byte[1];
        int bytesRead;

        Socket clientSocket = null;
        InputStream inStream = null;
        BufferedOutputStream outStream = null;
        
        try {
            clientSocket = new Socket( serverIP , serverPort );
            
            inStream = clientSocket.getInputStream();
            outStream = new BufferedOutputStream(clientSocket.getOutputStream());
            if (outStream != null) {
            	outStream.write("J".getBytes());
				outStream.flush();
			//	outStream.close();
            	
            }
        } catch (IOException ex) {
            // Do exception handling
        	ex.printStackTrace();
        }
        

        System.out.println("Now recieveng file");

        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        if (inStream != null) {

            FileOutputStream fos = null;
            BufferedOutputStream bos = null;
            try {
                fos = new FileOutputStream( fileOutput );
                bos = new BufferedOutputStream(fos);
                bytesRead = inStream.read(aByte, 0, aByte.length);

                do {
                        baos.write(aByte);
                        bytesRead = inStream.read(aByte);
                } while (bytesRead != -1);

                bos.write(baos.toByteArray());
                bos.flush();
                bos.close();
                clientSocket.close();
            } catch (IOException ex) {
            	ex.printStackTrace();
                // Do exception handling
            }
        }
    }
}