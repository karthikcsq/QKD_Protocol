#include <Servo.h>
//#include <String>

int to_deg[6] = {45, 105, 80, 65, 155, 135}; //h is vertical/horizontal and d is diagonal

String Alice[4] = {"Ah0", "Ad0", "Ah1", "Ad1"};
String Bob[2] = {"Bh", "Bd"};

Servo servoA;
Servo servoB;
int lastA;
int lastB;
int degree = 0;
String message="";
String key = "";
String binaryMessage="";
String aliceBases="";
String bobBases="";
int a;
int b;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servoA.attach(8);
  servoB.attach(9);

  servoA.write(45);
  servoB.write(155);

  lastA = 45;
  lastB = 155;
  
  message = "cat";
  binaryMessage = "010000110100000101010100";
  key = "110110001001001101110100";
  aliceBases = "dhhddhdhhhhddhddhdhhdhhd";
  bobBases = "hhdhdddhhdhhdhddhhdhddhd";
}

void writeToB(int degree) {
  Serial.println(degree);
  if (degree < lastB){
    for (int pos = lastB; pos >= degree; pos -= 1) { // goes backwards
    // in steps of 1 degree
      servoB.write(pos);
      delay(8);                       // waits 15ms for the servo to reach the position
    }
  }
  else {
    for (int pos = lastB; pos <= degree; pos += 1) { // goes forwards
    // in steps of 1 degree
      servoB.write(pos);
      delay(8);                       // waits 15ms for the servo to reach the position
    }
  }
  lastB = degree;
}

void writeToA(int degree) {
  Serial.println(degree);
  if (degree < lastA){
    for (int pos = lastA; pos >= degree; pos -= 1) { // goes backwards
    // in steps of 1 degree
      servoA.write(pos);              // tell servo to go to position in variable 'pos'
      //servoB.write(pos);
      delay(8);                       // waits 15ms for the servo to reach the position
    }
  }
  else {
    for (int pos = lastA; pos <= degree; pos += 1) { // goes forwards
    // in steps of 1 degree
      servoA.write(pos);              // tell servo to go to position in variable 'pos'
      //servoB.write(pos);
      delay(8);                       // waits 15ms for the servo to reach the position
    }
  }
  lastA = degree;
}

void loop() {

  String hang = "";
  Serial.print("Press a key to begin:");
  while (hang == "") {
    while (Serial.available() == 0) {
    }
    hang = Serial.readString();
  }

  // put your main code here, to run repeatedly:
  Serial.print("enter a lowercase message to send.");
  while (message == "") {
    while (Serial.available() == 0) {
    }
    message = Serial.readString();
  }
  //convert the message to binary
  binaryConverter(message);
  //make a key 2 times the length of the message (to account for lost numbers when choosing wrong basis)
  for(int i =0; i<2*binaryMessage.length(); i++)
  {
    key+= String(random(0,2));
  }
  Serial.println("message in binary:" + binaryMessage);
  Serial.println("randomly generated key:" + key);
  Serial.print("enter bases for Alice, at least of length " +String(key.length())+ ", using  'd' and 'h').");
  while (aliceBases == "") {
    while (Serial.available() == 0) {
    }
    aliceBases = Serial.readString();
  }
  Serial.print("enter bases for Bob, at least of length " +String(key.length())+ ", using  'd' and 'h').");
  while (bobBases == "") {
    while (Serial.available() == 0) {
    }
    bobBases = Serial.readString();
  }
  for(int i=0; i<key.length(); i++)
  {
    Serial.print(i); Serial.print("/"); Serial.println(key.length());
    if(aliceBases.charAt(i)=='h')
    {
      a = 0;
    }
    if(aliceBases.charAt(i)=='d')
    {
      a = 1;
    }
    if(key.charAt(i)=='1')
    {
      a += 2;
    }
    if(bobBases.charAt(i)=='h')
    {
      b = 0;
    }
    if(bobBases.charAt(i)=='d')
    {        
      b = 1;
    }

    long int starttime = millis();

    String aGoTo = Alice[a];
    int aDegree = to_deg[a];
    Serial.print(aGoTo);
    Serial.print(": ");
    Serial.print(a); Serial.print("Degree:");
    writeToA(aDegree);

    String bGoTo = Bob[b];
    int bDegree = to_deg[b+4];
    Serial.print(bGoTo);
    Serial.print(": ");
    Serial.print(b+4); Serial.print("Degree:");
    writeToB(bDegree);

    long int endtime = millis();

    long int duration = endtime - starttime;

    Serial.print("Duration of rotation:");
    Serial.println(duration);

    if(duration < 670) {
      delay(670-duration);
    }

    delay(2500);

    long int realduration = millis() - starttime;

    Serial.print("Actual duration of process:");
    Serial.println(realduration);
  }
  message="";
  aliceBases="";
  bobBases="";
  binaryMessage="";
  key="";
}
//Write to Quantum Qey Qistribution

void binaryConverter(String input){
  
  for(int i=0;i<input.length();i++)
  {

    switch( input.charAt(i) ){

      case ' ':
      binaryMessage += "00100000";
      break;
      case 'a':
      binaryMessage += "01100001";
      break;
      case 'b':
      binaryMessage += "01100010";
      break;
      case 'c':
      binaryMessage += "01100011";
      break;
      case 'd':
      binaryMessage += "01100100";
      break;
      case 'e':
      binaryMessage += "01100101";
      break;
      case 'f':
      binaryMessage += "01100110";
      break;
      case 'g':
      binaryMessage += "01100111";
      break;
      case 'h':
      binaryMessage += "01101000";
      break;
      case 'i':
      binaryMessage += "01101001";
      break;
      case 'j':
      binaryMessage += "01101010";
      break;
      case 'k':
      binaryMessage += "01101011";
      break;
      case 'l':
      binaryMessage += "01101100";
      break;
      case 'm':
      binaryMessage += "01101101";
      break;
      case 'n':
      binaryMessage += "01101110";
      break;
      case 'o':
      binaryMessage += "01101111";
      break;
      case 'p':
      binaryMessage += "01110000";
      break;
      case 'q':
      binaryMessage += "01110001";
      break;
      case 'r':
      binaryMessage += "01110010";
      break;
      case 's':
      binaryMessage += "01110011";
      break;
      case 't':
      binaryMessage += "01110100";
      break;
      case 'u':
      binaryMessage += "01110101";
      break;
      case 'v':
      binaryMessage += "01110110";
      break;
      case 'w':
      binaryMessage += "01110111";
      break;
      case 'x':
      binaryMessage += "01111000";
      break;
      case 'y':
      binaryMessage += "01111001";
      break;
      case 'z':
      binaryMessage += "01111010";
      break;

      default:
      break;
    }
  }
}