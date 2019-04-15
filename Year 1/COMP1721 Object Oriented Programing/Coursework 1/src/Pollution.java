import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.io.*;

public class Pollution{
  public static void main(String[] args) {
    // throw exception if there is no argument entered on the command line
    if(args.length==0){
      throw new DataException("Please add a file to be read on the command line.\n");
    }
    // create a new dataset
    PollutionDataset dataset = new PollutionDataset();
    // attempt to read the file
    try{
      dataset.readCSV(args[0]);
    } catch(FileNotFoundException i){
      throw new DataException("Could not read the file.\n");
      }
    // print out the meaningful statistics
    System.out.printf("%d records processed.\n",dataset.size());
    System.out.printf("Max: %s\n",dataset.maxLevel());
    System.out.printf("Min: %s\n",dataset.minLevel());
    System.out.printf("Mean: %f\n",dataset.meanLevel());
    // check if the EU rules were breached
    if(dataset.dayRulesBreached()==null){
      System.out.println("The EU rules were not breached.");
    }
    else if(dataset.dayRulesBreached()!=null){
      // format the date to be printed as a string
      DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("yyy-MM-dd");
      LocalDate dateBreached=dataset.dayRulesBreached();
      String stringDateBreached=dateBreached.format(FORMATTER);
      // print breach message
      System.out.println("The EU rules were breached on the "+stringDateBreached);
    }
  }
}
