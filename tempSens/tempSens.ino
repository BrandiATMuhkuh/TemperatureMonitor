int offset = 3000;
int timeBetweenMedian = 1000;
float celsArrayp[5] = {0,0,0,0,0}; //Store average celcius values
float minThreshold = 18;
float maxThreshold = 21;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  //take in current voltage and calculate temperature
  for(int i = 0; i < 5; i ++){
    celsArrayp[i] = ((analogRead(A0)/1024.0)*500) - 273.15;
    delay(500);
  }
    
  bubbleSort(celsArrayp, 5); //sort array  
  Serial.print(celsArrayp[2]); // print median object. just in case we had weird readings
  Serial.println();
 
  delay(3000);
}

// an horribly inefficent sorting algorithm. Sorry i wantted to use qsort but ardino had no sorting
// available and i coulde find a library. So i took the first thing i could find online :(
void bubbleSort(float analogValues[], int numReadings) {

  int out, in, swapper;
  for(out=0 ; out < numReadings; out++) {  // outer loop
    for(in=out; in<(numReadings-1); in++)  {  // inner loop
      if( analogValues[in] > analogValues[in+1] ) {   // out of order?
        // swap them:
        swapper = analogValues[in];
        analogValues [in] = analogValues[in+1];
        analogValues[in+1] = swapper;
      }
    }
  }
}
