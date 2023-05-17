#include <LiquidCrystal_I2C.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27,16,2);
const int soilmoisture = A0;
float persen;
int Relay1 = 2;

void setup() {
  Serial.begin(9600);
  pinMode(Relay1, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Penyiram Tanaman");
  lcd.setCursor(1,1);
  lcd.print("Auto Basis IOT");
  delay(5000);
  lcd.clear();
}

void loop() {//Pengulangan hasil pembacaan sensor
  for(int i=0; i<5; i++)
  {
    analogSense();
    delay(500);
}
}
void analogSense(){   //Sensor kelembaban tanah
    float soil = analogRead(soilmoisture);  //mendeteksi nilai dari sensor soil moisture
    persen=(soil/8192)*100;  //mempersentasikan hasil pembacaan nilai sensor ke persen
//Tampilan pada serial moitor
    Serial.print("\nSoil Moisture: ");
    Serial.print(soil);
    delay(800);
    Serial.print("Hasil Persen: ");
    Serial.print(persen);
    delay(900);
    //Untuk kondisi tanah kering
     if(persen>25){  //jika kelembaban tanah <= 25, maka pompa on
    relayOFF();  
    lcd.setCursor(1,0);
    lcd.print("T Kering: ");
    lcd.print(persen);
    lcd.print("%");
    lcd.setCursor(3,1);
    lcd.print("Pompa Nyala");
     }
 //Untuk kondisi  tanah basah
    else if(persen<=25){// jika kelembaban tanah > 25 pompa off
    relayON();
    lcd.setCursor(1,0);
    lcd.print("T Basah: ");
    lcd.print(persen);
    lcd.print("%");
    lcd.setCursor(3,1);
    lcd.print("Pompa Mati");
    }
    delay(100);
  }
//Inisiasi penggunaan relay
void relayON(){
  digitalWrite(Relay1, LOW);
  Serial.println("Relay 1 ON");

}
void relayOFF(){
  digitalWrite(Relay1, HIGH);
  Serial.println("Relay 1 OFF");

}
  
