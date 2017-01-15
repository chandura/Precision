//Set up the pins to be used and their purpose
int targetOnePin = A4; //Light sensor for target one.
int targetTwoPin = A3; //Light sensor for target two

int targetOneVal = 0;
int targetTwoVal = 0;
int liveTargetVal = 0;
int sleepingTargetVal = 0;

int targetOneLive = 3; //Currently the yellow LED
int targetTwoLive = 4; //Currenty the orange LED
int targetMiss = 5; //Curently the red LED
int targetHit = 6; //Add a green LED

int whichTargetLive = 0;
int liveTimer = 0;

long howLongLive = 0;

int targetResult = 0; //Record if there is a result
int resultCount = 0;

//int Yellow = 3;
//int Orange = 4;
//int Red = 5;

//int lightsensorVal = 0;

void setup () {
  Serial.begin(9600); //Open Pin A0 as a serial port 
  
  //Loop round pins number 2 through to 6 and set them as output pins
  for (int pinNumber = 2; pinNumber <7; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  digitalWrite(targetOneLive, LOW);
  digitalWrite(targetTwoLive, LOW);
  digitalWrite(targetHit, HIGH);
  digitalWrite(targetMiss, HIGH);

  randomSeed(analogRead(0));
}

void loop (){
  
  targetOneVal = analogRead(targetOnePin);
  targetTwoVal = analogRead(targetTwoPin);
    
  while (targetOneVal > 200 || targetTwoVal > 200){
      targetOneVal = analogRead(targetOnePin);
      targetTwoVal = analogRead(targetTwoPin); 
      digitalWrite(targetHit, HIGH);
      digitalWrite(targetMiss, HIGH);
  }

  countdown();
  
  digitalWrite(targetHit, LOW);
  digitalWrite(targetMiss, LOW);
  
  //Select a target
  whichTargetLive = random(3, 5);
  Serial.print("Target ");
  Serial.print(whichTargetLive);
  Serial.println(" is live");

  //Select a duration
  howLongLive = random(100, 1000);
  Serial.print("Live for ");
  Serial.print(howLongLive);
  Serial.println(" seconds");

  targetResult = 0;
  liveTimer = 0;
  digitalWrite(whichTargetLive, HIGH);
  while (liveTimer < howLongLive){
    Serial.print("liveTimer ");
    Serial.print(liveTimer);
    Serial.print(" howLongLive = ");
    Serial.println(howLongLive);
    if (whichTargetLive == targetOneLive){
      liveTargetVal = analogRead(targetOnePin);
      sleepingTargetVal = analogRead(targetTwoPin);
    }
    else {
      liveTargetVal = analogRead(targetTwoPin);
      sleepingTargetVal = analogRead(targetOnePin);
    }
   
    //Serial.print ("Live target value ");
    //Serial.println (liveTargetVal);

    if (liveTargetVal > 200){
      digitalWrite(targetHit, HIGH);
      targetResult = 6;
      liveTimer = howLongLive; 
    }
    
    if (sleepingTargetVal > 200){
      digitalWrite(targetMiss, HIGH);
      targetResult = 5;
      liveTimer = howLongLive;
    }    
    liveTimer++;
  }

  if (targetResult > 0){
      Serial.println("Positive result recorded");
  }
  else {
    Serial.println("Timeout");
    targetResult = 5;
    digitalWrite(whichTargetLive, LOW);
    digitalWrite(targetMiss, HIGH);
  }
  
  digitalWrite(whichTargetLive, LOW); 
  //delay(5000);
  for (resultCount = 0; resultCount < 10; resultCount++){
    Serial.print("targetResult ");
    Serial.print(targetResult);
    Serial.print("  resultCount = ");
    Serial.println(resultCount);
    digitalWrite(targetResult, LOW);
    delay(500);
    digitalWrite(targetResult, HIGH);
    delay(500);
  }
  digitalWrite(targetResult, LOW);
 }
 
