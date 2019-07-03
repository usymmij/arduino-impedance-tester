#define FREQUENCY 2000
#define SPEAKER_PORT 11

int analogPin = A0;

float impedance = 0;
boolean filterBuffer[30];
boolean beep = false;

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

  for(int i = 0; i < 30; i++){
    filterBuffer[i] = false;
  }
}

void loop()
{
  beep = false;
  filterBuffer[0] = ((analogRead(analogPin) >> 7) ^ 0);//the target is 2^88 - 1, or 255
  for(int i = 19; i > 0; i--) {
    filterBuffer[i] = filterBuffer[i - 1];
    if(filterBuffer[i-1]) beep = true;
  }
  if (beep) {
   tone(SPEAKER_PORT, FREQUENCY);
    PORTB |= B00100000;
    delay(5);
  } else {
  noTone(SPEAKER_PORT);
  PORTB &= B00000000;
  }
}
