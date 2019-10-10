import java.io.*;
import java.net.*;

class ServerProtocol {

  // Returns string array of file names on server
  public String[] getFileNamesOnServer() {

    File folder = new File("serverFiles/");
    File[] filesOnServer = folder.listFiles();

    String[] fileNames = new String[filesOnServer.length];

    for(int i = 0; i < fileNames.length; ++i) {
      fileNames[i] = filesOnServer[i].getName();
    }

    return fileNames;
  }

  // Returns true if file exists on server, false otherwise
  public boolean fileExistsOnServer(String fileName) {

    File folder = new File("serverFiles/");
    File[] filesOnServer = folder.listFiles();

    for(int i = 0; i < filesOnServer.length; ++i) {
      if(fileName.equals(filesOnServer[i].getName())) {
        return true;
      }
    }
    return false;
  }

  // Returns the bytes of a file onh the server
  // File name is checked using fileExistsOnServer before calling this method
  public byte[] getFileAsBytes(String fileName) throws IOException {

    File folder = new File("serverFiles/");
    File[] filesOnServer = folder.listFiles();
    byte[] fileAsBytes;

    for(int i = 0; i < filesOnServer.length; ++i) {
      if(fileName.equals(filesOnServer[i].getName())) {
        fileAsBytes = new byte[(int) filesOnServer[i].length()];
        FileInputStream readFileToBytes = new FileInputStream(filesOnServer[i]);
        readFileToBytes.read(fileAsBytes);
        readFileToBytes.close();
        return fileAsBytes;
      }
    }
    return fileAsBytes = new byte[0]; // Code not reached
  }
}
