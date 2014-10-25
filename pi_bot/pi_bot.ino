//#include <aJSON.h>
#include <Servo.h>
#include <AFMotor.h>

// json paramerter
char Orders[3];
char current_mode = 't';

//dc motor controls
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(1, MOTOR12_64KHZ);

// ping sensor pins 
int tri_pin = 14;
int echo_pin = 15;

// servo for ping sensor
unsigned long last_print = 0;
Servo servo;
int servo_pin = 10;

// modes
#define Contorl_Mode 0
#define Dir          1#define Time         2
#define min_distance 20 // minimubum distance to be considered as a obstrical

int right_distance = 0;
 int left_distance = 0;

void setup(){
  
 Serial.begin(9600);
 // inilize the json objects
 // a- autonomous, m-manual 
 Orders[Contorl_Mode] = 'a';
 // f- forward, r- right, l -left, b- backwords
 Orders[1] = 'f';
 Orders[2] = '1';
 
 servo.attach(servo_pin);
}

void loop(){
  if(Serial.available() > 0){
    Serial.println("revceivin info over serival");
    Serial.readBytesUntil('/r',Orders,3);
    // check the control mode 
    if(Orders[Contorl_Mode] == 'a'){
      if(current_mode != 'a'){
        current_mode = 'a';
        activate_autonomous_mode();
      }
    }
      // do what ever neede to automatic
    }
    
    if(Orders[Contorl_Mode] == 'm'){
      current_mode = 'm';
      
      // I have the power,, no need of stupid ord
    }
    
  }
}


//method to get distance from the nearest object
int get_distance()
{
  int dis,duration;
  digitalWrite(tri_pin,HIGH);
  delay(150);
  digitalWrite(tri_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  int obj_dist = (duration/2)/29.1;
  Serial.println("distance from nearest obstrical is" + obj_dist);
  Serial.println(obj_dist);
  delay(300);
  return obj_dist;
}

//autonomous mode
void activate_autonomous_mode(){
  Serial.println("in automousmode");
  servo.write(90);
  if(get_distance() > min_distance){
  //  go_forward();
    delay(1000);
   // all_stop();
  }
  else{
    //lok right
    servo.write(0);
    delay(500);
    left_distance = get_distance();
    // look left
    servo.write(180);
    delay(500);
    right_distance = get_distance();
    //turn left
    if(left_distance > right_distance){
      turn_left();
    }
    // turn right
    else{
      turn_right();
    }
   
  }
}

// turn left
void turn_left()
{
motor1.run(FORWARD);
motor2.run(BACKWARD);
delay(400);
stop();
}

// turn right
void turn_right()
{
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(500);
stop();
}

//all stop
void stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
  
