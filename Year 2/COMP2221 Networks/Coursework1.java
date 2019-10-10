import java.io.*;
import java.net.*;

public class Coursework1 {

  private int ipv4Count = 0;

  // Get some information of an InetAddress for supplied host names
  public void tryGetInetInfo(String hostNames[]) {

    // If there are no host names print error message
    if(hostNames.length == 0) {
      System.out.print("Please enter at least one host name on the ");
      System.out.println("comand line. IP addresses are not accepted.");
      System.out.print("An example of an accepted host name is : ");
      System.out.println("google.com");

      // Stop further execution of this method
      return;
    }

    // Create array to store addresses
    InetAddress addresses[] = new InetAddress[hostNames.length];

    // String arrays to store ipv4 bytes for ipv4 addresses
    String ipv4Address = "";
    String seperateBytes[] = new String[4];
    String firstSetBytes[][] = new String[hostNames.length][1];
    String secondSetBytes[][] = new String[hostNames.length][1];
    String thirdSetBytes[][] = new String[hostNames.length][1];
    String fourthSetBytes[][] = new String[hostNames.length][1];


    // Loop through host names and determine InetAddress information
    for(int i = 0;i < hostNames.length; ++i) {

      System.out.println("---------------------------------------------------");

      // Deterimine the IP address of hostName
      try {
        addresses[i] = InetAddress.getByName(hostNames[i]);

        // Print successful creation message
        System.out.print("The host name " + addresses[i].getHostName());
        System.out.println(" was found");

        // Print the IP address of the host
        System.out.print("  This host has an IP address of ");
        System.out.println(addresses[i].getHostAddress());

        // Print the Canonical Hostname
        System.out.print("  This host has a canonical host name of ");
        System.out.println(addresses[i].getCanonicalHostName());

        // Determine if the hostName is reachable
        try {
          // Wait at most 1 second until timeout to determine if
          if(addresses[i].isReachable(1000) == true) {
            System.out.println("  This host name is reachable");
          }
          else {
            System.out.println("  This host name is not reachable");
          }
        }
        // Catch error IOExcpetion from network error
        catch(IOException error) {
          System.out.println("  There was an error with the network trying to reach this host name.");
        }

        // Determine if the Address is IPV4 or IPV6
        if (addresses[i] instanceof Inet4Address) {
          System.out.println("  This host name has an IPV4 address");

          // Store each byte of the IP address seperately
          ipv4Address = addresses[i].getHostAddress();
          seperateBytes = ipv4Address.split("\\.",4);
          firstSetBytes[ipv4Count][0] = seperateBytes[0];
          secondSetBytes[ipv4Count][0] = seperateBytes[1];
          thirdSetBytes[ipv4Count][0] = seperateBytes[2];
          fourthSetBytes[ipv4Count][0] = seperateBytes[3];
          ++ipv4Count;
        }
        else if (addresses[i] instanceof Inet6Address) {
          System.out.println("  This host name has an IPV6 address");
        }
      }

      // Catch error of hostName not existing and print error message
      catch(UnknownHostException error) {
        System.out.println("The host name " + hostNames[i] + " could not be found");
      }
    }

    System.out.println("---------------------------------------------------");

    // check if there are more than one IPV4 addresses found
    if(ipv4Count >= 2) {

      // Print out this information
      System.out.println("Highest level of shared hierarchy for IPV4 host names is");
      System.out.print("  ");
      String comparisonByte = firstSetBytes[0][0];

      // Check all first bytes are the same
      for(int i = 1; i < ipv4Count; ++i) {
        if(firstSetBytes[i][0].equals(comparisonByte) == false) {
          System.out.println("*.*.*.*");
          return;
        }
      }

      // Check all second bytes are the same
      comparisonByte = secondSetBytes[0][0];
      for(int i = 1; i < ipv4Count; ++i) {
        if(secondSetBytes[i][0].equals(comparisonByte) == false) {
          System.out.println(firstSetBytes[0][0] + ".*.*.*");
          return;
        }
      }

      // Check all third bytes are the same
      comparisonByte = thirdSetBytes[0][0];
      for(int i = 1; i < ipv4Count; ++i) {
        if(thirdSetBytes[i][0].equals(comparisonByte) == false) {
          System.out.println(firstSetBytes[0][0] + "." + secondSetBytes[0][0] + ".*.*");
          return;
        }
      }

      // Check all fourth bytes are the same
      comparisonByte = fourthSetBytes[0][0];
      for(int i = 1; i < ipv4Count; ++i) {
        if(fourthSetBytes[i][0].equals(comparisonByte) == false) {
          System.out.println(firstSetBytes[0][0] + "." + secondSetBytes[0][0] + "." + 
            thirdSetBytes[0][0] + ".*");
          return;
        }
      }

      // At this point the addresses don't share any common bytes
      System.out.println(firstSetBytes[0][0] + "." + secondSetBytes[0][0] + "."
       + thirdSetBytes[0][0] + "." + fourthSetBytes[0][0]);
      return;
    }
  }

  public static void main(String args[]) {
    Coursework1 coursework = new Coursework1();
    coursework.tryGetInetInfo(args);
  }
}
