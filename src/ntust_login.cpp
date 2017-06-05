#include <ntust_login.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* login_request="POST /auth/loginnw.html HTTP/1.1\r\nHost: wlan-aruba.ntust.edu.tw\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) Gecko/20100101 Firefox/53.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-TW,zh;q=0.8,en-US;q=0.5,en;q=0.3\r\nAccept-Encoding: gzip, deflate, br\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 38\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\nusername=%s&password=%s\r\n\r\n";
const char* logout_request="GET /auth/logout.html HTTP/1.1\r\nHost: 140.118.151.250\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) Gecko/20100101 Firefox/53.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-TW,zh;q=0.8,en-US;q=0.5,en;q=0.3\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";

//TODO add fingerprint
//const char *fingerprint = "CB:52:53:B1:F2:27:30:C6:85:E7:21:B7:DB:81:DA:74:6C:23:86:13";

const char *login_host = "wlan-aruba.ntust.edu.tw";
const char *logout_host = "140.118.151.250";
const int logout_http_port = 80;
const int login_https_port = 443;
const char *login_url = "/auth/loginnw.html";
const char *logout_url = "/auth/logout.html";


bool login(const char* username,const char* password)
{
  WiFiClientSecure client;
  if(!client.connect(login_host,login_https_port))
  {
    Serial.println("login server connect failed, trying to logout");
    logout();
    delay(1000);
    if(!client.connect(login_host,login_https_port))
    {
      Serial.println("login server connect failed");
      return false;
    }
  }
  client.printf(login_request,username,password );

  bool is_login=false;

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if(line.indexOf("res=success") > 0)
    {
      is_login=true;
      break;
    }
  }
  client.stop();
  return is_login;
}

void logout()
{
  WiFiClient client;
  if(!client.connect(logout_host, logout_http_port))
  {
    Serial.println("logout server connect failed");
    while(1){}
  }
  client.print(logout_request);
  client.stop();
  Serial.println("Logout OK");
}
