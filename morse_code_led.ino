/*
A small Morse Code LED program with string parsing.

Morse Code functionality based on the Morse Code Project:
https://www.arduino.cc/education/morse-code-project

Author: Niko Tubach
Class: EN.605.715.81
*/

// Pin for LED output
const int led_pin = 13;

// Delay timing for dots / dashes
const int timing = 100;
const int dot_pause = timing;
const int part_pause = timing;
const int dash_pause = timing * 3;
const int letter_pause = timing * 3;
const int word_pause = timing * 7;

// For letters
const char *letters[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.",   // A - F
    "--.", "....", "..", ".---", "-.-", ".-..", // G - L
    "--", "-.", "---", ".--.", "--.-", ".-.",   // M - R
    "...", "-", "..-", "...-", ".--", "-..-",   // S - X
    "-.--", "--.."                              // Y & Z
};

// For Numbers
const char *numbers[] = {
    "-----", ".----", "..---", // 0 - 2
    "...--", "....-", ".....", // 3 - 5
    "-....", "--...", "---..", // 6 - 8
    "----."};                  // 9

void setup()
{
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  // Program welcome
  Serial.println("Module 1: Morse Code Converter");
  // Print the help message for instruction
  helpPrint();
}

void loop()
{
  // Check that our connection is still valid
  if (Serial.available())
  {
    // Erase any buffered strings before announcing ready for input
    Serial.flush();

    // Read in new string from user
    String s = Serial.readString();
    Serial.println("Morse code of: " + s);
    // Loop through each character in string
    for (const char c : s)
    {
      // Check for lowercase letters
      if (c >= 'a' && c <= 'z')
      {
        // Print letter for reference
        Serial.print(c);
        Serial.print(" : ");
        // Lookup pre-defined sequence chars for output
        morseLetter(letters[c - 'a']);
      }
      // Check for uppercase letters
      else if (c >= 'A' && c <= 'Z')
      {
        Serial.print(c);
        Serial.print(" : ");
        morseLetter(letters[c - 'A']);
      }
      // Check for numbers
      else if (c >= '0' && c <= '9')
      {
        Serial.print(c);
        Serial.print(" : ");
        morseLetter(numbers[c - '0']);
      }
      // Check for space
      else if (c == ' ')
      {
        // Space is just a word pause
        Serial.println(c);
        delay(word_pause);
      }
      // Check for end program command
      else if (c == '\x1A')
      {
        Serial.println("Goodbye!");
        // Delay to allow for output to serial before exit
        delay(10);
        exit(0);
      }
      else
      {
        // Bad or unknown message type
        // Or end of message
        // Print new help information
        helpPrint();
      }
    }
  }
}

void morseLetter(const char *letter)
{
  int i = 0;
  Serial.println(letter);
  // Print letter
  while (letter[i] != '\0')
  {
    outputDotDash(letter[i]);
    i++;
  }
  // Delay for time between letters
  delay(letter_pause);
}

void outputDotDash(char dotOrDash)
{
  digitalWrite(led_pin, HIGH);
  if (dotOrDash == '.')
  {
    // Dot delay
    delay(dot_pause);
  }
  else
  {
    // Dash delay
    delay(dash_pause);
  }
  digitalWrite(led_pin, LOW);
  // Delay for time between parts of a letter
  delay(part_pause);
}

void helpPrint()
{
  Serial.println("Please input the desired alphanumeric (A-z, 0-9) string to be output as Morse Code (spaces allowed).");
  Serial.println("Non-allowed characters will be skipped; please use \'ctrl+z\' (0x1a) to end the application.");
}