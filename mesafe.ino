int trigPin = 6; /* Sensorun trig pini Arduinonun 6 numaralı ayağına bağlandı */
int echoPin = 7;/* Sensorun echo pini Arduinonun 7 numaralı ayağına bağlandı */
int echoPin2 = 5;
int trigPin2 = 4;
                                                                                                                              
long sure,sure2;
long uzaklik,uzaklik2;

void setup(){
  pinMode(trigPin, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin,INPUT); /* echo pini giriş olarak ayarlandı */
   pinMode(trigPin2, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin2,INPUT); 
  Serial.begin(9600); /* Seri haberlesme baslatildi */
}
void loop()
{
  digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
  sure = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  uzaklik= sure /29.1/2; /* ölçülen sure uzaklığa çevriliyor */            
  if(uzaklik > 100)
    uzaklik = 100;
 
  //Serial.print("1. sensor Uzaklik ");  
 // Serial.print(uzaklik); /* hesaplanan uzaklık bilgisayara aktarılıyor */
 // Serial.println(" CM olarak olculmustur.");  



digitalWrite(trigPin2, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
  sure2 = pulseIn(echoPin2, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  uzaklik2= sure2 /29.1/2; /* ölçülen sure uzaklığa çevriliyor */            
  if(uzaklik2 > 100)
    uzaklik2 = 100;
 // Serial.print("2. sensor Uzaklik ");  
 Serial.print(uzaklik);
 Serial.print("/");
  Serial.println(uzaklik2); /* hesaplanan uzaklık bilgisayara aktarılıyor */
 // Serial.println(" CM olarak olculmustur.");  
  
  delay(1000); 
}
