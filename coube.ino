#define NUM_LEDS 8

#define PIN_1 3
#define PIN_2 5
#define PIN_3 6
#define PIN_4 9
#define PIN_5_GROUNDED 10
#define PIN_6_GROUNDED 11

bool stateLeds[] = {0, 0, 0, 0, 0, 0, 0, 0};  // Состояние каждого светодиода (вкл или выкл)

int schemeLeds[8][2] = {{PIN_4, PIN_6_GROUNDED},  // Пины, которые нужно дернуть для определённого светоиода
  {PIN_4, PIN_5_GROUNDED},
  {PIN_3, PIN_6_GROUNDED},
  {PIN_3, PIN_5_GROUNDED},
  {PIN_2, PIN_6_GROUNDED},
  {PIN_2, PIN_5_GROUNDED},
  {PIN_1, PIN_6_GROUNDED},
  {PIN_1, PIN_5_GROUNDED}
};

int temp_led = 0;  // временное хранение при вводе

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_5_GROUNDED, OUTPUT);
  pinMode(PIN_6_GROUNDED, OUTPUT);

  off_all();
}

bool changed = false;

void loop()
{
  if (Serial.available())
  {
    temp_led = Serial.read();
    temp_led = temp_led - '0' - 1;  // перевод ascii в цифру и потом в индекс
    if (temp_led >= 0)  // отброс плохих значений (плохой индекс или некорректный символ)
    {
      Serial.println(temp_led);
      stateLeds[temp_led] = !stateLeds[temp_led];  // переключаем светодиод
      changed = true;  // флаг о том что был ввод
    }
  }
  
  if (changed) {  // Если состояния поменялись, сброс (нужно при выключении последнего светодиода)
    off_all();
  }

  for (int8_t i = 0; i < NUM_LEDS; i++) {
    if (stateLeds[i]) {
      turnLed(i);
      delay(1);
    }
  }

  changed = false;
}

void off_all()
{
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, LOW);
  digitalWrite(PIN_5_GROUNDED, LOW);
  digitalWrite(PIN_6_GROUNDED, LOW);
}

void turnLed(const int8_t& led)
{
  static uint8_t lastLed = -1;
  if (lastLed != led && lastLed != -1) {  // отключение пред светодиода
    digitalWrite(schemeLeds[lastLed][0], LOW);  // сначала убираем питание (светодиод доедает и не оставляет другому, который посстояно зажигался)
    //delayMicroseconds(200);)  // ждать не пришлось
    digitalWrite(schemeLeds[lastLed][1], LOW);  // теперь можно поставить землю другому светодиоду
  }

  lastLed = led;

  digitalWrite(schemeLeds[led][1], HIGH);  // сначала напряжение на пин grounded, чтобы другой светодиод вообще не зажигался
  digitalWrite(schemeLeds[led][0], HIGH);  // питание на нужный светодиод
}
