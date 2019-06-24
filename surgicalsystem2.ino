#define FREQUENCY 440
#define DURATION 1000
#define speakerPort 11

String old = "";
int mode = 2;
int analogPin = A0;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 4700;
float R2 = 0;
float buffer = 0;

//variables from processing
float globalTotal = 0;//original proccessing code had bad naming practice
float target = 100.0;
int samples=0;
float filterdat[5];

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  for (int i = 14; i < 53; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  pinMode(A0, INPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  pinMode(A4, INPUT);
}

void loop()
{

  if (Serial.available() > 0)
  {
    mode = 1;
  }

  if (mode == 1)
  {
    String output = "";
    for (int i = 14; i < 53; i++)
    {
      if (digitalRead(i) == LOW)
      { //input has been pulled down
        output = output + (i - 13) + " ";
      }
    }
  }
  else if (mode == 2)
  {
    raw = analogRead(analogPin);

    buffer = raw * 5;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;
    int returned = analogRead(A3);
    //Serial.print(R2, DEC);
    //Serial.print(",");
    //Serial.print(raw, DEC);
    //Serial.print(",");
    //Serial.print(returned, DEC);
    //Serial.println("v");
  }
  //inject processing code
  float valueOne = maFilter((float)raw);//rvalue
  float valueTwo = (float)raw;//rvalue2
  Serial.println(valueOne);
  char status = '0';
  if (samples < 10) {
    globalTotal = globalTotal + valueOne;
    samples++;
    status = '1';
  }  else
  {
    target = (globalTotal / samples) + 200;
    status = '2';
    valueOne = map(valueOne, 0, 1005, 0, 1015);
    //the speaker draws out some of the current, so a simple software amplifier is added
    if (valueOne >= target)
    {
      tone(speakerPort, 440);
      digitalWrite(13, HIGH);
    } else {
      noTone(speakerPort);
      digitalWrite(13, LOW);
    }
  }
}

float maFilter(float data) {
  double total = 0;
  for (int i = 2; i < 5; i++)
  {
    filterdat[i - 1] = filterdat[i];
    total = total + filterdat[i];
  }
  total = total / 3;
  filterdat[4] = data;
  return (float)total;
}
