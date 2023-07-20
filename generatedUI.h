#include "Arduino.h"
// #include "Inkplate.h"
#include "C:\Users\Matt\Documents\Arduino\libraries\Adafruit_GFX_Library\Fonts\FreeSansBold24pt7b.h"
#include "fonts/Montserrat_Medium_digits64pt7b.h"
#include "fonts/Montserrat_Medium24pt7b.h"
#include "fonts/Montserrat_Medium18pt7b.h"
#include "fonts/Montserrat_Medium16pt7b.h"
#include "fonts/Montserrat_Medium14pt7b.h"
// #include <TimeLib.h>
#include <math.h>



extern Inkplate display;


// String cc_temp_content = cc.current_conditions_air_temperature;
// cc_temp_content= cc_temp_content +  String("%F");
int cc_temp_cursor_x = 35;
int cc_temp_cursor_y = 100;
const GFXfont *cc_temp_font = &Montserrat_Medium_digits64pt7b;

// String cc_feelslike_content = "Feels Like 100";
int cc_feelslike_cursor_x = 30;
int cc_feelslike_cursor_y = 142;
const GFXfont *cc_feelslike_font = &Montserrat_Medium24pt7b;

int circle0_center_x = 900;
int circle0_center_y = 120;
int circle0_fill = -1;
int circle0_radius = 80;
int circle0_color = BLACK;

String N_label_content = "N";
int N_label_cursor_x = 880;
int N_label_cursor_y = 35;
const GFXfont *N_label_font = &Montserrat_Medium24pt7b;


const uint8_t triangle0_fill = 1;
const int8_t triangle0_radius = -1;
const uint8_t triangle0_color = BLACK;
const uint8_t triLength = 25;



// Now x, y, w and h were set to respected values
// display.setFont(&Montserrat_Medium24pt7b);
// String cc_rapid_speed_content = String(wx.rapid_speed*2.237); //m/s to mph
// display.getTextBounds(cc_rapid_speed_content, 0, 0, &x, &y, &w, &h);
int cc_rapid_speed_cursor_x = 880;
int cc_rapid_speed_cursor_y = 122;
const GFXfont *cc_rapid_speed_font = &Montserrat_Medium24pt7b;

// display.setFont(&Montserrat_Medium18pt7b);
String text6_content = "mph";
// display.getTextBounds(text6_content, 0, 0, &x, &y, &w, &h);
int text6_cursor_x = 870;
int text6_cursor_y = 146;
const GFXfont *text6_font = &Montserrat_Medium18pt7b;

// Serial.println(buffer);
// String time_content = "time"";
int time_cursor_x = 33;
int time_cursor_y = 350;
const GFXfont *time_font = &Montserrat_Medium24pt7b;

// String cc_humidity_content = cc.current_conditions_relative_humidity;
// cc_humidity_content= cc_humidity_content + String("% humidity");
int cc_humidity_cursor_x = 65;
int cc_humidity_cursor_y = 191;
const GFXfont *cc_humidity_font = &Montserrat_Medium18pt7b;

// String cc_pressure_content = cc.current_conditions_station_pressure;
// cc_pressure_content= cc_pressure_content + String(" inHg");
int cc_pressure_cursor_x = 65;
int cc_pressure_cursor_y = 240;
const GFXfont *cc_pressure_font = &Montserrat_Medium18pt7b;

String lightning_content = "No Lightning";
int lightning_cursor_x = 65;
int lightning_cursor_y = 285;
const GFXfont *lightning_font = &Montserrat_Medium18pt7b;

// String cc_text_content = "Cloudy";
int cc_text_cursor_x = 420;
int cc_text_cursor_y = 230;
const GFXfont *cc_text_font = &Montserrat_Medium24pt7b;

// String uv_text_content = "3 UV";
int uv_text_cursor_x = 880;
int uv_text_cursor_y = 260;
const GFXfont *uv_text_font = &Montserrat_Medium18pt7b;

// String text11_content = "0.08 in TODAY";
int text11_cursor_x = 420;
int text11_cursor_y = 285;
const GFXfont *text11_font = &Montserrat_Medium18pt7b;

String text12_content = "Gust";
int text12_cursor_x = 1000;
int text12_cursor_y = 41;
const GFXfont *text12_font = &Montserrat_Medium18pt7b;

// String text13_content = "60"; //gust
int text13_cursor_x = 1000;
int text13_cursor_y = 79;
const GFXfont *text13_font = &Montserrat_Medium24pt7b;

String text14_content = "Avg";
int text14_cursor_x = 1000;
int text14_cursor_y = 120;
const GFXfont *text14_font = &Montserrat_Medium18pt7b;

// String text15_content = "56"; //avg
int text15_cursor_x = 1000;
int text15_cursor_y = 160;
const GFXfont *text15_font = &Montserrat_Medium24pt7b;

// String hour1_conditions_content = "5 pm   49°       0%         9";
int hour1_conditions_cursor_x = 30;
int hour1_conditions_cursor_y = 450;
const GFXfont *hour1_conditions_font = &Montserrat_Medium18pt7b;

String hour2_conditions_content = "7 pm ICON  49° ICO 0% ICO 9";
int hour2_conditions_cursor_x = 30;
int hour2_conditions_cursor_y = 512;
const GFXfont *hour2_conditions_font = &Montserrat_Medium18pt7b;

String hour3_conditions_content = "9 pm ICON  49° ICO 0% ICO 9";
int hour3_conditions_cursor_x = 30;
int hour3_conditions_cursor_y = 574;
const GFXfont *hour3_conditions_font = &Montserrat_Medium18pt7b;

String hour4_conditions_content = "11 pm ICON  49° ICO 0% ICO 9";
int hour4_conditions_cursor_x = 30;
int hour4_conditions_cursor_y = 636;
const GFXfont *hour4_conditions_font = &Montserrat_Medium18pt7b;

String hour5_conditions_content = "1 am ICON  49° ICO 0% ICO 9";
int hour5_conditions_cursor_x = 30;
int hour5_conditions_cursor_y = 698;
const GFXfont *hour5_conditions_font = &Montserrat_Medium18pt7b;

String hour6_conditions_content = "2 am ICON  49° ICO 0% ICO 9";
int hour6_conditions_cursor_x = 30;
int hour6_conditions_cursor_y = 760;
const GFXfont *hour6_conditions_font = &Montserrat_Medium18pt7b;


//Daily Weather
String day1_content = "Today";
int day1_cursor_x = 660;
int day1_cursor_y = 445;
const GFXfont *day1_font = &Montserrat_Medium18pt7b;

// String day1_conditions_content = "Partly Cloudy";
int day1_conditions_cursor_x = 660;
int day1_conditions_cursor_y = 475;
const GFXfont *day1_conditions_font = &Montserrat_Medium18pt7b;

// String day1_data_content = "IC 10%  IC 34°  IC 48°";
int day1_data_cursor_x = 870;
int day1_data_cursor_y = 445;
const GFXfont *day1_data_font = &Montserrat_Medium18pt7b;

String day2_content = "Sun 5";
int day2_cursor_x = 600;
int day2_cursor_y = 540;
const GFXfont *day2_font = &Montserrat_Medium18pt7b;

// String day2_conditions_content = "Wintery Mix Likely";
int day2_conditions_cursor_x = 600;
int day2_conditions_cursor_y = 570;
const GFXfont *day2_conditions_font = &Montserrat_Medium18pt7b;

// String day2_data_content = "IC 11%  IC 34°  IC 48°";
int day2_data_cursor_x = 820;
int day2_data_cursor_y = 540;
const GFXfont *day2_data_font = &Montserrat_Medium18pt7b;

String day3_content = "Mon 6";
int day3_cursor_x = 600;
int day3_cursor_y = 640;
const GFXfont *day3_font = &Montserrat_Medium18pt7b;

// String day3_conditions_content = "Rain Likey";
int day3_conditions_cursor_x = 600;
int day3_conditions_cursor_y = 675;
const GFXfont *day3_conditions_font = &Montserrat_Medium18pt7b;

// String day3_data_content = "IC 12%  IC 34°  IC 48°";
int day3_data_cursor_x = 820;
int day3_data_cursor_y = 640;
const GFXfont *day3_data_font = &Montserrat_Medium18pt7b;

String day4_content = "Tues 7";
int day4_cursor_x = 600;
int day4_cursor_y = 740;
const GFXfont *day4_font = &Montserrat_Medium18pt7b;

// String day4_conditions_content = "Sunny";
int day4_conditions_cursor_x = 600;
int day4_conditions_cursor_y = 770;
const GFXfont *day4_conditions_font = &Montserrat_Medium18pt7b;

// String day4_data_content = "IC 13%  IC 34°  IC 48°";
int day4_data_cursor_x = 820;
int day4_data_cursor_y = 740;
const GFXfont *day4_data_font = &Montserrat_Medium18pt7b;





unsigned long getTime() { //returns epoch time
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void drawTriangle(int x, int y, int angle) {
  // Define the size and angle of the triangle
  int size = 30;
  int theta = 40;
  angle+=90;

  // Calculate the angles of the other two vertices
  int angle1 = angle + theta / 2;
  int angle2 = angle - theta / 2;

  // Convert the angles to radians
  float rad_angle = angle * PI / 180.0;
  float rad_angle1 = angle1 * PI / 180.0;
  float rad_angle2 = angle2 * PI / 180.0;

  // Calculate the coordinates of the other two vertices
  int x1 = x + size * cos(rad_angle1);
  int y1 = y + size * sin(rad_angle1);
  int x2 = x + size * cos(rad_angle2);
  int y2 = y + size * sin(rad_angle2);

  // Draw the triangle
  display.fillTriangle(x, y, x1, y1, x2, y2, BLACK);

}

void mainDraw() {
//1200x825
int16_t x, y;
uint16_t w, h;
display.clearDisplay();
display.setFont();
//display.setTextColor(0, 7);    
display.setTextSize(2);    

// for (int i = 0; i < 1200; i += 20){ //draw gridlines
//   if (i/20 % 2 ==0){
//     display.setCursor(i+5, 780);
//   } else {
//     display.setCursor(i+5, 800);
//   }
//   display.print(i/10);
//   // display.drawLine(i, 0, i, 825, 5); // with those. Arguments are: start X, start Y, ending X, ending Y, color.
// }
// for (int i = 0; i < 825; i += 20){
//   display.setCursor(1150, i);
//   display.print(i);
//   // display.drawLine(0, i, 1200, i, 5); // with those. Arguments are: start X, start Y, ending X, ending Y, color.
// }


  Serial.println(1);
    display.setFont(cc_temp_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(cc_temp_cursor_x, cc_temp_cursor_y);
    display.print(cc.current_conditions_air_temperature);display.print("%F");
  Serial.println(2);
    display.setFont(cc_feelslike_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(cc_feelslike_cursor_x, cc_feelslike_cursor_y);
    display.print("Feels like ");display.print(cc.current_conditions_feels_like);
  Serial.println(3);
    if (circle0_fill != -1)
       display.fillCircle(circle0_center_x, circle0_center_y, circle0_radius, circle0_color);
   else
       display.drawCircle(circle0_center_x, circle0_center_y, circle0_radius, circle0_color);
       display.drawCircle(circle0_center_x, circle0_center_y, circle0_radius-1, circle0_color);
       display.drawCircle(circle0_center_x, circle0_center_y, circle0_radius-2, circle0_color);
       display.drawCircle(circle0_center_x, circle0_center_y, circle0_radius-28, circle0_color);
  Serial.println(4);
    display.setFont(cc_text_font);
    //display.setTextColor(0, 7);    
    display.getTextBounds(cc.current_conditions_conditions, 0, 0, &x, &y, &w, &h);
    display.setTextSize(1);    display.setCursor(560-w/2, cc_text_cursor_y);
    display.print(cc.current_conditions_conditions);
  Serial.println(5);
    display.setFont(N_label_font);
    display.getTextBounds(N_label_content, 0, 0, &x, &y, &w, &h);
    N_label_cursor_x = circle0_center_x-w/2;
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(N_label_cursor_x, N_label_cursor_y);
    display.print(N_label_content);
  Serial.println(6);
//wx.wind_dir
  int angle = cc.current_conditions_wind_direction;
    // int triX = circle0_center_x + (int)(circle0_radius * cos((windAngle - 30) * PI / 180));
    // int triY = circle0_center_y + (int)(circle0_radius * sin((windAngle - 30) * PI / 180));
 int x0 = circle0_center_x+(int)circle0_radius*cos((90-angle)* PI /180);
 int y0 = circle0_center_y-(int)circle0_radius*sin((90-angle)* PI /180);
  // display.fillCircle(x0, y0, 5, circle0_color);
  drawTriangle(x0, y0, angle);

  //   if (triangle0_fill != -1)
  //      display.fillTriangle(arrow_tail_x, arrow_tail_y, arrow_head_x, arrow_head_y, arrow_point_x, arrow_point_y, triangle0_color);
  //  else
  //      display.drawTriangle(arrow_tail_x, arrow_tail_y, arrow_head_x, arrow_head_y, arrow_point_x, arrow_point_y, triangle0_color);
  Serial.println(7);
    display.setFont(cc_rapid_speed_font);
    if(wx.rapid_speed < 10){
      display.getTextBounds(String(wx.rapid_speed*2.237,1), 0, 0, &x, &y, &w, &h);
      cc_rapid_speed_cursor_x = circle0_center_x-w/2;    
      //display.setTextColor(0, 7);    
      display.setTextSize(1);    display.setCursor(cc_rapid_speed_cursor_x, cc_rapid_speed_cursor_y);
      display.print(wx.rapid_speed*2.237,1);
    } else {
      display.getTextBounds(String(wx.rapid_speed*2.237,0), 0, 0, &x, &y, &w, &h);
      cc_rapid_speed_cursor_x = circle0_center_x-w/2;    
      //display.setTextColor(0, 7);    
      display.setTextSize(1);    display.setCursor(cc_rapid_speed_cursor_x, cc_rapid_speed_cursor_y);
      display.print(wx.rapid_speed*2.237,0);     
    }
  Serial.println(8);
    display.setFont(text6_font);
    display.getTextBounds(text6_content, 0, 0, &x, &y, &w, &h);
    text6_cursor_x = circle0_center_x-w/2;
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(text6_cursor_x, text6_cursor_y);
    display.print(text6_content);
  Serial.println(9);
    display.setFont(time_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(time_cursor_x, time_cursor_y);
    long epTime = getTime();
    //epTime += timeZone * 60 * 60;
  struct tm timeinfo;
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %e %Y %H:%M:%S");
  display.print(&timeinfo, "%A, %B %e %Y %I:%M %p");
  bool DST = timeinfo.tm_isdst;

  Serial.println(10);
    display.setFont(cc_humidity_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(cc_humidity_cursor_x, cc_humidity_cursor_y);
    display.print(cc.current_conditions_relative_humidity);display.print("% humidity");
    display.drawImage(epd_cc_humidity, cc_humidity_cursor_x-40, cc_humidity_cursor_y-30, 30, 30);
  Serial.println(11);
    display.setFont(cc_pressure_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(cc_pressure_cursor_x, cc_pressure_cursor_y);
    display.print(cc.current_conditions_sea_level_pressure);display.print(" inHg");
      if (strcmp(cc.current_conditions_pressure_trend,"falling")==0){ 
        display.drawImage(epd_cc_pressure_trend_arrow_falling, cc_pressure_cursor_x-40, cc_pressure_cursor_y-30, 30, 30);
      }
      if (strcmp(cc.current_conditions_pressure_trend,"rising")==0){ 
        display.drawImage(epd_cc_pressure_trend_arrow_rising, cc_pressure_cursor_x-40, cc_pressure_cursor_y-30, 30, 30);
      }
      if (strcmp(cc.current_conditions_pressure_trend,"steady")==0){ 
        display.drawImage(epd_cc_pressure_trend_arrow_steady, cc_pressure_cursor_x-40, cc_pressure_cursor_y-30, 30, 30);
      }
      if (strcmp(cc.current_conditions_pressure_trend,"unknown")==0){ 
        display.drawImage(epd_cc_pressure_trend_arrow_steady, cc_pressure_cursor_x-40, cc_pressure_cursor_y-30, 30, 30);
      }
Serial.println(12);
    display.setFont(uv_text_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(uv_text_cursor_x, uv_text_cursor_y);
    display.print(cc.current_conditions_uv);
    display.setFont(&Montserrat_Medium16pt7b);
    display.print(" UV ");
    display.setCursor(uv_text_cursor_x, uv_text_cursor_y+30);
    display.setFont(&Montserrat_Medium18pt7b);
    display.print(cc.current_conditions_solar_radiation);
    display.setFont(&Montserrat_Medium16pt7b);
    display.print(" W/m");
    display.setFont(&Montserrat_Medium14pt7b);
    display.setCursor(display.getCursorX(),display.getCursorY()-8);
    display.print("2");
Serial.println(13);
    display.setFont(text11_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(text11_cursor_x, text11_cursor_y);
    if (cc.current_conditions_precip_accum_local_day >0.0){
      display.print(cc.current_conditions_precip_accum_local_day);display.print("\" Today");
    } else {
      display.print("No rain today");
    }

Serial.println(14);
    display.setFont(text12_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(text12_cursor_x, text12_cursor_y);
    display.print(text12_content);
Serial.println(15);
    display.setFont(text13_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(text13_cursor_x, text13_cursor_y);
    // display.print(wx.wind_gust*2.23,1);
    display.print(cc.current_conditions_wind_gust);
      
Serial.println(16);
    display.setFont(text14_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(text14_cursor_x, text14_cursor_y);
    display.print(text14_content);
Serial.println(17);
    display.setFont(text15_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(text15_cursor_x, text15_cursor_y);
    // display.print(wx.wind_avg*2.23,1);
    display.print(cc.current_conditions_wind_avg);
Serial.println(18);
display.setFont(&Montserrat_Medium16pt7b);
display.setCursor(10, 400);
display.print("Hourly Forecast");
display.setCursor(570, 400);
display.print("Five Day Forecast");
    display.setFont(hour1_conditions_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    
    for(y=0;y<7;y++){
      display.setCursor(hour1_conditions_cursor_x, hour1_conditions_cursor_y+y*60);
      if (hour(hourly[y].forecast_hourly_item_time) >12){
        display.print(hour(hourly[y].forecast_hourly_item_time)-12);
        display.print(" pm");
      } else if ((hour(hourly[y].forecast_hourly_item_time)<=12 && hour(hourly[y].forecast_hourly_item_time) >=0 )){
        if (hour(hourly[y].forecast_hourly_item_time) == 0){
          display.print("12");
        } else {
          display.print(hour(hourly[y].forecast_hourly_item_time));
        }
        display.print(" am");
      } 
 //select hourly weather icon   
      if (strcmp(hourly[y].forecast_hourly_item_icon,"clear-day")==0){ //epd_clear_day
        display.drawImage(epd_60_clear_day, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"clear-night")==0){ //epd_clear_day
        display.drawImage(epd_60_clear_night, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }    
      if (strcmp(hourly[y].forecast_hourly_item_icon,"cloudy")==0){ //epd_clear_day
        display.drawImage(epd_60_cloudy, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"foggy")==0){ //epd_clear_day
        display.drawImage(epd_60_foggy, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"partly-cloudy-day")==0){ //epd_clear_day
        display.drawImage(epd_60_partly_cloudy_day, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"partly-cloudy-night")==0){ //epd_clear_day
        display.drawImage(epd_60_partly_cloudy_night, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-rainy-day")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_rainy_day, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-rainy-night")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_rainy_night, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-sleet-day")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_sleet_day, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-sleet-night")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_sleet_night, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-snow-day")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_snow_day, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-snow-night")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_snow_night, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-thunderstorm-day")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_thunderstorm_day, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"possibly-thunderstorm-night")==0){ //epd_clear_day
        display.drawImage(epd_60_possibly_thunderstorm_night, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"rainy")==0){ //epd_clear_day
        display.drawImage(epd_60_rainy, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"sleet")==0){ //epd_clear_day
        display.drawImage(epd_60_sleet, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"snow")==0){ //epd_clear_day
        display.drawImage(epd_60_snow, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"thunderstorm")==0){ //epd_clear_day
        display.drawImage(epd_60_thunderstorm, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }
      if (strcmp(hourly[y].forecast_hourly_item_icon,"windy")==0){ //epd_clear_day
        display.drawImage(epd_60_windy, epd_hourly_icon_x, hour1_conditions_cursor_y+y*60-40, epd_hourly_icon_w, epd_hourly_icon_h);
      }

      display.setCursor(220, hour1_conditions_cursor_y+y*60); display.print(hourly[y].forecast_hourly_item_air_temperature);
      display.setCursor(350, hour1_conditions_cursor_y+y*60); display.print(hourly[y].forecast_hourly_item_precip_probability); display.print("%");
      display.setCursor(500, hour1_conditions_cursor_y+y*60); display.print(hourly[y].forecast_hourly_item_wind_avg);
      // display.drawBitmap(bitmap1_x, bitmap1_y+y*60, bitmap1_content, bitmap1_w, bitmap1_h);

      display.drawImage(epd_chance_rain, epd_chance_rain_x, epd_chance_rain_y+y*60, epd_chance_rain_w, epd_chance_rain_h);

      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"N")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_n, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }      
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"NNE")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_nne, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"NE")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_ne, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"ENE")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_ene, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"E")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_e, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"ESE")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_ese, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"SE")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_se, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"SSE")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_sse, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"S")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_s, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"SSW")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_ssw, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"SW")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_sw, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"WSW")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_wsw, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"W")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_w, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"WNW")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_wnw, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"NW")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_nw, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
      if (strcmp(hourly[y].forecast_hourly_item_wind_direction_cardinal,"NNW")==0){ //epd_clear_day
        display.drawImage(epd_wind_arrow_nnw, wind_arrow_x, wind_arrow_y+y*60, wind_arrow_w, wind_arrow_h);
      }   
    }
    uint8_t y_spacing = 82;
    int8_t startx, endx, xoffset;
    // if(timeinfo.tm_hour<16){ //forecast rolls over to next day sometime in 11pm hour. need to get forecasat start time and compare to current hour.
      startx = 0;
      endx = 5;
      xoffset = 0;
    // } else {
    //   startx = 1;
    //   endx = 5;
    //   xoffset=-1;
    // }
      for(x=startx;x<endx;x++){
        Serial.print("**y:");Serial.println(day1_cursor_y+(x+xoffset)*y_spacing-30);
        if (strcmp(daily[x].forecast_daily_item_icon,"clear-day")==0){ //epd_clear_day
          display.drawImage(epd_60_clear_day, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h); 
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"clear-night")==0){ //epd_clear_day
          display.drawImage(epd_60_clear_night, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }    
        if (strcmp(daily[x].forecast_daily_item_icon,"cloudy")==0){ //epd_clear_day
          display.drawImage(epd_60_cloudy, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"foggy")==0){ //epd_clear_day
          display.drawImage(epd_60_foggy, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"partly-cloudy-day")==0){ //epd_clear_day
          display.drawImage(epd_60_partly_cloudy_day, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"partly-cloudy-night")==0){ //epd_clear_day
          display.drawImage(epd_60_partly_cloudy_night, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-rainy-day")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_rainy_day, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-rainy-night")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_rainy_night, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-sleet-day")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_sleet_day, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-sleet-night")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_sleet_night, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-snow-day")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_snow_day, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-snow-night")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_snow_night, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-thunderstorm-day")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_thunderstorm_day, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"possibly-thunderstorm-night")==0){ //epd_clear_day
          display.drawImage(epd_60_possibly_thunderstorm_night, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"rainy")==0){ //epd_clear_day
          display.drawImage(epd_60_rainy, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"sleet")==0){ //epd_clear_day
          display.drawImage(epd_60_sleet, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"snow")==0){ //epd_clear_day
          display.drawImage(epd_60_snow, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"thunderstorm")==0){ //epd_clear_day
          display.drawImage(epd_60_thunderstorm, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }
        if (strcmp(daily[x].forecast_daily_item_icon,"windy")==0){ //epd_clear_day
          display.drawImage(epd_60_windy, 580, day1_cursor_y+(x+xoffset)*y_spacing-30, epd_hourly_icon_w, epd_hourly_icon_h);
        }

        display.setCursor(day1_cursor_x, day1_cursor_y+(x+xoffset)*y_spacing);
        // if(x==0){
        //   display.print("Today");
        // }
        // else{
          display.print(dayShortStr(weekday(daily[x].forecast_daily_item_day_start_local)));
          display.print(" ");
          display.print(day(daily[x].forecast_daily_item_day_start_local));
          Serial.print("hourly start time day ");Serial.print(x);Serial.print(" day:");
          Serial.print(day(daily[x].forecast_daily_item_day_start_local));Serial.print(" hour:");
          Serial.println(hour(daily[x].forecast_daily_item_day_start_local));
        // }
        display.setCursor(day1_data_cursor_x, day1_cursor_y+(x+xoffset)*y_spacing);
        display.print(daily[x].forecast_daily_item_precip_probability);display.print("%");
        display.setCursor(995, day1_cursor_y+(x+xoffset)*y_spacing);
        display.print(daily[x].forecast_daily_item_air_temp_low);
        display.setCursor(1095, day1_cursor_y+(x+xoffset)*y_spacing);
        display.print(daily[x].forecast_daily_item_air_temp_high);
        display.setCursor(day1_conditions_cursor_x, day1_conditions_cursor_y+(x+xoffset)*y_spacing);
        display.print(daily[x].forecast_daily_item_conditions);

        display.drawImage(epd_chance_rain, hourly_epd_chance_rain_x, hourly_epd_chance_rain_y+(x+xoffset)*y_spacing, epd_chance_rain_w, epd_chance_rain_h);      
        display.drawImage(epd_low_temp_arrow, epd_low_temp_arrow_x, epd_low_temp_arrow_y+(x+xoffset)*y_spacing, epd_low_temp_arrow_w, epd_low_temp_arrow_h);
        display.drawImage(epd_high_temp_arrow, epd_high_temp_arrow_x, epd_high_temp_arrow_y+(x+xoffset)*y_spacing, epd_high_temp_arrow_w, epd_high_temp_arrow_h);
        
      }
    

 //select main weather icon   
      if (strcmp(cc.current_conditions_icon,"clear-day")==0){ //epd_clear_day
        display.drawImage(epd_clear_day, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"clear-night")==0){ //epd_clear_day
        display.drawImage(epd_clear_night, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }    
      if (strcmp(cc.current_conditions_icon,"cloudy")==0){ //epd_clear_day
        display.drawImage(epd_cloudy, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"foggy")==0){ //epd_clear_day
        display.drawImage(epd_foggy, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"partly-cloudy-day")==0){ //epd_clear_day
        display.drawImage(epd_partly_cloudy_day, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"partly-cloudy-night")==0){ //epd_clear_day
        display.drawImage(epd_partly_cloudy_night, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-rainy-day")==0){ //epd_clear_day
        display.drawImage(epd_possibly_rainy_day, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-rainy-night")==0){ //epd_clear_day
        display.drawImage(epd_possibly_rainy_night, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-sleet-day")==0){ //epd_clear_day
        display.drawImage(epd_possibly_sleet_day, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-sleet-night")==0){ //epd_clear_day
        display.drawImage(epd_possibly_sleet_night, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-snow-day")==0){ //epd_clear_day
        display.drawImage(epd_possibly_snow_day, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-snow-night")==0){ //epd_clear_day
        display.drawImage(epd_possibly_snow_night, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-thunderstorm-day")==0){ //epd_clear_day
        display.drawImage(epd_possibly_thunderstorm_day, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"possibly-thunderstorm-night")==0){ //epd_clear_day
        display.drawImage(epd_possibly_thunderstorm_night, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"rainy")==0){ //epd_clear_day
        display.drawImage(epd_rainy, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"sleet")==0){ //epd_clear_day
        display.drawImage(epd_sleet, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"snow")==0){ //epd_clear_day
        display.drawImage(epd_snow, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"thunderstorm")==0){ //epd_clear_day
        display.drawImage(epd_thunderstorm, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
      if (strcmp(cc.current_conditions_icon,"windy")==0){ //epd_clear_day
        display.drawImage(epd_windy, epd_cc_icon_x, epd_cc_icon_y, epd_cc_icon_w, epd_cc_icon_h);
      }
//end of main weather icon

    display.drawImage(epd_cc_uv, uv_icon_x, uv_icon_y-15, uv_icon_w, uv_icon_h);
    display.drawImage(epd_cc_rain_accum, epd_cc_rain_accum_x, epd_cc_rain_accum_y, epd_cc_rain_accum_w, epd_cc_rain_accum_h);

    Serial.println(38);
    display.setFont(lightning_font);
    //display.setTextColor(0, 7);    
    display.setTextSize(1);    display.setCursor(lightning_cursor_x, lightning_cursor_y);
    display.print(lightning_content);
    display.drawImage(epd_cc_lightning, lightning_cursor_x-40, lightning_cursor_y-30, 21, 30);
Serial.println(39);
// display.display();
  display.drawThickLine(0,370,1280,370,BLACK,2);
  display.drawThickLine(550,370,550,825,BLACK,2);
display.partialUpdate();
}
