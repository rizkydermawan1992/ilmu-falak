
String str_tgl, str_bln, str_thn, Kalender, namaBulan, Masehi, Hijriah;
int int_tgl, int_bln, int_thn, B2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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

String masehiToHijriah(int tgl, int bln, int thn){
  if(thn < 1582){
      B2 = 0;
      Kalender = "Julian";
    }
    else if( thn == 1582 && bln < 10){
      B2 = 0;
      Kalender = "Julian";
    }
    else if(thn == 1582 && bln == 10 && tgl <= 4){
      B2 = 0;
      Kalender = "Julian";
    }
    else{
      //Gregorian
      unsigned long T2 = thn/100;
      B2 = 2-T2+(T2/4); //Faktor Koreksi Tahun Kabisat
      Kalender = "Gregorian";
    }

 
  unsigned long JHT = 365.25*thn;
  unsigned long JHB = (30.6001*(bln+1));
  float JD = 1722519 + JHT  + JHB + B2 + tgl;
  //Serial.println("JD : "+String(JD));
  
  unsigned long c = (JD-122.1)/365.25;
  //Serial.println("c : "+String(c));
  unsigned long d = 365.25*c;
  //Serial.println("d : "+String(d));
  unsigned long e = (JD-d)/30.6001;

  unsigned long HM, BM, TM;
  if(Kalender == "Gregorian"){
    HM = JD-d-(30.6001*e);
  }
  else{
    HM = tgl;
  }
  if(Kalender == "Gregorian"){
     if (e<14){
        BM = e-1;
     }
    else{
        BM = e-13;
    }
  }
  else{
    BM = bln;
  }
  if(Kalender == "Gregorian"){
    if (BM<3){
        TM = c-4715;
    }
    else{
        TM = c-4716;
    }
  }
  else{
    TM = thn;
  }
  
  //Serial.println("e : "+String(e));
  
  int W;
  if(TM%4==0){
    W=1;
  }
  else{
    TM=2;
  }
   //Serial.println("W : "+String(W));
  
  unsigned long N = (275*BM)/9-W*((BM+9)/12) + HM - 30;
  //Serial.println("N : "+String(N));
  int A = thn - 623;
  //Serial.println("A : "+String(A));
  unsigned long BH = A/4;
  //Serial.println("BH : "+String(BH));
  int C = A%4;
  //Serial.println("C : "+String(C));
  float C1 = 365.2501*C;
  //Serial.println("C1 : "+String(C1));
  unsigned long C2 = C1;
  //Serial.println("C2 : "+String(C2));
  
  if (C1-C2 > 0.5){
      C2 = C2+1;
  }
  
  unsigned long D2 = 1461*BH+170+C2;
  //Serial.println("D2 : "+String(D2));
  unsigned long Q = D2/10631;
  //Serial.println("Q : "+String(Q));
  int R = D2%10631;
  //Serial.println("R : "+String(R));
  unsigned long J = R/354;
  //Serial.println("J : "+String(J));
  int K = R%354;
  //Serial.println("K : "+String(K));
  unsigned long O = (11*J+14)/30;
  //Serial.println("O : "+String(O));
  int Hah = 30*Q+J+1;
  //Serial.println("Hah : "+String(Hah));
  int JJ = K-O+N-1;
  //Serial.println("JJ : "+String(JJ));  
  int CL = Hah%30;
  //Serial.println("CL : "+String(CL));
  int DL =(11*CL+3)%30;
  //Serial.println("DL : "+String(DL));
  
  if (JJ > 354){
      Hah = Hah+1;
  }
  
  if (JJ>354){
      if (DL<19){
        JJ = JJ-354;
      }
      else{
        JJ = JJ-355;
      }
  }
  
  if(JJ == 0){
      Hah = Hah-1;
      JJ = 355;
  }
  
  unsigned long S = (JJ-1)/29.5;
  //Serial.println("S : "+String(S));
  int m = S+1;
  //Serial.println("m : "+String(m));
  
  if (JJ == 355){
      m = 12;
  }
  
  d = JJ-29.5*S;
  //Serial.println("d : "+String(d));
  
  if(JJ == 355){
      d = 30;
  }
  
  int HH = d;
  int TH = Hah;

  Hijriah = "Hijriah : "+String(HH)+" "+bulanHijriah(m)+" "+String(TH);
  return Hijriah;
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
  
  
  Serial.println("Masehi : "+str_tgl+" "+bulanMasehi(int_bln)+" "+str_thn);
  Hijriah = masehiToHijriah(int_tgl, int_bln, int_thn);
  Serial.println(Hijriah);
  

  Serial.println("-----------------------------------------");
  delay(1000);
  
}
