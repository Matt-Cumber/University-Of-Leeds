import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;


/**
 * A sequence of air pollution measurements.
 *
 * <p>Created for COMP1721 Coursework 1.</p>
 *
 * @author Matthew Cumber
 */
public class PollutionDataset {
  // add field
  List<Measurement> measurements=new ArrayList<>();

  public PollutionDataset() {
    // default constructor
    measurements.clear();
  }

  public void readCSV(String filename) throws FileNotFoundException {
    // load measurements from CSV file
    measurements.clear();
    Scanner readMe = new Scanner(new File(filename));
    // each file's first line has no use as it is not data so read this line straight away to get rid of it
    String redundantLine=readMe.nextLine();
    // read the rest of the file and add the data to the list of measurements
      while(readMe.hasNext()){
        String actualLine=readMe.nextLine();
        Measurement realMeasurement = new Measurement(actualLine);
        add(realMeasurement);
      }
    readMe.close();
  }

  public void add(Measurement m) {
    // add a new measurement to the dataset
    measurements.add(m);
  }

  public int size() {
   // return number of measurements in dataset
   return measurements.size();
  }

  public Measurement get(int index) {
    // return measurement at given index
    // throw exception if the index does not match any in the list
    if(index<0 || index >= size()){
      throw new DataException("There is no measurement with that index in the list.");
    }
    else{
      return measurements.get(index);
    }
  }

  public Measurement maxLevel() {
    // return measurement with max NO2 level
    // throw exception if the list is empty as there will be no max
    if(measurements.isEmpty()){
      throw new DataException("There are no measurements in the list.");
    }
    else{
      int maxLevel=0;
      Measurement maxMeasurement=measurements.get(0);
      for(int i=0;i<size();++i){
        // loop through the list and check if the measurement is greater than the current highest measurement
        if(measurements.get(i).getLevel()>maxLevel){
          maxLevel=measurements.get(i).getLevel();
          maxMeasurement=measurements.get(i);
        }
      }
      return maxMeasurement;
    }
  }

  public Measurement minLevel() {
    // return measurement with min NO2 level
    // throw exception if the list is empty as there will be no min
    if(measurements.isEmpty()){
      throw new DataException("There are no measurements in the list.");
    }
    else{
      int minLevel=measurements.get(0).getLevel();
      Measurement minMeasurement=measurements.get(0);
      // loop through the list
      for(int i=0;i<size();++i){
        // check if the value is -1 if so move on as this represents no recorded value for a particular day
        if(measurements.get(i).getLevel()==-1){
          continue;
        }
        // check if the measurement is lower than the current highest measurement
        else if(measurements.get(i).getLevel()<minLevel){
          minLevel=measurements.get(i).getLevel();
          minMeasurement=measurements.get(i);
        }
      }
      return minMeasurement;
    }
  }

  public double meanLevel() {
    // return mean NO2 level
    // throw exception if the list is empty as there will be no mean
    if(measurements.isEmpty()){
      throw new DataException("There are no measurements in the list.");
    }
    else{
      double meanLevel=0,sumLevels=0;
      int counter=0;
      // loop through measurements
      for(int i=0;i<size();++i){
        // check if the measurement is -1 if so ignore
        if(measurements.get(i).getLevel()==-1){
          continue;
        }
        // add to sum otherwise
        else{
          sumLevels+=measurements.get(i).getLevel();
          ++counter;
        }
      }
      meanLevel=sumLevels/counter;
      return meanLevel;
    }
  }

  public LocalDate dayRulesBreached() {
    // hourly toxic levels must not be more than 200 every hour(4 measurements) more than 18 times a year to meet EU standards
    // throw exception if the list is empty as there is no chance of a breach
    if(measurements.isEmpty()){
      throw new DataException("There are no measurements in the list.");
    }
    else{
      int timesRulesBreached=0,hourlyToxicityLevel=0,breachedAlready=0;
      String stringDayBreached;
      LocalDate dayBreached;
      // each file has 3 times at the beginning for the first hour so iterate through these before the rest of the file
      for(int i=0;i<3;++i){
        // if the measuremnt is -1 then ignore as this is invalid
        if(measurements.get(i).getLevel()==-1){
          continue;
        }
        else{
          hourlyToxicityLevel+=measurements.get(i).getLevel();
          // if the hourlyToxicityLevel breaches the rules increase how many times it has been breached by 1 assuming this has not already been counted for the hour
          if(hourlyToxicityLevel>200 && breachedAlready==0){
            ++timesRulesBreached;
            breachedAlready=1;
          }
        }
      }
      // reset the hourlyToxicityLevel and breachedAlready to 0 before moving onto rest of data
      hourlyToxicityLevel=0;
      breachedAlready=0;
      // start loop at index three as the first 3 pieces of data have been checked already(indexes start at 0).
      // increment this loop by 4 to iterate through hours of a day
      for(int i=3;i<size();i+=4){
        // iterate through each quartly measuremnt
        for(int j=i;j<i+4;++j){
          // stop the loop before going out of bounds
          if(j>size()-1){
            break;
          }
          // if the measuremnt is -1 then ignore as this is invalid
          else if(measurements.get(j).getLevel()==-1){
            continue;
          }
          hourlyToxicityLevel+=measurements.get(j).getLevel();
          // if the hourlyToxicityLevel breaches the rules increase how many times it has been breached by 1 assuming this has not already been counted for the hour
          if(hourlyToxicityLevel>200 && breachedAlready==0){
            ++timesRulesBreached;
            breachedAlready=1;
          }
          // if the rules have been breached more than 18 times return the 19th breach
          else if(timesRulesBreached>18){
            dayBreached=measurements.get(j).getTime().toLocalDate();
            return dayBreached;
          }
        }
        // reset hourlyToxicityLevel and breachedAlready as before
        hourlyToxicityLevel=0;
        breachedAlready=0;
      }
      return null;
    }
  }
}
