#define KROK 4
#define KIERUNEK 5
#define EN 6
#define ENK1 2
#define ENK2 3

void setup() {
  pinMode(KROK, OUTPUT);
  pinMode(KIERUNEK, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(ENK1, INPUT_PULLUP);
  pinMode(ENK2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENK2), krocz, FALLING);
}

boolean krok = false;
boolean sleep = true;
unsigned long ostatni_krok;

void krocz()
{
  sleep = true;
  ostatni_krok = millis();
  krok = true;
  if (digitalRead(ENK1))
    digitalWrite(KIERUNEK, LOW);
  else
    digitalWrite(KIERUNEK, HIGH);
}

void loop() {
  if(krok)
  {
      digitalWrite(KROK, HIGH);
      digitalWrite(KROK, LOW);
      krok = false;
  }
  
    if((ostatni_krok + 1000) < millis())
    sleep = false;
    
  digitalWrite(EN, sleep);
}
