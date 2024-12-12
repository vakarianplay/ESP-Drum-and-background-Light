#include "datagrabber.h"

DataGrabber::DataGrabber()
{
  Serial.println("init datagrabber");
}

void DataGrabber::setupUrl(String url_)
{
  url = url_;
}

String DataGrabber::getData()
{
  if (url.length() > 5) {
    http.begin(client, url);  
    int responseCode = http.GET();                                  
    if (responseCode > 0) { 
      payload = http.getString();   
    }
    http.end();
  }
  return payload;
}