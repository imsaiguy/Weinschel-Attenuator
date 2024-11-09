// ImsaiGuy 2024
// Weinschel attenuator control board
// for ATTINY85 micro

int Button1 = 0;  //pin 5
int Button2 = 1;  //pin 6
int Data = 2;     //pin 7
int Clock = 3;    //pin 2
int Latch = 4;    //pin 3

void setup() {
  // put your setup code here, to run once:
  pinMode(Data, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(Latch, OUTPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  digitalWrite(Latch, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 255; i++) {
    digitalWrite(Latch, LOW);
    shiftOut(Data, Clock, MSBFIRST, i);   //ones num
    shiftOut(Data, Clock, MSBFIRST, i);   //tens num    
    shiftOut(Data, Clock, MSBFIRST, i);   //hundreds num
    shiftOut(Data, Clock, MSBFIRST, i);                                     //attenuator setting
    digitalWrite(Latch, HIGH);

    delay(30);  // Wait for 100 milliseconds before sending the next number
  }
}
