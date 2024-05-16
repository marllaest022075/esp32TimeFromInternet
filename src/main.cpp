
#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <Constantes.h>


void setTimezone(String timezone)
{
  Serial.printf("  Setting Timezone to %s\n", timezone.c_str());
  setenv("TZ", timezone.c_str(), 1); //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void initTime(String timezone)
{
  struct tm timeinfo;

  Serial.println("Setting up time");
  configTime(0, 0, "pool.ntp.org"); // First connect to NTP server, with 0 TZ offset
  while (!getLocalTime(&timeinfo))
  {

    Serial.println("  Failed to obtain time");
    delay(1000);
  }

  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time 1");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S zone %Z %z ");
}

void startWifi()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting Wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Wifi RSSI=");
  Serial.println(WiFi.RSSI());
}

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  startWifi();
  initTime("MST7"); // Cd Obregon
}

void loop()
{

  printLocalTime();
  delay(1000);
}