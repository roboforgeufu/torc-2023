#include <Arduino.h>

class DCMotor
{
public:
  int speed = 255;
  int pin1;
  int pin2;

  DCMotor(int in1, int in2)
  {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void set_speed(int spd)
  {
    speed = spd;
  }

  void forward()
  {
    analogWrite(pin1, speed);
    digitalWrite(pin2, LOW);
  }

  void backward()
  {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, speed);
  }

  void stop()
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  void brake()
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
  }
};

class LineFollower
{
public:
  int ir1, ir2, ir3, ir4, ir5;
  int values[5];

  LineFollower(int port1, int port2, int port3, int port4, int port5)
  {
    ir1 = port1;
    ir2 = port2;
    ir3 = port3;
    ir4 = port4;
    ir5 = port5;
    pinMode(ir1, INPUT);
    pinMode(ir2, INPUT);
    pinMode(ir3, INPUT);
    pinMode(ir4, INPUT);
    pinMode(ir5, INPUT);
  }

  void refresh_values()
  {
    int ports[] = {ir1, ir2, ir3, ir4, ir5};
    for (int i = 0; i <= 4; i++)
    {
      values[i] = digitalRead(ports[i]);
    }
  }
};

// DCMotor left_motor(3,5);
LineFollower line_follower(2, 3, 4, 5, 6);

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  line_follower.refresh_values();
  for (int i = 0; i <= 4; i++)
  {
    Serial.print(line_follower.values[i]);
  }
  Serial.println("");
  delay(100);

  // left_motor.set_speed(255);
  // left_motor.forward();
  // delay(2000);

  // left_motor.set_speed(100);
  // left_motor.backward();
  // delay(2000);

  // left_motor.stop();
  // delay(2000);

  // left_motor.brake();
  // delay(2000);
}