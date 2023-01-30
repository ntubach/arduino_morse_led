// Pin for LED output
const int led_pin = 13;

void setup()
{
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);  
  Serial.print("Module 1: Morse Code Converter\n");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.print("Hello World\n");
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);

  String s = Serial.readString();
  if (s == 0x1a)
  {
    // exit(0);
  }
}

