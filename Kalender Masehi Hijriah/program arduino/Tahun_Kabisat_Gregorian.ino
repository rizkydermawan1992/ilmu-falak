void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Masukkan Tahun: ");
  while(Serial.available() == 0){}
  String tahun_str = Serial.readString();
  Serial.println(tahun_str);
  int tahun = tahun_str.toInt();

  if(tahun%4 == 0 && tahun%100 != 0 || tahun%400 == 0){
     Serial.println("Tahun "+tahun_str+" adalah tahun kabisat");
  }
  else{
    Serial.println("Tahun "+tahun_str+" adalah BUKAN tahun kabisat");
  }

  Serial.println("------------------------------");
  delay(1000);
}
