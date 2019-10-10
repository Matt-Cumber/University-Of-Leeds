import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class Server {
	private ServerSocket serverSocket = null;
	private ExecutorService executorService = null;

	// Constructor
	public Server() {

		// Try to create server socket which listens on port 8888
		try {
			serverSocket = new ServerSocket(8888);
		}
		catch(IOException error) {
			System.out.println("There was an error when opening the server"
			 + " socket on port 8888.");
		}
	}

	// Method for executing the server
	public void executeServer() {

		// Set threadpool size of max 10 threads
		executorService = Executors.newFixedThreadPool(10);

		// Server loop
		while(true) {

			// Connect with clients
			try {

				// Wait for a client to attempt to connect to server
				Socket clientSocket = serverSocket.accept();

				// Submit the client for the Executor to manage
				executorService.execute(new ClientHandler(clientSocket));
			}
			catch(IOException error) {
				System.out.println("There was an error waiting for a client."
					+ " Shutting server down.");
				System.exit(1);
			}
			catch(SecurityException error) {
				System.out.println("There was a security error accepting clients."
				 + "Shutting server down.");
				System.exit(1);
			}
		} // End serrver loop
	}

	public static void main( String[] args ) {

		// Create and run the server
		Server server = new Server();
		server.executeServer();
	}
}
