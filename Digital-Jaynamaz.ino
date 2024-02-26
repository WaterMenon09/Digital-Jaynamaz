#define PIR_Sensor_1 1
#define PIR_Sensor_2 2
#define triggerSONAR1 3
#define echoSONAR1 4
#define triggerSONAR2 5
#define echoSONAR2 6
#define triggerSONAR3 7
#define echoSONAR3 8
#define buzzer 9


float duration;
short int distance;

void setup()
{
  pinMode(PIR_Sensor_1, INPUT);
  pinMode(PIR_Sensor_2, INPUT);
  pinMode(triggerSONAR1, OUTPUT);
  pinMode(triggerSONAR2, OUTPUT);
  pinMode(triggerSONAR3, OUTPUT);
  pinMode(echoSONAR1, INPUT);
  pinMode(echoSONAR2, INPUT);
  pinMode(echoSONAR3, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

short int state = 1;
short int rakats = 4; // take input

void loop()

{
  // ruku();
  // Serial.print(" Ruku: ");
  // Serial.print(ruku());
  // Serial.print(" Sizdah: ");
  // Serial.print(sizdah());
  // Serial.print(" Sit: ");
  // Serial.print(sitting());
  // Serial.print(" Standing: ");
  // Serial.println(standing());
  Serial.print(" State: ");
  Serial.println(state);



  if (state == 1 || state == 7 ||
      state == 14 || state == 20)

  {
    if (sizdah())
      error();
    if (ruku())
    {
      delay(1000);
      if (ruku())
      {
        state++;
        Serial.println(state);

      }
    }

    if (sitting())
      error();
  }

  if (state == 2 || state == 8 ||
      state == 15 || state == 21)

  {
    if (sizdah())
      error();
    if (standing())
    {
      if (standing())
        {state++;
          Serial.println(state);
        }
    }
    if (sitting()) {
      delay(500);
      if (sitting()) {
      error();
      }
    }
  }

  if (state == 3 || state == 9 ||
      state == 16 || state == 22)

  {
    if (!standing())
    {
      delay(3500);
      if (sizdah())
      {
        state++;
        Serial.println(state);

      }

      else
      {
        error();
      }
    }
  }

  if (state == 4 || state == 10 ||
      state == 12 || state == 17 ||
      state == 23 || state == 25)

  {
    if (standing())
    {
      delay(1000);
      if (standing()) {
        error();
      }
        
    }
    if (sitting())
    {
      delay(1000);
      if (!sizdah())
        {
          delay(500);
          state++;
          Serial.println(state);

        }
    };
  }

  if (state == 5 || state == 11 ||
      state == 18 || state == 24)

  {
    if (sizdah())
      {
      delay(500);
      state++;
      Serial.println(state);
      }
    if (standing())
    {
      delay(2000);
      if (standing()) {
        error();}
    }
  }

  if (state == 6 || (state == 19 && rakats != 3))
  {
    if (sitting() && !sizdah())
    {
      delay(2500);
      if (sitting() && !sizdah()) {
        error();}
        
    }
    if (standing())
    {
      delay(1000);
      if (standing())
        {
          delay(500);
          state++;
          Serial.println(state);
          }
    };
  }

  if (state == 13 && rakats == 2)
    state = 26;
  if (state == 19 and rakats == 3)
  {
    if (sitting())
      state = 26;
    if (ruku())
    {
      if (!sitting())
        error();
    }
    if (standing())
      error();
  }
  if (state == 26)
  {
    delay(15000);
    if (sizdah())
      error();
    if (ruku())
    {
      if (!sizdah())
        error();
    }
    if (standing())
      error();
  }
}

boolean sizdah(short int throwaway_int) // Overloaded function. Pass in a garbage short int if you want to use pir sensor to detect

{
  short int sensor1Value = digitalRead(PIR_Sensor_1);
  short int sensor2Value = digitalRead(PIR_Sensor_2);
  short int Detect1 = 0;
  short int Detect2 = 0;

  if (sensor1Value)
  {
    Detect1 = 1;
  }

  if (sensor2Value)
  {
    Detect2 = 1;
  }

  if (sensor1Value)
  {
    Detect1 = 1;
  }

  if (Detect1 == 1 && Detect2 == 1)
  {
    return true;
  }

  return false;

  delay(100);
}

boolean sizdah() // Overloaded function. This one uses SONAR

{
  boolean sizdah = true;
  for (int i = 1; i <= 6; i++)
  {
    digitalWrite(triggerSONAR1, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerSONAR1, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerSONAR1, LOW);
    duration = pulseIn(echoSONAR1, HIGH);
    distance = duration * 0.034 / 2;

    delay(10);

    if ((distance >= 10))
    {
      sizdah = false;
    }
  }

  Serial.print(" Sizdah: ");

  Serial.print(distance);

  // Serial.print("Sizdah: ");
  // Serial.print(sizdah);
  // Serial.print(" ");

  return sizdah;
}

boolean ruku()

{

  boolean ruku = false;
  for (int i = 1; i <= 3; i++)
  {
    digitalWrite(triggerSONAR2, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerSONAR2, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerSONAR2, LOW);
    duration = pulseIn(echoSONAR2, HIGH);
    distance = duration * 0.034 / 2;

    delay(100);

    if (distance < 120)
    {
      ruku = true;
    }
  }
  Serial.print(" Ruku: ");

  Serial.print(distance);
  // Serial.print("Ruku: ");
  // Serial.print(ruku);
  // Serial.print(" ");

  return ruku;
}

boolean sitting()
{
  boolean sitting = true;
  for (int i = 1; i <= 3; i++)
  {
    digitalWrite(triggerSONAR3, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerSONAR3, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerSONAR3, LOW);
    duration = pulseIn(echoSONAR3, HIGH);
    distance = duration * 0.034 / 2;

    delay(10);

    if (distance >= 10)
    {
      sitting = false;
    }
  }
  Serial.print(" Sitting: ");

  Serial.println(distance);
  // Serial.print("Sitting: ");
  // Serial.print(sitting);
  // Serial.print(" ");

  return sitting;
}

boolean standing()
{
  if (!ruku() && !sitting() && !sizdah())
    return true;
  return false;
}

void error()
{
  // Play sound
  Serial.println("You've made an error!");
  tone(buzzer, 440);
  delay(1500);
  noTone(buzzer);
  delay(3000);
}
