#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);       // called this way, it uses the default address 0x40   

#define SERVOMIN      125   // minimum pulse length count (out of 4096)
#define SERVOMAX      625   // maximum pulse length count (out of 4096)
#define NUM_CHANNELS  16
#define ANGLE_MIN     0
#define ANGLE_MAX     180
#define ANGLE_STEP    10
#define SWEEP_DELAY   100
#define RESET_DELAY   1000

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  board1.begin();
  board1.setPWMFreq(60);                  // Analog servos run at ~60 Hz updates
}

void loop()
  { for(int i=0; i<NUM_CHANNELS; i++)
      { board1.setPWM(i, 0, angleToPulse(ANGLE_MIN) );}
    delay(RESET_DELAY);

    for( int angle=ANGLE_MIN; angle<=ANGLE_MAX; angle+=ANGLE_STEP)
      { for(int i=0; i<NUM_CHANNELS; i++)
          { board1.setPWM(i, 0, angleToPulse(angle) );}
      }
    delay(SWEEP_DELAY);
  }

int angleToPulse(int ang)                             //gets angle in degree and returns the pulse width
  {  int pulse = map(ang, ANGLE_MIN, ANGLE_MAX, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
     Serial.print("Angle: ");Serial.print(ang);
     Serial.print(" pulse: ");Serial.println(pulse);
     return pulse;
  }