#include <Arduino.h>

#define pinSensorHall 8
#define pinRele 10

const int BOBINAS = 4;
const int ESPIRAS_PRIMARIO = 5;
const int ESPIRAS_SECUNDARIO = 5;

int bobina = 0;
int contadorGiros = 0;
bool sensorDesativado = false;
bool bobinandoPrimario = true;

void setup()
{
  pinMode(pinSensorHall, INPUT_PULLUP);
  pinMode(pinRele, OUTPUT);
  Serial.begin(9600);
  Serial.println("Iniciando bobinagem...");
}

void loop()
{
  bool sensorHall = !digitalRead(pinSensorHall);

  if (sensorHall && !sensorDesativado && bobina < BOBINAS)
  {
    digitalWrite(pinRele, HIGH);
    contadorGiros++;
    Serial.print("Espira ");
    Serial.print(contadorGiros);
    Serial.println(bobinandoPrimario ? " do primário" : " do Secundário");

    if (bobinandoPrimario && contadorGiros >= ESPIRAS_PRIMARIO)
    {
      contadorGiros = 0;
      bobinandoPrimario = false;
      Serial.println("Bobina do primário concluída.");
      digitalWrite(pinRele, LOW);
      delay(5000);
    }
    else if (!bobinandoPrimario && contadorGiros >= ESPIRAS_SECUNDARIO)
    {
      digitalWrite(pinRele, HIGH);
      contadorGiros = 0;
      bobinandoPrimario = true;
      bobina++;
      Serial.print("Bobina ");
      Serial.print(bobina);
      Serial.println(" concluída.");
    }

    if (bobina >= BOBINAS)
    {
      Serial.println("Bobinas concluídas.");
      digitalWrite(pinRele, LOW);
      while (true)
        ;
    }
  }

  sensorDesativado = sensorHall;
}