int offset = 3000;
int timeBetweenMedian = 1000;
float celsArrayp = 0.0; //Store average celcius values
float minThreshold = 18;
float maxThreshold = 21;
bool offOn = true;
bool _offOn = true; // this is to check if something changed
int relayPin = 13;
int avTop = 100;
int avCount = 0;
int avSum = 0;
float currentTemp = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  //take in current voltage and calculate temperature
  celsArrayp = ((analogRead(A0)/1024.0)*500) - 273.15;
  //Serial.println(celsArrayp);
  //do same calucations to balance the relay
  if(offOn == false){
    celsArrayp = celsArrayp - 7.00; 
  }
  
  //Calculate average count
  if(avCount < avTop){
    avSum = avSum + celsArrayp;
    avCount = avCount + 1;
  }else{
    // Reset everything after count ends
    currentTemp = avSum / avTop;
    avSum = 0;
    avCount=0;
  }

  if(currentTemp < 25.00){
    //Serial.println("turn on");
    offOn = false;
  }else{
    offOn = true;
  }
  
  // switch on or off the relay
  // this will switch on or off the relay and will do some
  if(_offOn != offOn){
    digitalWrite(relayPin, offOn);
  }
  _offOn = offOn;
  
  Serial.println(currentTemp); // print median object. just in case we had weird readings

 
  //delay(1000);
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
