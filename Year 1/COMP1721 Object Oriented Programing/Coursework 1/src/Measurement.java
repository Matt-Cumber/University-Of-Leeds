import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * A single measurement of NO<sub>2</sub> level.
 *
 * <p>Created for COMP1721 Coursework 1.</p>
 *
 * @author Matthew Cumber
 */

public class Measurement {
  // Use this when parsing measurement time
  private static DateTimeFormatter FORMAT = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");

  // define fields
  private LocalDateTime time;
  private int level;

  public Measurement(String record) {
    // implement constructor
    String[] recordSplit = record.split(",");
    // throw DataException when there the data is not the correct length
    if(recordSplit.length<2){
      throw new DataException("There is data missing.");
    }
    else if(recordSplit.length>3){
      throw new DataException("Data is not in the correct format.");
    }
    // if the length of the data is 2 this signifies there was no reading so must deal with this case seperately
    else if(recordSplit.length==2){
      level=-1;
      time=LocalDateTime.parse(recordSplit[0]+" "+recordSplit[1],FORMAT);
    }
    else{
      level= Integer.parseInt(recordSplit[2]);
      time=LocalDateTime.parse(recordSplit[0]+" "+recordSplit[1],FORMAT);
    }
  }

  public LocalDateTime getTime() {
    return time;
  }

  public int getLevel() {
    return level;
  }

  public String toString() {
    String string;
    // find out if there is a level for the date so that each case can be printed in an appropriate way and the method getLevel is not incorrectly used
    if(getLevel()==-1){
      string=getTime()+", no data";
    }
    else{
      string=getTime()+", "+getLevel()+" \u00b5g/m\u00b3";
    }
    return string;
  }
}
