
String str_tgl, str_bln, str_thn, Kalender, namaBulan, Masehi, Hijriah;
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



String bulanMasehi(int angkaBulan){
  namaBulan;
  
  if(angkaBulan == 1){ namaBulan = "januari"; }
  else if(angkaBulan == 2) { namaBulan = "Februari"; }
  else if(angkaBulan == 3) { namaBulan = "Maret"; }
  else if(angkaBulan == 4) { namaBulan = "April"; }
  else if(angkaBulan == 5) { namaBulan = "Mei"; }
  else if(angkaBulan == 6) { namaBulan = "Juni"; }
  else if(angkaBulan == 7) { namaBulan = "Juli"; }
  else if(angkaBulan == 8) { namaBulan = "Agustus"; }
  else if(angkaBulan == 9) { namaBulan = "September"; }
  else if(angkaBulan == 10) { namaBulan = "Oktober"; }
  else if(angkaBulan == 11) { namaBulan = "November"; }
  else if(angkaBulan == 12) { namaBulan = "Desember"; }
  else { namaBulan = "Tidak Diketahui"; }
  
  return namaBulan;
}

String bulanHijriah(int angkaBulan){
  namaBulan;
  
  if(angkaBulan == 1){ namaBulan = "Muharram"; }
  else if(angkaBulan == 2) { namaBulan = "Shafar"; }
  else if(angkaBulan == 3) { namaBulan = "Rabiul Awal"; }
  else if(angkaBulan == 4) { namaBulan = "Rabiul Akhir"; }
  else if(angkaBulan == 5) { namaBulan = "Jumadil Awal"; }
  else if(angkaBulan == 6) { namaBulan = "Jumadil Akhir"; }
  else if(angkaBulan == 7) { namaBulan = "Rajab"; }
  else if(angkaBulan == 8) { namaBulan = "Sya'ban"; }
  else if(angkaBulan == 9) { namaBulan = "Ramadhan"; }
  else if(angkaBulan == 10) { namaBulan = "Syawal"; }
  else if(angkaBulan == 11) { namaBulan = "Dzulqa'dah"; }
  else if(angkaBulan == 12) { namaBulan = "Dzulhijjah"; }
  else { namaBulan = "Tidak Diketahui"; }
  
  return namaBulan;
}

String hijriahToMasehi(int tgl, int bln, int thn){
  unsigned long bln_2 = 29.5001*(bln-1);
  int N = tgl + bln_2 +0.99;
  //Serial.println("N = "+ String(N));
  
  unsigned long Q = thn/30;
  //Serial.println("Q = "+ String(Q));
  
  int R = thn%30;
  //Serial.println("R = "+ String(R));
  
  unsigned long A = (11*R+3)/30;
  //Serial.println("A = "+ String(A));
  
  int W = 404*Q+354*R+208+A;
  //Serial.println("W = "+ String(W));
  
  unsigned long Q1 = W/1461;
  //Serial.println("Q1 = "+ String(Q1));
  
  int Q2 = W%1461;
  //Serial.println("Q2 = "+ String(Q2));

  unsigned long Q_3 = 7*Q+Q1;
  int G  = 621+4*Q_3;
  //Serial.println("G = "+ String(G));
  
  unsigned long K  = Q2/365.2422;
  //Serial.println("K = "+ String(K));
  
  unsigned long E  = 365.2422*K;
  //Serial.println("E = "+ String(E));
  
  int J  = Q2 - E + N - 1;
  //Serial.println("J = "+ String(J));
  
  int X = G + K;
  //Serial.println("X = "+ String(X));
  
  if (X%4 == 0 && J>366){
      J = J-366;
      X = X+1;
  }
  else if (X%4 == 0 && J>365){
      J = J-365;
      X = X+1;
  }
  
  unsigned long JD = 365.25*(X-1)+1721423+J;
  //Serial.println("JD = "+ String(JD));
  
  unsigned long alpha = (JD-1867216.25)/36524.25;
  //Serial.println("alpha = "+ String(alpha));

  unsigned long beta = JD+1+alpha-alpha/4;
  //Serial.println("beta = "+ String(beta));
  
  if (beta < 2299161){
      beta = JD;
  }
  
  unsigned long b = beta+1524;
  //Serial.println("b = "+ String(b));
  
  unsigned long c = (b-122.1)/365.25;
  //Serial.println("c = "+ String(c));
  
  unsigned long d = 365.25*c;
  //Serial.println("d = "+ String(d));
  
  unsigned long e = (b-d)/30.6001;
  //Serial.println("e = "+ String(e));

  unsigned long e_2 = 30.6001*e;
  int HM = b-d-e_2;

  int BM, TM;
  
  if(e< 14){
    BM = e-1;
  }
  else{
    BM = e-13;
  }
  
  if(BM<3){
    TM = c-4715;
  }
  else{
    TM = c-4716;
  }

  float Julian = julianDay(HM, BM, TM);
  Serial.println("Julian Day: "+String(Julian));

  if (Julian <= 2299159.5){
       Kalender = "Julian"; 
  }
  else if(Julian > 2299159.5){
     Kalender = "Gregorian";
  }
  else{
     Kalender = "Tidak Diketahui";
  }
  Serial.println("Kalender : "+Kalender);

  Hijriah = "Hijriah : "+String(tgl)+" "+bulanHijriah(bln)+" "+String(thn);
  Serial.println(Hijriah);
  
  Masehi  = "Masehi : "+String(HM)+" "+bulanMasehi(BM)+" "+String(TM);
  Serial.println(Masehi);
  
  Serial.println("Hari : "+namaHari(Julian));
  
  return;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Tanggal Hijriah: ");
  while(Serial.available() == 0){};
  str_tgl = Serial.readString();
  Serial.println(str_tgl);
  int_tgl = str_tgl.toInt();

  Serial.print("Bulan Hijriah: ");
  while(Serial.available() == 0){};
  str_bln = Serial.readString();
  Serial.println(str_bln);
  int_bln = str_bln.toInt();

  Serial.print("Tahun Hijriah: ");
  while(Serial.available() == 0){};
  str_thn = Serial.readString();
  Serial.println(str_thn);
  int_thn = str_thn.toInt();

  hijriahToMasehi(int_tgl, int_bln, int_thn);
  
  Serial.println("-----------------------------------------");
  delay(1000);
  
}
