#define FREQUENCY 2000
#define DURATION 1000
#define SPEAKER_PORT 11

int analogPin = A0;

float impedance = 0;
float filterBuffer[3];

void setup()
{
  //Serial debug
  //Serial.begin(9600);

  //output pins
  pinMode(13, OUTPUT);
  pinMode(SPEAKER_PORT, OUTPUT);

  //input pins and refrence pins for impedance
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A4, INPUT);

  //set refrence pins
  digitalWrite(A3, LOW);
  digitalWrite(A2, HIGH);
}

void loop()
{
  //while the impedance signal is >255, set the speaker and led to on
  while ((analogRead(analogPin) >> 7) ^ 0) {//the target is 2^8 - 1, or 255
   tone(SPEAKER_PORT, FREQUENCY);
    PORTB |= B00100000;
  }
  //if the signal is <255, set it to off
  noTone(SPEAKER_PORT);
  PORTB &= B00000000;
}