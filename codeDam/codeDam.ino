#include <NewPing.h>
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5);
Servo myservo;
int pos = 0;
#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
void setup() {
  mySerial.begin(115200);
  myservo.attach(9);
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  myservo.write(0);
}
void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if(sonar.ping_cm()<10 && sonar.ping_cm()>0)
  {
    SendMessage("WATER LEVEL IS HIGH DAM GOING TO OPEN");
    delay(3000);
    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if(analogRead(A3)<20)
  {
    SendMessage("LAND IS VERY DRY DAM GOING TO OPEN");
    delay(3000);
    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if(analogRead(A2)<500)
  {
    SendMessage("RAIN FALL IS DETECTED DAM WILL RELEASE ASAP");
  }
}
void SendMessage(String a)
{
  mySerial.println("AT+CMGF=1");//text mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919999999999\"\r");
  delay(1000);
  Serial.println(a);
  mySerial.println(a);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
