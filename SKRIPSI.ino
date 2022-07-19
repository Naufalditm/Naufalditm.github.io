#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "CTBot.h"

// Membuat ESP8266 Terhubung dengan hotspot WiFi
const char* ssid = "Testament";
const char* password = "satuampelapan";
const char* host = "192.168.43.173";

// Inisialisasi Bot Telegram
CTBot myBot;
CTBotReplyKeyboard Tbl;
CTBotInlineKeyboard TblSiram, SIRAM, TIDAK;

#define SIRAM "Pompa air segera dinyalakan :)"
#define TIDAK "Tidak"
              
String token = "5402099655:AAFMNSSHIjb_Tll-VdDI2Ys1_HQ3w9jeZb4";
// End Inisialisasi Bot Telegram

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


dht DHT11;
#define DHT11_PIN D4

int kelembapant = analogRead(A0);
int relay = 0; // 0 merupakan GPIO0 dari D3 Pin NodeMCU ESP8266




void setup()
{
  Serial.begin(115200);

  lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight(); //To Power ON the back light
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  

  Serial.println('\n');
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start Telegram Bot
  myBot.wifiConnect(ssid, password);       
  myBot.setTelegramToken(token);
           
  if(myBot.testConnection()){
      Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
  }else{ 
      Serial.println("\nTidak Terkoneksi Ke Telegram BOT"); 
  }

  // Membuat quick command pada bot Telegram
  Tbl.addButton("Status");
  Tbl.addButton("Siram");

  // Membuat inline quick command
  TblSiram.addButton("✅ Ya", SIRAM, CTBotKeyboardButtonQuery);
  TblSiram.addButton("❌ Tidak", TIDAK, CTBotKeyboardButtonQuery);     
}



// Menjalankan fungsi loop
void loop() {
  WiFiClient client;
  const int httpPort = 80;
  String Link;
  HTTPClient http;
  
  TBMessage msg;
  
String keterangan[] = {"TANAH BASAH", "NORMAL", "TANAH KERING", "SIRAM OTOMATIS"};
String a;
  
  if(!client.connect(host, httpPort)) {
    Serial.println("Connection Failed");
    return;
  }

  
  int chk = DHT11.read11(DHT11_PIN);
  float suhu = DHT11.temperature;
  int kelembapanu = DHT11.humidity;
  int kelembapant = analogRead(A0);

  lcd.clear();
  if (kelembapant >= 550) {
      a = keterangan[3];  
        lcd.setCursor(0, 0);
        lcd.print("Kelembapan : ");
        lcd.println(kelembapant);
        lcd.setCursor(0, 1);
        lcd.println(" SIRAM OTOMATIS ");
            myBot.sendMessage(msg.sender.id, "Kondisi tanah sangat kering :( Water pump akan menyala otomatis...");
         digitalWrite(relay, LOW);
         delay(5000);
         digitalWrite(relay, HIGH); 
  } else  if (kelembapant >= 500 && kelembapant < 549) {
      a = keterangan[2];   
        lcd.setCursor(0, 0);
        lcd.print("Kelembapan : ");
        lcd.println(kelembapant);
        lcd.setCursor(0, 1);
        lcd.print("  TANAH KERING  ");
            myBot.sendMessage(msg.sender.id, "Suhu: " +(String)DHT11.temperature+"°C" +"\nKelembapan Udara: " +(String)DHT11.humidity+"%" +"\nKelembapan Tanah: " +(String)kelembapant +"\nKondisi Tanah: " +(String)a);
            myBot.sendMessage(msg.sender.id, "Tanah dalam keadaan kering. Apakah anda ingin menyiram tanaman anda?", TblSiram);
  } else  if (kelembapant >= 300 && kelembapant < 500) {
      a = keterangan[1];
        lcd.setCursor(0, 0);
        lcd.print("Kelembapan : ");
        lcd.println(kelembapant);
        lcd.setCursor(0, 1);
        lcd.print("     NORMAL    ");
  } else {
          a = keterangan[0];
        lcd.setCursor(0, 0);
        lcd.print("Kelembapan : ");
        lcd.println(kelembapant);
        lcd.setCursor(0, 1);
        lcd.print("   TANAH BASAH   ");
  }
  delay(4000);
 Link = "http://" + String(host) + "/skripsi/controller/kirimdata.php?suhu=" +String(suhu) + "&kelembapanu=" + String(kelembapanu) + "&kelembapant=" + String(kelembapant);
  // Eksekusi alamat link
  http.begin(client, host, httpPort, Link);
  http.GET();
  String response = http.getString();
  Serial.println(response);
  http.end();

  lcd.clear();
  // Menjalankan fungsi LCD menampilkan data DHT11
  lcd.setCursor(0, 0); //Defining positon to write from first row,first column .
  lcd.print("Humidity:"); //You can write 16 Characters per line .
  lcd.setCursor(10, 0); //Defining positon to write from first row,first column .
  lcd.print(DHT11.humidity, 1); //You can write 16 Characters per line .
  lcd.print("%");

  lcd.setCursor(0, 1); //Defining positon to write from first row,first column .
  lcd.print("Temp    :"); //You can write 16 Characters per line .
  lcd.setCursor(10, 1); //Defining positon to write from first row,first column .
  lcd.print(DHT11.temperature, 1); //You can write 16 Characters per line .
  lcd.print((char)223);
  lcd.println("C");
  delay(4000);


  Serial.print("\n\n\nKelembapan Udara : ");
  Serial.println(DHT11.humidity);
  Serial.print("\nSuhu Udara : ");
  Serial.println(DHT11.temperature);
  Serial.print("\nKelembapan Tanah: ");
  Serial.println(kelembapant);
  Serial.print("\nKeterangan: ");
  Serial.println(a);
  
 
  

  
  // Membuat fungsi bot
  if (myBot.getNewMessage(msg)) {                                                           
    if (msg.text.equalsIgnoreCase("/start")) {                                         
       myBot.sendMessage(msg.sender.id, "Halo, saya adalah bot monitoring penyiram tanaman otomatis. Bila ingin mengetahui keadaan suhu ataupun kelembapan tanah silahkan klik tombol perintah dibawah :)", Tbl);
       Serial.println("\nBot dalam keadaan aktif \n");
    } 
    else if (msg.text.equalsIgnoreCase("Status")) { 
       myBot.sendMessage(msg.sender.id, "Suhu: " +(String)DHT11.temperature+"°C" +"\nKelembapan Udara: " +(String)DHT11.humidity+"%" +"\nKelembapan Tanah: " +(String)kelembapant +"\nKondisi Tanah: " +(String)a);
    } 
    else if (msg.text.equalsIgnoreCase("Siram")) {
       if (kelembapant < 500) {
        myBot.sendMessage(msg.sender.id, "Kelembapan Tanah: " +(String)kelembapant +"\nKondisi Tanah: " +(String)a);
        myBot.sendMessage(msg.sender.id, "Apakah anda ingin tetap menyiramnya?", TblSiram);
       } else {
        myBot.sendMessage(msg.sender.id, "Siap, akan dilakukan penyiraman terhadap tanaman :)");
        digitalWrite(relay, LOW);
        delay(5000);
        digitalWrite(relay, HIGH);
       }
    } 
    else if (msg.messageType == CTBotMessageQuery) { 
      if(msg.callbackQueryData.equals(SIRAM)){
           myBot.sendMessage(msg.sender.id, "Pompa akan segera dinyalakan...");
        digitalWrite(relay, LOW);
        delay(5000);
        digitalWrite(relay, HIGH);
      } else if(msg.callbackQueryData.equals(TIDAK)){
           myBot.sendMessage(msg.sender.id, "Perintah 'Siram' dibatalkan.\nSilahkan klik 'Status' bila ingin mengetahui kondisi tanah :)");
        digitalWrite(relay, HIGH);
      }
    }
  }
}
