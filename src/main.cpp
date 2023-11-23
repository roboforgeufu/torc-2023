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

// Derrete Roda (Roboforge Zer0)
DCMotor left_motor(6, 9);
DCMotor right_motor(3, 5);
LineFollower line_follower(8, 10, 11, 12, 13);

// Sally (Forge and Furious)
// DCMotor left_motor(3, 5);
// DCMotor right_motor(6, 9);
// LineFollower line_follower(8, 10, 11, 12, 13);

// Snoopy (Roboforge F1)
// DCMotor left_motor(4, 16);
// DCMotor right_motor(5, 17);
// LineFollower line_follower(23, 22, 21, 19, 18);

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  // line_follower.refresh_values();
  // for (int i = 0; i <= 4; i++)
  // {
  //   Serial.print(line_follower.values[i]);
  // }
  // Serial.println("");
  // delay(100);

  // left_motor.set_speed(255);
  // left_motor.forward();
  // right_motor.set_speed(140);
  // right_motor.forward();

  // Serial.print(left_motor.speed);
  // Serial.println(right_motor.speed);
  // delay(2000);

  int vel_left = 255;
  int vel_right = 255;

  line_follower.refresh_values();

  for (int i = 0; i <= 4; i++)
  {
    Serial.print(line_follower.values[i]);
  }
  Serial.println("");

  if (line_follower.values[0])
  {
    vel_right = 0;
  }
  if (line_follower.values[1])
  {
    vel_right -= 200;
  }
  if (line_follower.values[3])
  {
    vel_left -= 200;
  }
  if (line_follower.values[4])
  {
    vel_left = 0;
  }

  left_motor.set_speed(vel_left);
  left_motor.forward();

  right_motor.set_speed(vel_right);
  right_motor.forward();
  delay(100);
}