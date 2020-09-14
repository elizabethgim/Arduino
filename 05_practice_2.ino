#define PIN_LED 7
unsigned int count, toggle,delaytime;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200); // Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  count = 0, toggle = 1;
  delaytime=1000;
  digitalWrite(PIN_LED, 0); // turn on LED.
}

void loop() {
  Serial.println(++count); 
  toggle = toggle_state(toggle); //toggle LED value.
  digitalWrite(PIN_LED, toggle); // update LED status.
  delay(delaytime); 
  delaytime=100;
  
  if(count == 12)
    while(1){digitalWrite(PIN_LED, toggle);}
}

int toggle_state(int toggle) {
  if(toggle==0)
    return 1;
  else
    return 0;
}
