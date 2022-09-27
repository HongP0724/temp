#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello World!");
  count=0,toggle=0;
  digitalWrite(PIN_LED, toggle);
  delay(1000);
}
void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    while(count<5)
    {
      Serial.println(++count);
      toggle = toggle_state(toggle);
      digitalWrite(PIN_LED,toggle);
      delay(100);
      toggle=toggle_state(toggle);
      digitalWrite(PIN_LED,toggle);
      delay(100);
    }
    digitalWrite(PIN_LED,1);
  }
}

int toggle_state(int toggle)
{
  return (toggle+1)%2;
}
