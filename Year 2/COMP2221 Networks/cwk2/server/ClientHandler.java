import java.net.*;
import java.io.*;
import java.util.*;
import java.text.SimpleDateFormat;


public class ClientHandler extends Thread {

	// Create variables used in class
	private Socket clientSocket = null;
	private DataInputStream byteReaderHandler = null;
	private DataOutputStream byteSenderHandler = null;
	private ServerProtocol serverProtocol = null;

	// Constructor
	public ClientHandler(Socket client) {
		super("ClientHandler");
		this.clientSocket = client;

		// Log date,time and IP address of accpeting client
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy:HH.mm.ss:");
		Calendar calendar = Calendar.getInstance();
		try {
			PrintWriter toFile = new PrintWriter(
				new BufferedWriter(new FileWriter("log.txt",true)));
			toFile.append(dateFormat.format(calendar.getTime()));
			toFile.append(client.getInetAddress().getHostAddress());
			toFile.flush();
		}
		catch(IOException error) {
			System.out.println("Error trying to log");
		}
	}

	// Method to handle list
	public void handleListCommand() throws IOException {

		// Log client request
		try {
			PrintWriter toFile = new PrintWriter(
				new BufferedWriter(new FileWriter("log.txt",true)));
			toFile.append(":");
			toFile.append("list\n");
			toFile.flush();
		}
		catch(IOException error) {
			System.out.println("Error trying to log");
		}

		// Variables to store filenames as strings and as bytes to be sent
		String[] fileNames = serverProtocol.getFileNamesOnServer();

		// Send number of files on server
		byteSenderHandler.writeInt(fileNames.length);
		byteSenderHandler.flush();

		// Send filenames as bytes
		for(int i = 0; i < fileNames.length; ++i) {

			// Convert string to byte array
			byte[] fileNameAsBytes = fileNames[i].getBytes();

			// Send length of byte array
			byteSenderHandler.writeInt(fileNameAsBytes.length);
			byteSenderHandler.flush();

			// Send byte array
			byteSenderHandler.write(fileNameAsBytes);
			byteSenderHandler.flush();
		}
	}

	// Method to handle get
	public void handleGetCommand() throws IOException {

		// Read size of file name
		int fileNameLength = byteReaderHandler.readInt();

		// Create byte array to store file name as bytes
		byte[] fileNameAsBytes = new byte[fileNameLength];

		// Read file name
		byteReaderHandler.read(fileNameAsBytes);

		// Convert bytes to string
		String fileName = new String(fileNameAsBytes);

		// Check the file exists on the server
		if(serverProtocol.fileExistsOnServer(fileName)) {

			// Log client request
			try {
				PrintWriter toFile = new PrintWriter(
					new BufferedWriter(new FileWriter("log.txt",true)));
				toFile.append(":");
				toFile.append("get " + fileName + "\n");
				toFile.flush();
			}
			catch(IOException error) {
				System.out.println("Error trying to log");
			}

			// Send true to client
			byteSenderHandler.writeInt(1);
			byteSenderHandler.flush();

			// Send file to client
			try {

				// Get the file as bytes
				byte[] fileAsBytes = serverProtocol.getFileAsBytes(fileName);

				// Send size of byte array to client
				byteSenderHandler.writeInt(fileAsBytes.length);
				byteSenderHandler.flush();

				// Send the file
				byteSenderHandler.write(fileAsBytes);
				byteSenderHandler.flush();
			}
			catch(IOException error) {
				return;
			}
		}

		// Send false to client
		else {
			byteSenderHandler.writeInt(0);
			byteSenderHandler.flush();

			// Log error request
			try {
				PrintWriter toFile = new PrintWriter(
					new BufferedWriter(new FileWriter("log.txt",true)));
				toFile.append(":");
				toFile.append("get request error\n");
				toFile.flush();
			}
			catch(IOException error) {
				System.out.println("Error trying to log");
			}
		}
	}

	// Method to handle put
	public void handlePutCommand() throws IOException {

		// Read true/false value from client
		int clientFileExists = byteReaderHandler.readInt();

		// Only try read file if client sends true
		if(clientFileExists == 1) {

			// Read size of byte array for file name
			int fileNameLength = byteReaderHandler.readInt();

			// Create byte array for filename
			byte[] fileNameAsBytes = new byte[fileNameLength];

			// Read bytes of filename
			byteReaderHandler.read(fileNameAsBytes);

			// Convert bytes to string
			String fileName = new String(fileNameAsBytes);

			// Log client request
			try {
				PrintWriter toFile = new PrintWriter(
					new BufferedWriter(new FileWriter("log.txt",true)));
				toFile.append(":");
				toFile.append("put " + fileName + "\n");
				toFile.flush();
			}
			catch(IOException error) {
				System.out.println("Error trying to log");
			}

			// Open file
			File file = new File("serverFiles/" + fileName);

			// Ensure file exists
			file.createNewFile();

			// Read size of byte array of file
			int fileLength = byteReaderHandler.readInt();

			// Create byte array for file
			byte[] fileAsBytes = new byte[fileLength];

			// Read bytes of file
			byteReaderHandler.read(fileAsBytes);

			// Write bytes into file
			FileOutputStream writeBytestoFile = new FileOutputStream(file);
			writeBytestoFile.write(fileAsBytes);
			writeBytestoFile.close();
		}

		// Log error request
		else {
			try {
				PrintWriter toFile = new PrintWriter(
					new BufferedWriter(new FileWriter("log.txt",true)));
				toFile.append(":");
				toFile.append("put request error\n");
				toFile.flush();
			}
			catch(IOException error) {
				System.out.println("Error trying to log");
			}
		}
	}

	// HandleclientCommandAsBytes client requests
	public void run() {

		// Create new protocol
		serverProtocol = new ServerProtocol();

		// Try create the readers
		try {
			byteReaderHandler = new DataInputStream(
				new BufferedInputStream(clientSocket.getInputStream()));
			byteSenderHandler = new DataOutputStream(
				new BufferedOutputStream(clientSocket.getOutputStream()));
			byteSenderHandler.flush();
		}
		catch(IOException error) {
			System.out.println("IOException");
			return;
		}

		// Read command from client
		try {

			// Read command as int
			int clientCommand = byteReaderHandler.readInt();

			// 1 signifies list command
			if(clientCommand == 1) {

				// Handle list
				handleListCommand();
			}

			// 2 signifies get command
			else if(clientCommand == 2) {

				// Handle get
				handleGetCommand();
			}

			// 3 signifies put command
			else if(clientCommand == 3) {

				// Handle put
				handlePutCommand();
			}

			// Command does not exist
			else {
				System.out.println("Command unkown");
			}
		}
		catch(IOException error) {
			System.out.println("IOException reading");
		}

		// Close all streams and sockets
		try {
      if(byteSenderHandler != null) {
				byteSenderHandler.flush();
				byteSenderHandler.close();
      }
      if(byteReaderHandler != null)
				byteReaderHandler.close();
			if(clientSocket != null)
				clientSocket.close();
		}
		catch(IOException error) {
			System.out.println("IOException closing");
		}
	}
}
