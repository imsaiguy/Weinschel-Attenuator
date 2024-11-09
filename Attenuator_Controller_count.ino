// ImsaiGuy 2024
// Weinschel attenuator control board
// for ATTINY85 micro

int Button1 = 0;  //pin 5
int Button2 = 1;  //pin 6
int Data = 2;     //pin 7
int Clock = 3;    //pin 2
int Latch = 4;    //pin 3

byte num_to_seven_segment[10] = {
  0b00111111,  // 0
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4
  0b01101101,  // 5
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01101111   // 9
};


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
    shiftOut(Data, Clock, MSBFIRST, num_to_seven_segment[i % 10]);          //ones num
    shiftOut(Data, Clock, MSBFIRST, num_to_seven_segment[(i / 10) % 10]);   //tens num
    shiftOut(Data, Clock, MSBFIRST, num_to_seven_segment[(i / 100) % 10]);  //hundreds num
    shiftOut(Data, Clock, MSBFIRST, i);                                     //attenuator setting
    digitalWrite(Latch, HIGH);

    delay(30);  // Wait for 100 milliseconds before sending the next number
  }
}
