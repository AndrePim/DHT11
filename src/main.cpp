#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h> // Подключение библиотеки датчика DHT

#define DHTPIN 2      // Датчик DHT подключён к пину 2
#define DHTTYPE DHT11 // Определение модели датчика

DHT dht(DHTPIN, DHTTYPE); // Объявление объекта класса DHT; Первый параметр - пин датчика, второй - тип датчика
char percent = '%';       // Объявление знака процента

void setup() {
  Serial.begin(9600);            // Инициализация последовательного соединения и задание скорости передачи данных в бит/с(бод)
  Serial.println("DHT11 Test!"); // Вывод надписи "DHT11 Test!" в монитор последовательного порта
  dht.begin();                   // Запуск датчика DHT11
}

void loop() {
  delay(2000);                         // Задержка 2мс между измерениями
  float h = dht.readHumidity();        // Запись получаемого значения влажности воздуха в переменную
  float t = dht.readTemperature();     // Запись получаемого значения температуры воздуха в переменную (По умолчанию измеряется в Цельсиях)
  float f = dht.readTemperature(true); // Запись получаемого значения температуры воздуха в переменную (Фаренгейт)
  // Проверка полученных значений
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!"); // Вывод сообщение об ошибке
    return;
  }

  float hif = dht.computeHeatIndex(f, h);        // Запись значения индекса жары в переменную (По умолчанию измеряется в Фаренгейтах)
  float hic = dht.computeHeatIndex(t, h, false); // Запись значения индекса жары в переменную (Цельсия)
  
  Serial.print("Humidity: ");
  Serial.print(h);       // Вывод значения переменной h
  Serial.print(percent); // Вывод значения переменной percent
  Serial.print("\t");
  Serial.print("Temperature: ");
  Serial.print(t); // Вывод значения переменной t
  Serial.print(" *C ");
  Serial.print(f); // Вывод значения переменной f
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic); // Вывод значения переменной hic
  Serial.print(" *C ");
  Serial.print(hif); // Вывод значения переменной hif
  Serial.println(" *F");
}