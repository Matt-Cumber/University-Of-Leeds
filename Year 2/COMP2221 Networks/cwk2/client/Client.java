import java.io.*;
import java.net.*;
import java.util.*;

public class Client {

	private Socket clientSocket = null;
	private DataInputStream byteReaderClient = null;
	private DataOutputStream byteSenderClient = null;

	// List
	public void listCommand() throws IOException {

		// read number of files
		// read lenght of file name
		// read file name

		// Read number of files on server
		int numberOfFiles = byteReaderClient.readInt();

		// If the number of files is greater than 0 read file names
		if(numberOfFiles > 0) {

			// Read all file names and print
			for(int i = 0; i < numberOfFiles; ++i) {

				// Read size of file name byte array
				int sizeOfFileName = byteReaderClient.readInt();

				// Create byte array of this size for filename
				byte[] fileNameAsBytes = new byte[sizeOfFileName];

				// Read bytes of file name
				byteReaderClient.read(fileNameAsBytes);

				// Convert bytes into a string
				String fileName = new String(fileNameAsBytes);

				// Print out file name
				System.out.println(fileName);
			}
		}

		// Else print no file names
		else {
			System.out.println("There are currently no files on the server.");
		}
	}

	// Get
	public void getCommand(String fileName) throws IOException {

		// Convert file name to bytes
		byte[] fileNameAsBytes = fileName.getBytes();

		// Send size of byte array
		byteSenderClient.writeInt(fileNameAsBytes.length);
		byteSenderClient.flush();

		// Send bytes to server
		byteSenderClient.write(fileNameAsBytes);
		byteSenderClient.flush();

		// Read the acknowledgement from the server
		int fileOnServer = byteReaderClient.readInt();

		// File exists on server
		if(fileOnServer == 1) {

			// Read size of file
			int lengthOfFile = byteReaderClient.readInt();

			// Create byte array to store file
			byte[] fileAsBytes = new byte[lengthOfFile];

			// Read bytes of file
			byteReaderClient.read(fileAsBytes);

			// Open a file
			File file = new File("clientFiles/" + fileName);

			// Ensure file exists
			file.createNewFile();

			// Write bytes to file
			FileOutputStream writeBytestoFile = new FileOutputStream(file);
			writeBytestoFile.write(fileAsBytes);
			writeBytestoFile.close();
		}

		// Server sent false (0)
		else {
			System.out.println("This file does not exist on the server.");
		}
	}

	// Returns true if given file name exists in clientFiles, false otherwise
	public boolean fileExistsClient(String fileName) {
		File folder = new File("clientFiles/");
		File[] clientFiles = folder.listFiles();

		for(int i = 0; i < clientFiles.length; ++i) {
			if(fileName.equals(clientFiles[i].getName())) {
				return true;
			}
		}
		return false;
	}

	// Returns the byte array of a file
	// Only called after fileExistsClient
	public byte[] clientFileAsBytes(String fileName) throws IOException {
		File folder = new File("clientFiles/");
		File[] clientFiles = folder.listFiles();
		byte[] fileAsBytes;

		for(int i = 0; i < clientFiles.length; ++i) {
			if(fileName.equals(clientFiles[i].getName())) {
				fileAsBytes = new byte[(int) clientFiles[i].length()];
				FileInputStream readFileToBytes =
					new FileInputStream(clientFiles[i]);
				readFileToBytes.read(fileAsBytes);
				readFileToBytes.close();
				return fileAsBytes;
			}
		}
		return fileAsBytes = new byte[0]; // Code not reached
	}

	// Put
	public void putCommand(String fileName) throws IOException {

		// File exists in client directory
		if(fileExistsClient(fileName)) {

			// Send true to server
			byteSenderClient.writeInt(1);
			byteSenderClient.flush();

			// Convert filename to bytes
			byte[] fileNameAsBytes = fileName.getBytes();

			// Send size of byte array
			byteSenderClient.writeInt(fileNameAsBytes.length);
			byteSenderClient.flush();

			// Send file name as bytes
			byteSenderClient.write(fileNameAsBytes);
			byteSenderClient.flush();

			// Get bytes of file
			byte[] fileAsBytes = clientFileAsBytes(fileName);

			// Send size of byte array
			byteSenderClient.writeInt(fileAsBytes.length);
			byteSenderClient.flush();

			// Send bytes of file
			byteSenderClient.write(fileAsBytes);
			byteSenderClient.flush();
		}

		// File does not exists in client directory
		else {

			// Send false to server
			byteSenderClient.writeInt(0);
			byteSenderClient.flush();

			// Print error to client
			System.out.println("File name \"" + fileName + "\" does not exist.");
		}
	}

	// Connect client to server and run request
	public void tryConnectToServer(String[] args) {

		// Connect to server
		try {
			clientSocket = new Socket("localhost",8888);
		}
		catch(IOException error) {
			System.out.println("There was an error connecting to the server."
				+ " Shutting down application.");
			System.exit(1);
		}

		// Create reader and writers
		try {
			byteReaderClient = new DataInputStream(
				new BufferedInputStream(clientSocket.getInputStream()));
			byteSenderClient = new DataOutputStream(
				new BufferedOutputStream(clientSocket.getOutputStream()));
			byteSenderClient.flush(); // Flush before use
		}
		catch(IOException error) {
			System.out.println("There was an error setting up client."
				+ " Shutting down appplication.");
			System.exit(1);
		}

		// Send command to server
		try {

			// List command
			if(args[0].equals("list")) {

				// Send server list command as int
				byteSenderClient.writeInt(1);
				byteSenderClient.flush();

				// Complete list command
				listCommand();
			}

			// Get command
			else if(args[0].equals("get")) {

				// Send server get command as int
				byteSenderClient.writeInt(2);
				byteSenderClient.flush();

				// Complete get command
				getCommand(args[1]);
			}

			// Put command
			else if(args[0].equals("put")) {

				// Send server put command as int
				byteSenderClient.writeInt(3);
				byteSenderClient.flush();

				// Complete put command
				putCommand(args[1]);
			}
		}
		catch(IOException error) {
			System.out.println("Failed to communicate with server."
				+ " Shutting down application.");
			System.exit(1);
		}

		// Close all streams and sockets
		try {
    	if(byteSenderClient != null) {
				byteSenderClient.flush();
				byteSenderClient.close();
      }
      if(byteReaderClient != null)
				byteReaderClient.close();
			if(clientSocket != null)
				clientSocket.close();
		}
		catch(IOException error) {
			System.out.println("IOException closing");
		}
	}

	public static void main( String[] args ) {

		// Create a new client
		Client client = new Client();

		// Expect at least command line argument but no more than 2
		if(args.length < 1 || args.length > 2){
			System.out.println("Enter a single command on the command line."
			 	+ "The commands are : \"list\",\"get\" and \"put\" where get and"
				+ "put are to be followed with an additional argument of the" +
				" file to be requested or sent.");
			System.exit(1);
		}

		// Connect straight away if only one argument with value "list"
		if(args[0].equals("list") && args.length == 1) {
			client.tryConnectToServer(args);
		}

		// Connect if exactly two arguments and first argument either get or put
		else if(args.length == 2 && (args[0].equals("get") || args[0].equals("put"))) {
			client.tryConnectToServer(args);
		}

		// Error
		else {
			System.out.println("Enter a single command on the command line."
			 	+ "The commands are : \"list\",\"get\" and \"put\" where get and"
				+ "put are to be followed with an additional argument of the" +
				" file to be requested or sent.");
			System.exit(1);
		}
	}
}
