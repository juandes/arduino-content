#include <Arduino_HTS221.h> // Temperature sensor
#include <Arduino_LPS22HB.h> // Air pressure sensor
#include <Arduino_APDS9960.h> // Color, light, and proximity sensor
#include <Arduino_LSM9DS1.h> // Accelerometer

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!HTS.begin()){
    Serial.println("Failed to start the HTS221 sensor.");
    while(1);
  }

  if (!BARO.begin()) {
    Serial.println("Failed to start the LPS22HB sensor.");
    while (1);
  }

  if (!APDS.begin()) {
    Serial.println("Failed to start the APDS9960 sensor.");
    while (1);
  }

  if (!IMU.begin()) {
    Serial.println("Failed to start the LSM9DS sensor.");
    while (1);
  }

}

void loop() {
  // Read the temperature and humidity values
  float temp = HTS.readTemperature(); // In C
  float humidity = HTS.readHumidity(); // In %
  float pressure = BARO.readPressure(); // In kPa

  int r, g, b, a;
  APDS.readColor(r, g, b, a);

  float x, y, z;
  IMU.readAcceleration(x, y, z);

  while (!APDS.colorAvailable() || !APDS.proximityAvailable())
  {
  }

  Serial.print(temp); 
  Serial.print(',');
  Serial.print(humidity); 
  Serial.print(',');
  Serial.print(pressure);
  Serial.print(',');
  Serial.print(r);
  Serial.print(',');
  Serial.print(b);
  Serial.print(',');
  Serial.print(g);
  Serial.print(',');
  Serial.print(a);
  Serial.print(',');
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.print(z);
  // Use Serial.println(); to add a linebreak


  // 10 mins
  delay(600000);
}
