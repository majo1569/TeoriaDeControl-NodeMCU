#include <arduino-timer.h>

auto timer = timer_create_default(); // create a timer with default settings
int pico = 0;
int led1 = D2;
int led2 = D3;
int led3 = D4;
int led4 = D5;
int led5 = D6;
int rele = D7;
int sonido_digital = D1;
int sonido_analogico = A0;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(sonido_digital, INPUT); 

  timer.every(3000, toggle_led);

}

bool toggle_led(void *) {
  
  if (pico > 2){
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, HIGH);
    digitalWrite (led5, HIGH);
    Serial.println("ACTIVAR EL RELE AHORA");
    digitalWrite (rele, HIGH);
    delay(2000);
    digitalWrite (rele, LOW);
    delay(2000);
    Serial.print("\t");
    Serial.println("reinicie pico");
    digitalWrite (led1, LOW);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
  }
  pico=0;
  return true; // keep timer active? true
}



void loop() {
  int val_digital = digitalRead(sonido_digital);
  int val_analogico = analogRead(sonido_analogico);

  Serial.print(val_analogico);
  Serial.print("\t");
  Serial.println(val_digital);
  Serial.print("\t");
  Serial.println(pico);

  timer.tick(); // tick the timer
  if (val_analogico<700){
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, HIGH);
    digitalWrite (led5, HIGH);
    pico ++;
  }
  if (val_analogico < 735){
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, HIGH);
    digitalWrite (led5, LOW);

  }
  else if (val_analogico < 755){
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, HIGH);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
  }
    else if (val_analogico < 775){
    digitalWrite (led1, HIGH);
    digitalWrite (led2, HIGH);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
  }
    else if (val_analogico < 800){
    digitalWrite (led1, HIGH);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);
    digitalWrite (led5, LOW);
  
  }
  
}
