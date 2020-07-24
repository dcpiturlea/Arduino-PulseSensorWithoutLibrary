//  Variables
int PulseSensorPurplePin = A0;        // Senzorul de puls este conectat la pinul o
int LED13 = 13;   // Ledul care va licari este legat la punul 13
int Signal;                // retine datele trimise de senzor(in mod analog). Valorile sunt intre 0 si 1024
int Threshold = 550;            // aceasta variabila determina care semnal reprezinta o bataie si care nu.
int BPM = 0;      //Variabila care retine bataile pe minut
boolean wasBPM = false; //Variabila booleana care devine true la fiecare bataie a inimii
int countBP = 0;  //Variabila care numara bataile inimii
int LastTime = 0;
int ThisTime;      //Variabila care retine milisecundele incepand din momentul respecctiv
int lastTimeFromCalculationBpm = 0; //Variabila care retine timpul de la ultima masurare BPM
int firstTime = 0; //Variabila care masoara timpul de la pornirea aplicatiei
int minBPM = 45;  //puls minim
int maxBPM = 200; //puls maxim
int pinAudio = 1;
boolean wasfirstPulse = false; //variabila care devine true la prima bataie de inima
int pulseInterval = 0;
int countCalculationBPM = 0;
int lastBPM = 0;

// pinii 2-8 sunt conectati la display pt cifre, iar 10-12 pentru nr cifrei

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;


// Setarile programului(ruleaza o singura data)
void setup() {
  pinMode(LED13, OUTPUT);        // pinul va aprinde si va stinge ledul la fiecare bataie a inimii(pin 13)
  Serial.begin(9600);
  Serial.println("A pornit aparatul");
  // lastTimeFromCalculationBpm = millis();
  firstTime = millis();

  //setare ecran 4 segmente
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT); 

  //afisare bydeFault zero pe toate ecranele
  afisareZero();
}


// "Functie" care se repeta la infinit
void loop() {
  noTone(pinAudio);
  if (countBP > 0) {
    wasfirstPulse == true;
  }
  ThisTime = millis();
  Signal = analogRead(PulseSensorPurplePin);  // Citim valoarea in mod analogic si o asignam variabilei signal.


  if (ThisTime - lastTimeFromCalculationBpm >= 15000 && wasBPM == true  && minBPM > 44 && maxBPM < 201) {
    if (countCalculationBPM == 0) {
      BPM = (countBP * 4);
    }

    if (countCalculationBPM > 1) {
      BPM = ((countBP * 4) + lastBPM) / 2;
    }
    countCalculationBPM = countCalculationBPM + 1;
    lastTimeFromCalculationBpm = millis();
    countBP = 0;
    lastBPM = BPM;
    Serial.println("BPM: " + String(BPM));
    afisareBPm(BPM);
  }

  if (Signal > Threshold+ 50*    && wasBPM == false) { //Cand senzorul analog primeste un semnal peste 600 se aduna o bataie, daca wasBPM este true
    countBP = countBP + 1;
    digitalWrite(LED13, HIGH);
    tone(pinAudio, 960);
    wasBPM = true;
    Serial.println("Batai inima: " + String(countBP));

    // BPM=ThisTime-LastTime;
    //BPM=int(60/(float(BPM)/1000));
    // Serial.println("BPM: " + String(BPM));

  }
  if (Signal < Threshold -50 && wasBPM == true) { //daca semnal scade sub 500 si bataie este falsa, aceasta devine adevarata
    digitalWrite(LED13, LOW);
    wasBPM = false;
    LastTime = millis();
    noTone(pinAudio);

  }

  delay(10);
}




void afisareBPm (int bpm){

String strBPM = String(bpm);
unsigned int lenghtStrBPM = strBPM.length();

int myBpmArray[lenghtStrBPM];
String bpmCaracter;
int cifraBpm;
for(int i =0; i<lenghtStrBPM; i++){

    bpmCaracter = strBPM.substring(i ,i+1);
    cifraBpm = bpmCaracter.toInt();
    myBpmArray[i] = cifraBpm;
 
}
  ecraneAfisate(myBpmArray, lenghtStrBPM, false);

}


void caseFirstNumber(int caseN){
    switch (caseN){

    case 0:
      afisareZero();
    break;
    
    case 1:
      afisareUnu();
    break;

    
    case 2:
      afisareDoi();
    break;

    case 3:
      afisareTrei();
    break;

    case 4:
      afisarePatru();
    break;

    case 5:
      afisareCinci();
    break;
    
    case 6:
      afisareSase();
    break;

    case 7:
      afisareSapte();
    break;
    
    case 8:
      afisareOpt();
    break;

    case 9:
      afisareNoua();
    break;
    
    }
  
}

void ecraneAfisate( int numereVector[], int lengthArray, boolean WasAnotherBPM){
  
  for(int i =0; i<lengthArray; i++){

      while (!WasAnotherBPM){
          digitalWrite(D1, LOW);
          digitalWrite(D2, HIGH);
          digitalWrite(D3, HIGH);
          digitalWrite(D4, HIGH);   
          caseFirstNumber(numereVector[0]);
          delay(5);
          digitalWrite(D1, HIGH);
          digitalWrite(D2, LOW);
          digitalWrite(D3, HIGH);
          digitalWrite(D4, HIGH);
          caseFirstNumber(numereVector[1]); 
          delay(1); 
           if(lengthArray==3){
          delay(5);
          digitalWrite(D1, HIGH);
          digitalWrite(D2, HIGH);
          digitalWrite(D3, LOW);
          digitalWrite(D4, HIGH);
          caseFirstNumber(numereVector[2]); 
          delay(5); 
           }
           loop();
           
      }
    
  }

  
 
  }
  
  void afisareErr(){
  digitalWrite(pinA,HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
  }
  
  void afisareZero(){
  digitalWrite(pinA,HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);   
  }
   
  void afisareUnu(){
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);   
  }

  void afisareDoi(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);     
  }

  void afisareTrei(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);     
  }

  void afisarePatru(){
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
  }
  
  void afisareCinci(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
  }
  
  void afisareSase(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
  }
  
  void afisareSapte(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
  }
  
 void afisareOpt(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
 }


  void afisareNoua(){
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
  }
  
