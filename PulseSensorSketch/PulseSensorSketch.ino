

//  Variables
int PulseSensorPurplePin = 0;        // Senzorul de puls este conectat la pinul o
int LED13 = 13;   // Ledul care va licari este legat la punul 13


int Signal;                // retine datele trimise de senzor(in mod analog). Valorile sunt intre 0 si 1024
int Threshold = 550;            // aceasta variabila determina care semnal reprezinta o bataie si care nu.
int BPM=0;        //Variabila care retine bataile pe minut
boolean wasBPM = false; //Variabila booleana care devine true la fiecare bataie a inimii
int countBP=0;    //Variabila care numara bataile inimii
int LastTime=0; 
int ThisTime;      //Variabila care retine milisecundele incepand din momentul respecctiv
int lastTimeFromCalculationBpm = 0; //Variabila care retine timpul de la ultima masurare BPM
int firstTime=0;  //Variabila care masoara timpul de la pornirea aplicatiei
int minBPM =45;   //puls minim
int maxBPM = 200; //puls maxim
boolean wasfirstPulse = false; //variabila care devine true la prima bataie de inima

// Setarile programului(ruleaza o singura data)
void setup() {
  pinMode(LED13,OUTPUT);         // pinul va aprinde si va stinge ledul la fiecare bataie a inimii(pin 13)
   Serial.begin(9600);    
   Serial.println("A pornit aparatul"); 
  // lastTimeFromCalculationBpm = millis();
 firstTime = millis();
}


// "Functie" care se repeta la infinit
void loop() {
  if (countBP >0){
    wasfirstPulse ==true;
  }
  ThisTime= millis();
  Signal = analogRead(PulseSensorPurplePin);  // Citim valoarea in mod analogic si o asignam variabilei signal.

    
   if (ThisTime - lastTimeFromCalculationBpm>=10000 && wasBPM == true  && minBPM > 44 && maxBPM <201){
        BPM = (countBP *6);
        lastTimeFromCalculationBpm = millis();
        countBP = 0;
        Serial.println("BPM: " + String(BPM));  
      }

  
   if(Signal > Threshold+50 && wasBPM == false){ //Cand senzorul analog primeste un semnal peste 600 se aduna o bataie, daca wasBPM este true
    countBP=countBP+1;
    digitalWrite(LED13,HIGH);
    wasBPM = true;
    Serial.println("Batai inima: " + String(countBP));
  
   // BPM=ThisTime-LastTime;
    //BPM=int(60/(float(BPM)/1000));
   // Serial.println("BPM: " + String(BPM));
    
   }
   if(Signal < Threshold-50 && wasBPM == true){  //daca semnal scade sub 500 si bataie este falsa, aceasta devine adevarata
    digitalWrite(LED13,LOW);
    wasBPM = false;
    LastTime=millis();

   }

delay(10);


}
