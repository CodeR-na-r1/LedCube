#define NUM_LEDS 8
#define NUM_PINS 6
#define NUM_STATES 2

#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define PIN_5 6
#define PIN_6 7

bool stateLeds[] = {0, 0, 0, 0, 0, 0, 0, 0};

int schemeLeds[8][2] = {{5, 7},
  {5, 6},
  {4, 7},
  {4, 6},
  {3, 7},
  {3, 6},
  {2, 7},
  {2, 6}
};

int temp_led = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_6, OUTPUT);

  off_all();
}

void loop()
{
  if (Serial.available())
  {
    temp_led = Serial.read();
    temp_led = temp_led - '0' - 1;
    if (temp_led >= 0)
    {
      Serial.println(temp_led);
      stateLeds[temp_led] = !stateLeds[temp_led];
    }
  }

  for (int i(0); i < NUM_LEDS; ++i)
  {
    if (stateLeds[i]){
      switchLed(i);
      delay(1);
      switchLed(i);
    }
  }
}

void off_all()
{
  for (int i = 2; i < 8; i++)
  {
    digitalWrite(i, LOW);
  }
}

void switchLed(const int led)
{
  for (int i = 0; i < NUM_STATES; i++)
  {
    //Serial.println(schemeLeds[i]);
    digitalWrite(schemeLeds[led][i], !digitalRead(schemeLeds[led][i]));
  }
}
