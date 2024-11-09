// ImsaiGuy 2024
// Weinschel attenuator control board
// for ATTINY85 micro

#define Button1 0  //pin 5
#define Button2 1  //pin 6
#define Data    2  //pin 7
#define Clock   3  //pin 2
#define Latch   4  //pin 3
int Attn = 0;

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
// Attenuator bits
// 0 - 64dB
// 1 - 16dB
// 2 - 8dB
// 3 - 4dB
// 4 - 64dB
// 5 - 2dB
// 6 - 1dB
// 7 - 32dB
byte num_to_attn[64] = {
  0b00000000,  // 0
  0b01000000,  // 1
  0b00100000,  // 2
  0b01100000,  // 3
  0b00001000,  // 4
  0b01001000,  // 5
  0b00101000,  // 6
  0b01101000,  // 7
  0b00000100,  // 8
  0b01000100,  // 9
  0b00100100,  // 10
  0b01100100,  // 11
  0b00001100,  // 12
  0b01001100,  // 13
  0b00101100,  // 14
  0b01101100,  // 15
  0b00000010,  // 16
  0b01000010,  // 17
  0b00100010,  // 18
  0b01100010,  // 19
  0b00001010,  // 20
  0b01001010,  // 21
  0b00101010,  // 22
  0b01101010,  // 23
  0b00000110,  // 24
  0b01000110,  // 25
  0b00100110,  // 26
  0b01100110,  // 27
  0b00001110,  // 28
  0b01001110,  // 29
  0b00101110,  // 30
  0b01101110,  // 31
  0b10000000,  // 32
  0b11000000,  // 33
  0b10100000,  // 34
  0b11100000,  // 35
  0b10001000,  // 36
  0b11001000,  // 37
  0b10101000,  // 38
  0b11101000,  // 39
  0b10000100,  // 40
  0b11000100,  // 41
  0b10100100,  // 42
  0b11100100,  // 43
  0b10001100,  // 44
  0b11001100,  // 45
  0b10101100,  // 46
  0b11101100,  // 47
  0b10000010,  // 48
  0b11000010,  // 49
  0b10100010,  // 50
  0b11100010,  // 51
  0b10001010,  // 52
  0b11001010,  // 53
  0b10101010,  // 54
  0b11101010,  // 55
  0b10000110,  // 56
  0b11000110,  // 57
  0b10100110,  // 58
  0b11100110,  // 59
  0b10001110,  // 60
  0b11001110,  // 61
  0b10101110,  // 62
  0b11101110,  // 63
};
//====================================================================================
void setup() {
  pinMode(Data, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(Latch, OUTPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  digitalWrite(Latch, LOW);
  Update(Attn);
}
//====================================================================================
void loop() {
   if (digitalRead(Button2) == 0) {
    Attn = ++Attn;
    if (Attn > 127) Attn = 127;
    Update(Attn);
  }

  if (digitalRead(Button1) == 0) {
    Attn = --Attn;
    if (Attn < 0) Attn = 0;
    Update(Attn);
  }
}
//====================================================================================
void Update(int Attn) {
    digitalWrite(Latch, LOW);
    shiftOut(Data, Clock, MSBFIRST, num_to_seven_segment[Attn % 10]);          //ones num
    shiftOut(Data, Clock, MSBFIRST, num_to_seven_segment[(Attn / 10) % 10]);   //tens num
    shiftOut(Data, Clock, MSBFIRST, num_to_seven_segment[(Attn / 100) % 10]);  //hundreds num
    int Setting = num_to_attn[Attn % 64];
    if (Attn >= 64) {
      Setting = Setting | 0b00010001;                 // 64dB attenuator has two bits set
    }
    shiftOut(Data, Clock, MSBFIRST, Setting);         //attenuator setting
    digitalWrite(Latch, HIGH);
    delay(20);
}
