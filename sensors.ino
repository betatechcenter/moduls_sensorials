#include "Arduino_HS300x.h"  // Biblioteca per a HS3003 (temperatura i humitat)

// Pins per als sensors analògics
const int NH3Pin = A0;    // Pin analògic per NH3
const int H2SPin = A1;    // Pin analògic per H2S
const int CO2Pin = A2;    // Pin analògic per CO2

// Variables per emmagatzemar les lectures dels sensors
float nh3Value;
float h2sValue;
float co2Value;
float temperature;
float humidity;

// Funció per convertir la lectura analògica en mA
float convertToMilliAmps(int sensorValue) {
    return 4 + (sensorValue * (16.0 / 1023.0));  // Converteix la lectura analògica (0-1023) a un rang de 4-20 mA
}

// Funcions per calcular les concentracions en ppm
float calculateNH3(float I) {
    return 6.25 * (I - 4); // Converteix mA a ppm per NH3
}

float calculateH2S(float I) {
    return 12.5 * (I - 4); // Converteix mA a ppm per H2S
}

float calculateCO2(float I) {
    return 312.5 * (I - 4); // Converteix mA a ppm per CO2
}

// Setup inicial
void setup() {
    Serial.begin(9600);  // Inicia la comunicació serial a 9600 bps
    HS300x.begin();  // Inicialitza el sensor HS3003 (temperatura i humitat)

    pinMode(NH3Pin, INPUT); // Configura el pin per NH3 com entrada
    pinMode(H2SPin, INPUT);  // Configura el pin per H2S com entrada
    pinMode(CO2Pin, INPUT);  // Configura el pin per CO2 com entrada
}

// Bucle principal per llegir els sensors
void loop() {
    // Llegeix els valors dels sensors analògics
    nh3Value = analogRead(NH3Pin);  // Llegeix NH3
    h2sValue = analogRead(H2SPin);   // Llegeix H2S
    co2Value = analogRead(CO2Pin);   // Llegeix CO2

    // Converteix les lectures a mA
    float nh3Current = convertToMilliAmps(nh3Value);
    float h2sCurrent = convertToMilliAmps(h2sValue);
    float co2Current = convertToMilliAmps(co2Value);

    // Llegeix temperatura i humitat del sensor HS3003
    temperature = HS300x.readTemperature();
    humidity = HS300x.readHumidity();

    // Converteix les lectures a concentracions utilitzant les funcions
    float nh3Concentration = calculateNH3(nh3Current); // NH3 en ppm
    float h2sConcentration = calculateH2S(h2sCurrent);  // H2S en ppm
    float co2Concentration = calculateCO2(co2Current);   // CO2 en ppm

    // Envia les dades a través de la interfície serial (format CSV)
    Serial.print(nh3Concentration);
    Serial.print(",");
    Serial.print(h2sConcentration);
    Serial.print(",");
    Serial.print(co2Concentration);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(humidity);

    delay(2000);  // Espera 2 segons abans de la següent lectura
}
