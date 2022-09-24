int led1 = D2;
int led2 = D3;
int led3 = D4;
int led4 = D5;
int led5 = D6;
byte rele = D7;
int sonido_digital = D1;
int sonido_analogico = A0;

void setup(){
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(sonido_digital, INPUT);  
}

void loop(){
  int val_digital = digitalRead(sonido_digital);
  int val_analogico = analogRead(sonido_analogico);

  Serial.print(val_analogico);
  Serial.print("\t");
  Serial.println(val_digital);

//CONTROL DE LEDS SEGUN VOLUMEN DETECTADO
  if (val_analogico < 500)
  {
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, HIGH);
    digitalWrite (led5, HIGH);
  }
  else if (val_analogico < 600)
   {
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, HIGH);
    digitalWrite (led5, LOW);
   }
   else if (val_analogico < 700)
    {
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
    }
   else if (val_analogico < 800)
    {
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
    }
   else if (val_analogico < 900)
    {
    digitalWrite (led1, HIGH);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
    }
  else if (val_analogico < 1025)
    {
    digitalWrite (led1, LOW);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
    }
}


// CONTROL DE RELE SEGUN THRESHOLD

//  if (val_digital == HIGH)
//  {
//    digitalWrite (rele, HIGH);
//    delay(5000);
//    }
//  else
//  {
//   digitalWrite (rele, LOW);
//    }
