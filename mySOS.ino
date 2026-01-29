/*
  mySOS

  Turns an LED on in an Morse code SOS pattern and writes each letter to the Serial Monitor

  Nested loops create a roughly 3 minute set of 1 minute signal bursts while each letter is
  printed to the port. Each word is printed on a separate line and messages are printed during 
  a short pause at the end of each set.  The whole pattern repeats after a 30 second break.

  created:  24 Jan 2026
  by:       bitKiva107
  IDE:      2.3.7
  board:    UNO R3
  modified: 29 Jan 2026 - bitKiva107
  
*/
void setup() {
  Serial.begin(9600);            // the setup routine runs once when you press reset:
  pinMode(LED_BUILTIN, OUTPUT);  // initialize digital pin LED_BUILTIN as an output.
}
// the loop routine runs over and over again forever:
void loop() {
  String message = String("Incoming message ...");  // Message header
  String sletter = String("S");                     // "S" letter
  String oletter = String("O");                     // "O" letter
  String paused = String("Message paused ...");     // Message paused
  String resumed = String("Message resumes ...");   // Message resumes
  String end_message = String("Message ends");      // Foo

  int dit = 125;           // set the length (milliseconds) of a "dit" (a short pulse)
  int dah = (3 * dit);     // set the length (milliseconds) of a "dah" (a long pulse)
  int unit = dit;          // set the length (milliseconds) of a space within a letter
  int lspace = (3 * dit);  // set the length (milliseconds) of a space between letters
  int wspace = (7 * dit);  // set the length (milliseconds) of a space between words
  int pause = (20 * dit);  // a 5 second pause

  delay(pause);             // ~5 seconds so you can open the SerialMonitor
  Serial.println(message);  // begin the message block
  delay(wspace);
  for (int g = 0; g < 3; g++) {
    for (int h = 0; h < 13; h++) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
        delay(dah);                       // wait for a dah space
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
        delay(unit);                      // wait for a unit space
      }
      // print out the letter
      Serial.print(sletter);
      delay(lspace - unit);

      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
        delay(dit);                       // wait for a dit space
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
        delay(unit);                      // wait for a unit space
      }
      // print out the letter
      Serial.print(oletter);
      delay(lspace - unit);

      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
        delay(dah);                       // wait for a dah space
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
        delay(unit);                      // wait for a unit space
      }
      // print out the last letter and CR/LF
      Serial.println(sletter);
      delay(wspace - unit);
    }
    delay(wspace);
    Serial.println(paused);  // begin the pause/resume block
    delay(5000);
    Serial.println(resumed);
  }
  delay(wspace * 2);
  Serial.println(end_message);  // announce the message end
  Serial.println();
  delay(30000);  // wait 30 seconds and begin the block again
}
