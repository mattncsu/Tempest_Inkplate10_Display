#include <WiFi.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "Inkplate.h"            //Include Inkplate library to the sketch

#include "images.h"
#include <TimeLib.h>
#include <time.h>

Inkplate display(INKPLATE_1BIT); // Create an object on Inkplate library and also set library into 3-bit mode (BW)

const char * ssid = "ssid";
const char * password = "password";
const char * ntpServer = "time.gov;

const int timeZone = -4;  // Eastern Standard Time (USA)
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 3600;

void setTimezone(String timezone){
  Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void initTime(String timezone){
  struct tm timeinfo;

  Serial.println("Setting up time");
  configTime(0, 0, ntpServer);    // First connect to NTP server, with 0 TZ offset
  if(!getLocalTime(&timeinfo)){
    Serial.println("  Failed to obtain time");
    return;
  }
  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);
}
void setTime(int yr, int month, int mday, int hr, int minute, int sec, int isDst){
  struct tm tm;

  tm.tm_year = yr - 1900;   // Set date
  tm.tm_mon = month-1;
  tm.tm_mday = mday;
  tm.tm_hour = hr;      // Set time
  tm.tm_min = minute;
  tm.tm_sec = sec;
  tm.tm_isdst = isDst;  // 1 or 0
  time_t t = mktime(&tm);
  Serial.printf("Setting time: %s", asctime(&tm));
  struct timeval now = { .tv_sec = t };
  settimeofday(&now, NULL);
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time 1");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S zone %Z %z ");
}

AsyncUDP udp;




const char* forecastURL = "https://swd.weatherflow.com/swd/rest/better_forecast?station_id=<ID>&units_temp=f&units_wind=mph&units_pressure=inhg&units_precip=in&units_distance=mi&token=<token>";

const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"xxxxxx" \
"-----END CERTIFICATE-----\n";


const int port = 50222;
bool hardwareInfo = false;

struct SpiRamAllocator {
  void* allocate(size_t size) {
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
  }

  void deallocate(void* pointer) {
    heap_caps_free(pointer);
  }

  void* reallocate(void* ptr, size_t new_size) {
    return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);
  }
};

using SpiRamJsonDocument = BasicJsonDocument<SpiRamAllocator>;

struct weather { //holds all the data received from the UDP broadcasts
  unsigned int rain_start; //rain start-time epoch seconds
  unsigned int strike_time; //lightning strike - time epoch seconds
  uint8_t strike_dist; //km
  uint16_t strike_energy; //unknown unit
  unsigned int rapid_time; //epoch seconds
  float rapid_speed; //rapid wind m/s
  uint16_t rapid_dir; //degrees
  unsigned int obs_air_time; //epoch seconds
  float press; //MB
  float temp; //C
  uint8_t rh; //%
  uint8_t strike_count;
  uint8_t strike_avg_dist; //km
  float battery; //Volts
  unsigned long obs_sky_time; //epoch seconds
  uint16_t illum; //lux
  uint8_t UV; //index
  uint8_t rain_min; //rain over prev minute mm
  uint8_t wind_lull; //m/s
  uint8_t wind_avg; //m/s
  uint8_t wind_gust; //m/s  
  uint8_t wind_dir; //degrees
  uint16_t solar; //W/m^2
  uint16_t daily_rain; //mm
  uint8_t precip_type; //0=none, 1 = rain, 2=hail
  uint8_t wind_int; //wind sample interval, seconds
  unsigned long obs_st_time; //epoch seconds
  int8_t rssi;  
  int8_t hub_rssi;
} wx;


struct current_conditions{
//next block stores all the weather data received from the API
  long current_conditions_time; // 1677814324
  const char *current_conditions_conditions; // "Clear"
  const char *current_conditions_icon; // "clear-night"
  int8_t current_conditions_air_temperature; // 38
  float current_conditions_sea_level_pressure; // 24.826
  float current_conditions_station_pressure; // 23.745
  const char *current_conditions_pressure_trend; // "steady"
  int current_conditions_relative_humidity; // 81
  int current_conditions_wind_avg; // 2
  int current_conditions_wind_direction; // 4
  const char *current_conditions_wind_direction_cardinal;
  int current_conditions_wind_gust; // 5
  int current_conditions_solar_radiation; // 0
  int current_conditions_uv; // 0
  int current_conditions_brightness; // 2
  int8_t current_conditions_feels_like; // 38
  int8_t current_conditions_dew_point; // 33
  int8_t current_conditions_wet_bulb_temperature; // 35
  int8_t current_conditions_wet_bulb_globe_temperature;
  int8_t current_conditions_delta_t; // 3
  float current_conditions_air_density; // 1.01
  uint8_t current_conditions_lightning_strike_count_last_1hr;
  uint8_t current_conditions_lightning_strike_count_last_3hr;
  uint8_t current_conditions_lightning_strike_last_distance;
  const char *current_conditions_lightning_strike_last_distance_msg;
  long current_conditions_lightning_strike_last_epoch;
  float current_conditions_precip_accum_local_day; // 0.01
  float current_conditions_precip_accum_local_yesterday;
  uint8_t current_conditions_precip_minutes_local_day; // 21
  uint8_t current_conditions_precip_minutes_local_yesterday;
  bool current_conditions_is_precip_local_day_rain_check;
  bool current_conditions_is_precip_local_yesterday_rain_check;
} cc;


struct daily_forecast{
  long forecast_daily_item_day_start_local; // 1677733200, ...
  uint8_t forecast_daily_item_day_num; // 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
  uint8_t forecast_daily_item_month_num; // 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
  const char* forecast_daily_item_conditions; // "Partly Cloudy", ...
  const char* forecast_daily_item_icon; // "partly-cloudy-night", "rainy", ...
  long forecast_daily_item_sunrise; // 1677757897, 1677844206, ...
  long forecast_daily_item_sunset; // 1677798677, 1677885143, 1677971610, ...
  int8_t forecast_daily_item_air_temp_high; // 61, 46, 48, 54, 63, 54, ...
  int8_t forecast_daily_item_air_temp_low; // 37, 36, 37, 34, 32, 36, ...
  uint8_t forecast_daily_item_precip_probability; // 0, 100, 90, ...
  const char* forecast_daily_item_precip_icon; // "chance-rain", ...
  const char* forecast_daily_item_precip_type; // "rain", "rain", ...
} daily[5];

struct hourly_forecast{
  long forecast_hourly_item_time; // 1677816000, 1677819600, 1677823200, ...
  const char* forecast_hourly_item_conditions; // "Partly Cloudy", ...
  const char* forecast_hourly_item_icon; // "partly-cloudy-night", ...
  int8_t forecast_hourly_item_air_temperature; // 38, 38, 38, 37, ...
  float forecast_hourly_item_sea_level_pressure; // 29.976, ...
  uint8_t forecast_hourly_item_relative_humidity; // 63, 64, 62, ...
  float forecast_hourly_item_precip; // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ...
  uint8_t forecast_hourly_item_precip_probability; // 0, 0, 5, 5, ...
  const char* forecast_hourly_item_precip_type; // "rain", "rain", ...
  const char* forecast_hourly_item_precip_icon; // "chance-rain", ...
  uint8_t forecast_hourly_item_wind_avg; // 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, ...
  uint16_t forecast_hourly_item_wind_direction; // 18, 36, 54, 56, 68, ...
  const char* forecast_hourly_item_wind_direction_cardinal;
  uint8_t forecast_hourly_item_wind_gust; // 5, 5, 5, 5, 5, 5, 5, 8, 8, 8, ...
  uint8_t forecast_hourly_item_uv; // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, ...
  uint8_t forecast_hourly_item_feels_like; // 35, 34, 35, 33, 33, 33, 33, ...
  uint8_t forecast_hourly_item_local_hour; // 23, 0, 1, 2, 3, 4, 5, 6, 7, ...
  uint8_t forecast_hourly_item_local_day; // 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, ...  
} hourly[10];

//static nvs_handle wf_nvs;
size_t len;


void connectUDPReceiver()
{
  if (udp.listen(port))
  {
    udp.onPacket([](AsyncUDPPacket packet) {
      StaticJsonDocument<384> doc_UDP;
      // SpiRamJsonDocument doc_UDP(512);
      DeserializationError error = deserializeJson(doc_UDP, packet.data(), packet.length());

      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        //Serial.println(error.f_str());
        return;
      }
      const char *type = doc_UDP["type"];

      if (strcmp(type, "obs_st") == 0)
      {

        JsonArray obs = doc_UDP["obs"][0];
        wx.obs_st_time = obs[0];
        wx.wind_lull = obs[1];
        wx.wind_avg = obs[2];
        wx.wind_gust = obs[3];
        wx.wind_dir = obs[4];
        wx.wind_int = obs[5];
        wx.press = obs[6];
        wx.temp = obs[7];
        wx.rh = obs[8];
        wx.illum = obs[9];
        wx.UV = obs[10];
        wx.solar = obs[11];
        wx.rain_min = obs[12];
        wx.precip_type = obs[13];
        wx.strike_avg_dist = obs[14];
        wx.strike_count = obs[15];
        wx.battery = obs[16];        

        Serial.print("obs_st received:");
        Serial.println(obs);
        Serial.print("Temperature: ");
        Serial.print(wx.temp);
        Serial.print(" Humidity: ");
        Serial.println(wx.rh);
        Serial.print("Wind: "); Serial.print(wx.wind_avg); Serial.print(" Gust: ");
        Serial.print(wx.wind_gust); Serial.print(" @ "); Serial.print(wx.wind_dir);
        Serial.println(" degreees");
        Serial.print(" Lux: "); Serial.print(wx.illum);
        Serial.print(" Solar: "); Serial.print(wx.solar); Serial.println(" W/m^2");
      }

      if (strcmp(type, "obs_air") == 0)
      {

        JsonArray obs1 = doc_UDP["obs"][0];
        wx.obs_air_time = obs1[0];
        wx.press = obs1[1];
        wx.temp = obs1[2];
        wx.rh = obs1[3];
        wx.strike_count = obs1[4];
        wx.strike_dist = obs1[5];
        wx.battery = obs1[6];
        
        Serial.print("obs_air received:");
        Serial.println(obs1);
      }

      if (strcmp(type, "obs_sky") == 0)
      {

        JsonArray obs2 = doc_UDP["obs"][0];
        wx.obs_air_time = obs2[0];
        wx.illum = obs2[1];
        wx.UV= obs2[2];
        wx.rain_min = obs2[3];
        wx.wind_lull = obs2[4];
        wx.wind_avg = obs2[5];
        wx.wind_gust = obs2[6];
        wx.wind_dir = obs2[7];
        wx.battery = obs2[8];
        wx.solar = obs2[10];
        wx.daily_rain = obs2[11];
        wx.precip_type = obs2[12];
        wx.wind_int = obs2[13];
       
       Serial.print("obs_sky received: ");
       Serial.println(obs2);

      }

      if (strcmp(type, "rapid_wind") == 0)
      {
        JsonArray ob = doc_UDP["ob"];
        wx.rapid_time = ob[0];
        wx.rapid_speed = ob[1];
        wx.rapid_dir = ob[2];

        Serial.print("Wind "); Serial.print(wx.rapid_speed*2.23); Serial.print("mph at ");
        Serial.print(wx.rapid_dir); Serial.println(" degrees.");
      }

      if (strcmp(type, "evt_strike") == 0)
      {
        JsonArray ob1 = doc_UDP["evt"];
        wx.strike_time = ob1[0];
        wx.strike_dist = ob1[1];
        wx.strike_energy = ob1[2];
        Serial.print("lightning "); Serial.print(wx.strike_dist);Serial.println(" km away.");
      }

      if (strcmp(type, "evt_precip") == 0)
      {
        JsonArray ob2 = doc_UDP["evt"];
        wx.rain_start = ob2[0];
        Serial.println("rain");
      }

      if (strcmp(type, "device_status") == 0)
      {
        JsonArray ob3 = doc_UDP["rssi"];
        wx.rssi = ob3[0];
        JsonArray ob4 = doc_UDP["hub_rssi"];
        wx.hub_rssi = ob4[0];
        Serial.println("evt_status received");

      }
    });
  }
}



void getForecast(){
  if(WiFi.status()== WL_CONNECTED){
    Serial.print("fetching: ");Serial.println(forecastURL);
    //String forecast = httpGETRequest(forecastURL);
    //Serial.println(forecast);
    // char* input;

    HTTPClient http;
    http.useHTTP10(true);
    http.begin(forecastURL, root_ca);
    http.GET();

    //DynamicJsonDocument doc(100000);
    SpiRamJsonDocument doc(100000);


  Serial.println(F("---starting deserialization"));
  DeserializationError error = deserializeJson(doc, http.getStream());
  // Disconnect
  http.end();



    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    Serial.println("Parsing current conditions...");
    JsonObject current_conditions = doc["current_conditions"];
    cc.current_conditions_time = current_conditions["time"]; // 1677814324
    cc.current_conditions_time += timeZone * 60 * 60;
    cc.current_conditions_conditions = current_conditions["conditions"]; // "Clear"
    cc.current_conditions_icon = current_conditions["icon"]; // "clear-night"
    cc.current_conditions_air_temperature = current_conditions["air_temperature"]; // 38
    cc.current_conditions_sea_level_pressure = current_conditions["sea_level_pressure"]; // 24.826
    cc.current_conditions_station_pressure = current_conditions["station_pressure"]; // 23.745
    cc.current_conditions_pressure_trend = current_conditions["pressure_trend"]; // "steady"
    cc.current_conditions_relative_humidity = current_conditions["relative_humidity"]; // 81
    cc.current_conditions_wind_avg = current_conditions["wind_avg"]; // 2
    cc.current_conditions_wind_direction = current_conditions["wind_direction"]; // 4
    cc.current_conditions_wind_direction_cardinal = current_conditions["wind_direction_cardinal"];
    cc.current_conditions_wind_gust = current_conditions["wind_gust"]; // 5
    cc.current_conditions_solar_radiation = current_conditions["solar_radiation"]; // 0
    cc.current_conditions_uv = current_conditions["uv"]; // 0
    cc.current_conditions_brightness = current_conditions["brightness"]; // 2
    cc.current_conditions_feels_like = current_conditions["feels_like"]; // 38
    cc.current_conditions_dew_point = current_conditions["dew_point"]; // 33
    cc.current_conditions_wet_bulb_temperature = current_conditions["wet_bulb_temperature"]; // 35
    cc.current_conditions_wet_bulb_globe_temperature = current_conditions["wet_bulb_globe_temperature"];
    cc.current_conditions_delta_t = current_conditions["delta_t"]; // 3
    cc.current_conditions_air_density = current_conditions["air_density"]; // 1.01
    cc.current_conditions_lightning_strike_count_last_1hr = current_conditions["lightning_strike_count_last_1hr"];
    cc.current_conditions_lightning_strike_count_last_3hr = current_conditions["lightning_strike_count_last_3hr"];
    cc.current_conditions_lightning_strike_last_distance = current_conditions["lightning_strike_last_distance"];
    cc.current_conditions_lightning_strike_last_distance_msg = current_conditions["lightning_strike_last_distance_msg"];
    cc.current_conditions_lightning_strike_last_epoch = current_conditions["lightning_strike_last_epoch"];
    cc.current_conditions_precip_accum_local_day = current_conditions["precip_accum_local_day"]; // 0.01
    cc.current_conditions_precip_accum_local_yesterday = current_conditions["precip_accum_local_yesterday"];
    cc.current_conditions_precip_minutes_local_day = current_conditions["precip_minutes_local_day"]; // 21
    cc.current_conditions_precip_minutes_local_yesterday = current_conditions["precip_minutes_local_yesterday"];
    cc.current_conditions_is_precip_local_day_rain_check = current_conditions["is_precip_local_day_rain_check"];
    cc.current_conditions_is_precip_local_yesterday_rain_check = current_conditions["is_precip_local_yesterday_rain_check"];
    Serial.println("Done with current conditions.");
    Serial.println(cc.current_conditions_conditions);
    Serial.println();
    Serial.println("parsing daily forecast");

    uint8_t x = 0;
    for (JsonObject forecast_daily_item : doc["forecast"]["daily"].as<JsonArray>()) {
      if (x > 4){break;}
      daily[x].forecast_daily_item_day_start_local = forecast_daily_item["day_start_local"]; // 1677733200, ...
      daily[x].forecast_daily_item_day_start_local += timeZone * 60 * 60;
      daily[x].forecast_daily_item_day_num = forecast_daily_item["day_num"]; // 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
      daily[x].forecast_daily_item_month_num = forecast_daily_item["month_num"]; // 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
      daily[x].forecast_daily_item_conditions = forecast_daily_item["conditions"]; // "Partly Cloudy", ...
      daily[x].forecast_daily_item_icon = forecast_daily_item["icon"]; // "partly-cloudy-night", "rainy", ...
      Serial.print("x:");Serial.println(x);
      Serial.println(daily[x].forecast_daily_item_day_num);
      Serial.println(daily[x].forecast_daily_item_conditions);
      Serial.println(daily[x].forecast_daily_item_icon);
      Serial.println("---");
      // Serial.println(forecast_daily_item["icon"]);
      daily[x].forecast_daily_item_sunrise = forecast_daily_item["sunrise"];
      daily[x].forecast_daily_item_sunrise +=  timeZone * 60 * 60; // 1677757897, 1677844206, ...
      daily[x].forecast_daily_item_sunset = forecast_daily_item["sunset"];
      daily[x].forecast_daily_item_sunset += timeZone * 60 * 60; // 1677798677, 1677885143, 1677971610, ...
      daily[x].forecast_daily_item_air_temp_high = forecast_daily_item["air_temp_high"]; // 61, 46, 48, 54, 63, 54, ...
      daily[x].forecast_daily_item_air_temp_low = forecast_daily_item["air_temp_low"]; // 37, 36, 37, 34, 32, 36, ...
      daily[x].forecast_daily_item_precip_probability = forecast_daily_item["precip_probability"]; // 0, 100, 90, ...
      daily[x].forecast_daily_item_precip_icon = forecast_daily_item["precip_icon"]; // "chance-rain", ...
      // daily[x].forecast_daily_item_precip_type = forecast_daily_item["precip_type"]; // "rain", "rain", ...
      x++;
    }
    Serial.println("Done parsing daily forecast");
    // Serial.print("tomorrow: "); Serial.println(daily[1].forecast_daily_item_conditions);
    Serial.print(F("Total heap: "));Serial.println( ESP.getHeapSize());
    Serial.print(F("Free heap: "));Serial.println(ESP.getFreeHeap());
    Serial.print(F("Total PSRAM: "));Serial.println( ESP.getPsramSize());
    Serial.print(F("Free PSRAM: "));Serial.println( ESP.getFreePsram());
    Serial.println();
    Serial.println("Parsing hourly forecast");
    x=0;
    uint8_t i = 0;
    for (JsonObject forecast_hourly_item : doc["forecast"]["hourly"].as<JsonArray>()) {
      if (x > 6){break;} //gets 6 hourly forecasats
      i++;
      if (i % 2 == 0){continue;} //gets every other hourly forecast
      hourly[x].forecast_hourly_item_time = forecast_hourly_item["time"];
      hourly[x].forecast_hourly_item_time += timeZone * 60*60; // 1677816000, 1677819600, 1677823200, ...
      hourly[x].forecast_hourly_item_conditions = forecast_hourly_item["conditions"]; // "Partly Cloudy", ...
      hourly[x].forecast_hourly_item_icon = forecast_hourly_item["icon"]; // "partly-cloudy-night", ...
      hourly[x].forecast_hourly_item_air_temperature = forecast_hourly_item["air_temperature"]; // 38, 38, 38, 37, ...
      hourly[x].forecast_hourly_item_sea_level_pressure = forecast_hourly_item["sea_level_pressure"]; // 29.976, ...
      hourly[x].forecast_hourly_item_relative_humidity = forecast_hourly_item["relative_humidity"]; // 63, 64, 62, ...
      hourly[x].forecast_hourly_item_precip = forecast_hourly_item["precip"]; // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ...
      hourly[x].forecast_hourly_item_precip_probability = forecast_hourly_item["precip_probability"]; // 0, 0, 5, 5, ...
      hourly[x].forecast_hourly_item_precip_type = forecast_hourly_item["precip_type"]; // "rain", "rain", ...
      hourly[x].forecast_hourly_item_precip_icon = forecast_hourly_item["precip_icon"]; // "chance-rain", ...
      hourly[x].forecast_hourly_item_wind_avg = forecast_hourly_item["wind_avg"]; // 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, ...
      hourly[x].forecast_hourly_item_wind_direction = forecast_hourly_item["wind_direction"]; // 18, 36, 54, 56, 68, ...
      hourly[x].forecast_hourly_item_wind_direction_cardinal = forecast_hourly_item["wind_direction_cardinal"];
      hourly[x].forecast_hourly_item_wind_gust = forecast_hourly_item["wind_gust"]; // 5, 5, 5, 5, 5, 5, 5, 8, 8, 8, ...
      hourly[x].forecast_hourly_item_uv = forecast_hourly_item["uv"]; // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, ...
      hourly[x].forecast_hourly_item_feels_like = forecast_hourly_item["feels_like"]; // 35, 34, 35, 33, 33, 33, 33, ...
      hourly[x].forecast_hourly_item_local_hour = forecast_hourly_item["local_hour"]; // 23, 0, 1, 2, 3, 4, 5, 6, 7, ...
      hourly[x].forecast_hourly_item_local_day = forecast_hourly_item["local_day"]; // 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, ...
      x++;
    }
    Serial.println("Done with hourly forecasts");

    Serial.print(F("Total heap: "));Serial.println( ESP.getHeapSize());
    Serial.print(F("Free heap: "));Serial.println(ESP.getFreeHeap());
    Serial.print(F("Total PSRAM: "));Serial.println( ESP.getPsramSize());
    Serial.print(F("Free PSRAM: "));Serial.println( ESP.getFreePsram());
    // Serial.print("next hour: "); Serial.println(hourly[1].forecast_hourly_item_conditions);  
    

  }
}



#include "generatedUI.h"
long timer;

void setup() {
  
  Serial.begin(115200);
  display.begin();

  WiFi.setSleep(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP_STA);
  delay(100);

  Serial.println("Connecting to WiFi..");
      //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

  Serial.println("");
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("Total heap: "));Serial.println( ESP.getHeapSize());
  Serial.print(F("Free heap: "));Serial.println(ESP.getFreeHeap());
  Serial.print(F("Total PSRAM: "));Serial.println( ESP.getPsramSize());
  Serial.print(F("Free PSRAM: "));Serial.println( ESP.getFreePsram());

  initTime("EST5EDT,M3.2.0,M11.1.0");
  printLocalTime();
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // struct tm timeinfo;
  // if(!getLocalTime(&timeinfo)){
  //   Serial.println("No time available (yet)");
  //   return;
  // }
  // Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  // char buffer[25];
  // sprintf(buffer, "Time: %d/%d/%d %d:%0d:%0d", year(epTime), month(epTime), day(epTime), hour(epTime), minute(epTime), second(epTime));
  // Serial.println(buffer);
  getForecast();
  connectUDPReceiver();
  // display.clear();
  Serial.println("Starting to draw screen buffer");
  mainDraw();
  Serial.println(" Done drawing buffer. Updating screen..");
  // display.print("Hello World");
  // display.display();
  Serial.println("setup done");
  // display.sdCardInit();
  timer=millis();
  }
const int refresh_time = 30000;
void loop()
{
  if (millis() > timer + refresh_time){
    timer=millis();
    mainDraw();
    // display.display();
    // display.partialUpdate();
  }
  // delay(5000);
  // display.print("Wind "); display.print(wx.rapid_speed*2.23); display.print("mph at ");
  // display.print(wx.rapid_dir); display.println(" degrees.");
  // display.partialUpdate();
}
