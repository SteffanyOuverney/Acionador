int led = 2;
int button = 4;
int buzzer = 5;
int rele = 13;
bool launch = LOW;
unsigned long button_press_time;
unsigned long waiting_time = 10000;

int playing = 0;
void tone(byte pin, int freq) {
  ledcSetup(0, 2000, 8); // setup beeper
  ledcAttachPin(pin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
  playing = pin; // store pin
}
void noTone() {
  tone(playing, 0);
}

void setup() {
  button_press_time = millis();
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);//resistor interno, fixado em HIGH
  pinMode(buzzer, OUTPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(button), prepareLaunch, FALLING);//FALLING acionar a interrupção apenas quando o estado do pino for de HIGH para LOW
}

void loop() {
  if (launch) {
    playSound();

  } else {
    noTone();
  }
}

void playSound() {
  Serial.println("We will play sound on the future!");
  digitalWrite(led, launch);
  digitalWrite(rele, HIGH);
  if ((millis() - button_press_time) < waiting_time) {
    tone(buzzer, 200);
  } else {
    digitalWrite(rele, LOW);
    tone(buzzer, 300);
  }

}

void prepareLaunch() {
  if ((millis() - button_press_time) > 1000) {
    launch = !launch;
    button_press_time = millis();
  }
}
