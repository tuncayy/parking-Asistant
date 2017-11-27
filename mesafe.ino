#include <Servo.h>
int servoPin = 8;
Servo servo;
int trigPin = 6; /* Sensorun trig pini Arduinonun 6 numaralı ayağına bağlandı */
int echoPin = 7;/* Sensorun echo pini Arduinonun 7 numaralı ayağına bağlandı */
int echoPin2 = 5;
int trigPin2 = 4;
int sonolcum; 
int sonolcum2;                                                                                                                             
long sure,sure2;
long uzaklik,uzaklik2;
long uzaklik1toplam = 0, uzaklik2toplam = 0;
int servoacisi;

void setup(){
  pinMode(trigPin, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin,INPUT); /* echo pini giriş olarak ayarlandı */
   pinMode(trigPin2, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin2,INPUT);
  servo.attach(servoPin); 
  servo.write(0);
  Serial.begin(9600); /* Seri haberlesme baslatildi */
}
void loop()
{
  uzaklik1toplam = 0; uzaklik2toplam = 0;
  for(int i = 0; i<20;i++)
  {
  digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
  sure = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  uzaklik= sure /29.1/2; /* ölçülen sure uzaklığa çevriliyor */            
  if(uzaklik > 100 && abs((uzaklik - sonolcum)) > 40)
    uzaklik = sonolcum;

  
   
  sonolcum = uzaklik;
  uzaklik1toplam += uzaklik;
 
digitalWrite(trigPin2, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
  sure2 = pulseIn(echoPin2, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  uzaklik2= sure2 /29.1/2; /* ölçülen sure uzaklığa çevriliyor */            
  if(uzaklik2 > 100 && abs((uzaklik2 - sonolcum2)) > 40)
    uzaklik2 = sonolcum2;

sonolcum2 = uzaklik2;
uzaklik2toplam += uzaklik2;
  }// end of for
  

 servoacisi = (uzaklik1toplam/20)*1.8;
 if(uzaklik1toplam/20 >= 0 && uzaklik1toplam/20 <= 20)
 {
//  Serial.print("servo= ");
 // Serial.println(servoacisi);
  servo.write(servoacisi);
  delay(20);  
  }
  if(uzaklik1toplam/20 >= 21 && uzaklik1toplam/20 <= 100)
 {
 // Serial.print("servo= ");
 // Serial.println(servoacisi);
  servo.write(servoacisi);
  delay(20);  
  }
  
 // Serial.print("2. sensor Uzaklik ");  
 Serial.print(uzaklik1toplam/20);
 Serial.print("/");
  Serial.println(uzaklik2toplam/20); /* hesaplanan uzaklık bilgisayara aktarılıyor */
 // Serial.println(" CM olarak olculmustur.");  
  
  delay(1000); 
}
