#include <AntaresESP8266HTTP.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 2
#define RST_PIN 0

#define ACCESSKEY "6100fc96a0000379:2536d3e0e1149aec"           // Put your Antares account key here
#define WIFISSID "Nancy"             // Put your SSID here
#define PASSWORD "haihaihai"         // Put your WiFi password here

#define projectName "CPS"       // Put your application name here
#define deviceName "RFID"         // Put your device name here

#define whitecard "DEFAULT WHITE CARD"
#define nancy "Nancy"
#define gilang "Gilang"
#define sri "sri"


AntaresESP8266HTTP antares(ACCESSKEY);        // Make antares object

LiquidCrystal_I2C lcd(0x27,16,2);

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;

void setup() 
{
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("TAP KARTU ANDA!");
  lcd.setCursor(0,1);
  lcd.print("---kelompok 2---");
  delay(2000);

  Serial.begin(115200);
  SPI.begin();

  mfrc522.PCD_Init();
  myServo.attach(15);
  myServo.write(0);

  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);  // Try to connect to WiFi

  Serial.println("\nTAP KARTU ANDA!");
  Serial.println();
}

void loop() 
{
  char open[] = "TERBUKA";
  char close[]  = "TERTUTUP";

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  Serial.print("Nomor Seri UID :");
  String content= "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("INFO: "); 

  content.toUpperCase();
  if (content.substring(1) == "1A DF FA 3B"||content.substring(1) == "3A B7 89 29"||content.substring(1) == "5A 30 5F 3B")
  {
    char UID1[] = "1A DF FA 3B";
    char UID2[] = "3A B7 89 29";
    char UID3[] = "5A 30 5F 3B";
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PINTU TERBUKA");
    lcd.setCursor(0,1);
    lcd.print("(VIA KTM)");
    delay(1000);

    myServo.write(180);
    delay(1000);
    myServo.write(0);

    if(content.substring(1) == "1A DF FA 3B")
    {
      antares.add("PINTU",open);
      antares.add("NAMA",nancy);
      antares.add("UID (VIA KTM)",UID1);
      antares.send(projectName, deviceName);
      delay(1000);
    }
    else if(content.substring(1) == "3A B7 89 29")
    {
      antares.add("PINTU",open);
      antares.add("NAMA",gilang);
      antares.add("UID (VIA KTM)",UID2);
      antares.send(projectName, deviceName);
      delay(1000);
    }
    else //(content.substring(1) == "5A 30 5F 3B")
    {
      antares.add("PINTU",open);
      antares.add("NAMA",sri);
      antares.add("UID (VIA KTM)",UID3);
      antares.send(projectName, deviceName);
      delay(1000);
    }

    Serial.println("PINTU TERBUKA (VIA KTM)");
    
    setup();
  }

  else if (content.substring(1) == "C6 0E A3 D3") 
  {
    char UID[] = "C6 0E A3 D3";
    
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PINTU TERBUKA");
    lcd.setCursor(0,1);
    lcd.print("(VIA WHITE CARD)");
    delay(1000);

    myServo.write(180);
    delay(1000);
    myServo.write(0);

    antares.add("PINTU",open);
    antares.add("NAMA",whitecard);
    antares.add("UID (VIA WHITE CARD)",UID);
    antares.send(projectName, deviceName);
    delay(1000);

    Serial.println("PINTU TERBUKA (VIA WHITE CARD)");

    setup();
  } 

  else if (content.substring(1) == "04 5A 10 92 4D 60 80"||content.substring(1) == "04 56 79 82 00 25 80"||content.substring(1) == "04 7B 16 02 D5 5D 80") 
  {
    char UID1[] = "04 5A 10 92 4D 60 80";
    char UID2[] = "04 56 79 82 00 25 80";
    char UID3[] = "04 7B 16 02 D5 5D 80";
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PINTU TERBUKA");
    lcd.setCursor(0,1);
    lcd.print("(VIA E-KTP)");
    delay(1000);

    myServo.write(180);
    delay(1000);
    myServo.write(0);

    if(content.substring(1) == "04 5A 10 92 4D 60 80")
    {
      antares.add("PINTU",open);
      antares.add("NAMA",nancy);
      antares.add("UID (VIA E-KTP)",UID1);
      antares.send(projectName, deviceName);
      delay(1000);
    }
    else if(content.substring(1) == "04 56 79 82 00 25 80")
    {
      antares.add("PINTU",open);
      antares.add("NAMA",gilang);
      antares.add("UID (VIA E-KTP)",UID2);
      antares.send(projectName, deviceName);
      delay(1000);
    }
    else //(content.substring(1) == "04 7B 16 02 D5 5D 80")
    {
      antares.add("PINTU",open);
      antares.add("NAMA",sri);
      antares.add("UID (VIA E-KTP)",UID3);
      antares.send(projectName, deviceName);
      delay(1000);
    }

    Serial.println("PINTU TERBUKA (VIA E-KTP)");

    setup();
  }

  else
  {
    char info[] = "KARTU TIDAK TERDAFTAR";
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("KARTU TIDAK");
    lcd.setCursor(0,1);
    lcd.print("TERDAFTAR");
    delay(1000);
    
    antares.add("PINTU",close);
    antares.add("INFO",info);
    antares.send(projectName, deviceName);
    delay(1000);

    Serial.println("KARTU TIDAK TERDAFTAR");

    setup();
  }
}
