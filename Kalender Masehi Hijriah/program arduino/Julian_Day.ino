
String str_tgl, str_bln, str_thn, Kalender;
int int_tgl, int_bln, int_thn, B2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

float julianDay(int tgl, int bln, int thn){
    if (bln < 3){
          bln = bln+12;
          thn = thn-1;
    }

    if(thn < 1582){
      B2 = 0;
    }
    else if( thn == 1582 && bln < 10){
      B2 = 0;
    }
    else if(thn == 1582 && bln == 10 && tgl <= 4){
      B2 = 0;
    }
    else{
      //Gregorian
      unsigned long T2 = thn/100;
      B2 = 2-T2+(T2/4); //Faktor Koreksi Tahun Kabisat
    }
    
    unsigned long JHT = 365.25*thn;
    unsigned long JHB = (30.6001*(bln+1));


    //Kalkulasi Julian Day
    float JD = 1720994.5 + JHT  + JHB + B2 + tgl;
    return JD;
}

String namaHari (float JD){
  String Hari;
  float p = JD + 1.5;
  float ss = (p/7) - int(p/7); //sisa hari
  ss = ss*7;

  int nomorHari = round(ss+1);
  if (nomorHari == 1){
    Hari = "Ahad";
  }
  else if(nomorHari == 2){
    Hari = "Senin";
  }
  else if(nomorHari == 3){
    Hari = "Selasa";
  }
  else if(nomorHari == 4){
    Hari = "Rabu";
  }
  else if(nomorHari == 5){
    Hari = "Kamis";
  }
  else if(nomorHari == 6){
    Hari = "Jumat";
  }
  else if(nomorHari == 7){
    Hari = "Sabtu";
  }
  else{
    Hari = "Tidak Diketahui";
  }
  return Hari;
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Tanggal Masehi: ");
  while(Serial.available() == 0){};
  str_tgl = Serial.readString();
  Serial.println(str_tgl);
  int_tgl = str_tgl.toInt();

  Serial.print("Bulan Masehi: ");
  while(Serial.available() == 0){};
  str_bln = Serial.readString();
  Serial.println(str_bln);
  int_bln = str_bln.toInt();

  Serial.print("Tahun Masehi: ");
  while(Serial.available() == 0){};
  str_thn = Serial.readString();
  Serial.println(str_thn);
  int_thn = str_thn.toInt();

  float JD = julianDay(int_tgl, int_bln, int_thn);
  if (JD <= 2299159.5){
       Kalender = "Julian"; 
  }
  else if(JD > 2299159.5){
     Kalender = "Gregorian";
  }
  else{
     Kalender = "Tidak Diketahui";
  }

  Serial.print("Julian Day : ");
  Serial.println(JD);
  Serial.print("Kalender : ");
  Serial.println(Kalender);
  Serial.print("Hari : ");
  Serial.println(namaHari(JD));
  Serial.println("-----------------------------------------");
  delay(1000);
  

}
