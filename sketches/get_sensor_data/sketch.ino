#include <Arduino_HTS221.h>   // Temperature sensor
#include <Arduino_LPS22HB.h>  // Air pressure sensor
#include <Arduino_APDS9960.h> // Color, light, and proximity sensor
#include <Arduino_LSM9DS1.h>  // Accelerometer/IMU
#include <PDM.h>

short sampleBuffer[256];

// number of samples read
volatile int samplesRead;

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    if (!HTS.begin())
    {
        Serial.println("Failed to start the HTS221 sensor.");
        while (1);
    }

    if (!BARO.begin())
    {
        Serial.println("Failed to start the LPS22HB sensor.");
        while (1);
    }

    if (!APDS.begin())
    {
        Serial.println("Failed to start the APDS9960 sensor.");
        while (1);
    }

    if (!IMU.begin())
    {
        Serial.println("Failed to start the LSM9DS sensor.");
        while (1);
    }

    // configure the data receive callback
    PDM.onReceive(onPDMdata);

    // optionally set the gain, defaults to 20
    PDM.setGain(10);

    // initialize PDM with:
    // - one channel (mono mode)
    // - a 16 kHz sample rate
    if (!PDM.begin(1, 16000))
    {
        Serial.println("Failed to start PDM!");
        while (1);
    }
}

void loop()
{
    // Read the temperature and humidity values
    float temp = HTS.readTemperature();   // In C
    float humidity = HTS.readHumidity();  // In %
    float pressure = BARO.readPressure(); // In kPa

    while (!APDS.colorAvailable())
    {
        delay(5);
    }

    int r, g, b, a;
    APDS.readColor(r, g, b, a);

    float x, y, z;
    IMU.readAcceleration(x, y, z);

    float xMagnetic, yMagnetic, zMagnetic;
    IMU.readMagneticField(xMagnetic, yMagnetic, zMagnetic); // in uT (micro Tesla).

    // To store sound data
    short soundVal, currentVal;

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
    Serial.print(',');
    Serial.print(xMagnetic);
    Serial.print(',');
    Serial.print(yMagnetic);
    Serial.print(',');
    Serial.print(zMagnetic);
    Serial.print(',');

    if (samplesRead)
    {
        for (int i = 0; i < samplesRead; i++)
        {
            currentVal = sampleBuffer[i];
            if (currentVal >= soundVal)
            {
                soundVal = currentVal;
            }
        }
        Serial.print(soundVal);
        samplesRead = 0;
        currentVal = 0;
        soundVal = 0;
    }
    Serial.println('\n');

    // time in milliseconds
    delay(120000); // 300000
}

void onPDMdata()
{
    // query the number of bytes available
    int bytesAvailable = PDM.available();

    // read into the sample buffer
    PDM.read(sampleBuffer, bytesAvailable);

    // 16-bit, 2 bytes per sample
    samplesRead = bytesAvailable / 2;
}
