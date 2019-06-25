# Daily Notes
## 06/24/2019 Monday
1.1 Learned how to assemble the Shinyei with soldering and wiring
1.1.1 The frayed wires are a pain
1.1.2 Adam discovered that by seprating the wires attached to the load so that they go to both of the sensors simultaneously (as 
oppose to being wired in parallel), accident rate (breaking solder) was cut down in addition to manufacturing time
1.2 Watched one Shinyei be put together (by Adam)
1.3 Helped Adam manufacture 3 Shinyeis (I did more of the soldering while he did more of the wiring)
## 06/25/2019 Tuesday
1.1 Created Arduino accaount
1.1.1 Ardiono Username: norad42; email: nora.desmond@aol.com; password: EdD785::
1.1.2 Github Username: norad02; email: norad.desmond@aol.com; password: EdD785::
2.1 Ran Lakitha's second Github exercise
2.1.1 
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
   // print out a String of your choice 
  Serial.println("Hello MINTS: Multi-scale Integrated Sensing and Simulation");
  // Delay for 1000 miliseconds 
  delay(1000);        // delay in between reads for stability
}
3.1 Ran Likitha's third Github exercise
3.1.1 void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
4.1 Downloaded the Arduino app on my computer
