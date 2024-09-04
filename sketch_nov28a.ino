#include <Stepper.h>   // library for stepper motor
#include <Servo.h>

// Pins for the 1st Motor
const int stepPinM1 = 2;  
const int dirPinM1 = 3;  

// Pins for 2nd Motor 
const int stepPinM2 = 9; 
const int dirPinM2 = 8; 

// Pins for 3rd Motor
const int stepPinM3 = 12;  
const int dirPinM3 = 11;

// 1st Joystick
const int joyXPin = A0;     //Controll 1st Motor
const int joyYPin = A1;    //Controll 2nd Motor

// 2nd Joystick
const int joyXPin1 = A2;    // Control 3rd Motor
const int joyYPin1 = A3;   // Controll Stepper motor

const int switchPinM1 = 4;    // Pin for the slide switch Motor1
const int switchPinM2 = 10;  // Pin for the slide switch  Motor2
const int switchPinM3 = 7;  // Pin for the slide switch   Motor3
const int switchPinP = 5;  // Pin for the Push Button     Play Function
const int switchPinD = 6; // Pin for the slide switch     Delete Values 


Stepper myStepperM1(200, stepPinM1, dirPinM1);   // Intialize 1st Motor
Stepper myStepperM2(200, stepPinM2, dirPinM2);  // Intialize 2nd Motor
Stepper myStepperM3(200, stepPinM3, dirPinM3); // Intialize 3rd Motor

Servo myServo; //for servo motor

int stepCountM1 = 0; // Variable to store the step count for Motor 1
int clockwiseStepsM1 = 0; // Variable to store the total clockwise steps Motor1
int counterclockwiseStepsM1 = 0; // Variable to store the total counterclockwise steps Motor1
int clockwisePlayM1 =0;   // Variable to store the total clockwise steps Motor1 for play function
int anticlockwisePlayM1 =0; // Variable to store the total counterclockwise steps Motor1 for play function


int stepCountM2 = 0; // Variable to store the step count Motor2
int clockwiseStepsM2 = 0; // Variable to store the total clockwise steps Motor2
int counterclockwiseStepsM2 = 0; // Variable to store the total counterclockwise steps Motor2
int clockwisePlayM2 =0;  // Variable to store the total clockwise steps Motor2 for play function
int anticlockwisePlayM2 =0; // Variable to store the total counterclockwise steps Motor2 for play function

int stepCountM3 = 0; // Variable to store the step count Motor3
int clockwiseStepsM3 = 0; // Variable to store the total clockwise steps Motor3
int counterclockwiseStepsM3 = 0; // Variable to store the total counterclockwise steps Motor3
int clockwisePlayM3 =0;  // Variable to store the total clockwise steps Motor3 for play function
int anticlockwisePlayM3 =0; // Variable to store the total counterclockwise steps Motor3 for play function

int angleCountClock=0;
int anglePlayClock=0;
int angleCountAntiClock=0;
int anglePlayAntiClock=0;

int axsisJoy1=0;  // Store value for Joystick1  for play function
int axsisBoth=0;  // store value for joystick2  for play function 
int axsisJoy2=0; // store value for both joystick for play function

bool isCountingM1 = false; // Flag to control step counting Motor1
bool isCountingM2 = false; // Flag to control step counting Motor2
bool isCountingM3 = false; // Flag to control step counting Motor3
bool isCountingP = false;  // Flag to control step counting Play Button
bool isCountingD = false;  // Flag to control step counting Delete Button


bool initialDirectionM1 = false; // Flag to track the initial direction for Motor1
bool isFirstMoveM1 = true; // Flag to track the first move for Motor2

bool initialDirectionM2 = false; // Flag to track the initial direction for Motor2
bool isFirstMoveM2 = true; // Flag to track the first move  for Motor 2

bool initialDirectionM3 = false; // Flag to track the initial direction Motor3
bool isFirstMoveM3 = true; // Flag to track the first move Motor3

bool initialDirectionS = false; // Flag to track the initial direction for stepper
bool isFirstMoveS = true; // Flag to track the first move for stepper

void setup()
{
  myStepperM1.setSpeed(60);
  myStepperM2.setSpeed(60);
  myStepperM3.setSpeed(60);
  myServo.attach(13);

  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);

  pinMode(joyXPin1, INPUT);
  pinMode(joyYPin1, INPUT);

  pinMode(stepPinM1, OUTPUT);
  pinMode(dirPinM1, OUTPUT);

  pinMode(stepPinM2, OUTPUT);
  pinMode(dirPinM2, OUTPUT);

  pinMode(stepPinM3, OUTPUT);
  pinMode(dirPinM3, OUTPUT);

  pinMode(switchPinM1, INPUT_PULLUP); // Initialize the switch pin with an internal pull-up resistor
  pinMode(switchPinP, INPUT_PULLUP);
  pinMode(switchPinD, INPUT_PULLUP);
  pinMode(switchPinM2, INPUT_PULLUP);
  pinMode(switchPinM3, INPUT_PULLUP);
  
  Serial.begin(9600); // Initialize serial communication for printing step count
}
void stepper() // function for stepper Motor motion
{
  int joyY1 = analogRead(joyYPin1);
  int servoPos;

  if (joyY1 > 512) 
  { // assuming the midpoint of the Y-axis range is 512
    myServo.write(180); // map Y-axis values to servo positions between 90 and 180
  } 
  else if(joyY1<512) 
  {
    myServo.write(90); // map Y-axis values to servo positions between 180 and 90
  }
}
void stepperPlay()
{
  myServo.write(180);
  delay(2000);
  myServo.write(90);
}

void Motor1()  // Motion Function for Motor 1
{
  int joyX = analogRead(joyXPin);
  if(joyX > 512)
  {
    // Set the direction of the stepper motor
    digitalWrite(dirPinM1, HIGH); // Clockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < 1; i++) {
      digitalWrite(stepPinM1, HIGH);
      delay(5);
      digitalWrite(stepPinM1, LOW);
      delay(5);
      if (isCountingM1) {
        stepCountM1++; // Increment step count for clockwise direction if counting is enabled
        clockwisePlayM1=clockwiseStepsM1++; // Increment total clockwise steps
      }
      if (isFirstMoveM1) {
        initialDirectionM1 = true; // Set the initial direction to clockwise
        isFirstMoveM1 = false;
      }
    }
  }

  else if(joyX < 512)
  {
    // Change the direction of the stepper motor
    digitalWrite(dirPinM1, LOW); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < 1; i++) {
      digitalWrite(stepPinM1, HIGH);
      delay(5);
      digitalWrite(stepPinM1, LOW);
      delay(5);
      if (isCountingM1) {
        stepCountM1--; // Decrement step count for counterclockwise direction if counting is enabled
        anticlockwisePlayM1=counterclockwiseStepsM1++; // Increment total counterclockwise steps
      }
      if (isFirstMoveM1) {
        initialDirectionM1 = false; // Set the initial direction to counterclockwise
        isFirstMoveM1 = false;
      }
    }
  }
  else
  {
    digitalWrite(stepPinM1, LOW);
  }

  if (initialDirectionM1) {
    
  } else if (!initialDirectionM1 && !isFirstMoveM1) {
    
  }
}

void Motor2() // Motion Function for Motor 2
{
  int joyY = analogRead(joyYPin);
  if(joyY > 512)
  {
    // Set the direction of the stepper motor
    digitalWrite(dirPinM2, HIGH); // Clockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < 1; i++) {
      digitalWrite(stepPinM2, HIGH);
      delay(5);
      digitalWrite(stepPinM2, LOW);
      delay(5);
      if (isCountingM2) {
        stepCountM2++; // Increment step count for clockwise direction if counting is enabled
        clockwisePlayM2=clockwiseStepsM2++; // Increment total clockwise steps
      }
      if (isFirstMoveM2) {
        initialDirectionM2 = true; // Set the initial direction to clockwise
        isFirstMoveM2 = false;
      }
    }
  }

  else if(joyY < 512)
  {
    // Change the direction of the stepper motor
    digitalWrite(dirPinM2, LOW); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < 1; i++) 
    {
      digitalWrite(stepPinM2, HIGH);
      delay(5);
      digitalWrite(stepPinM2, LOW);
      delay(5);
      if (isCountingM2) {
        stepCountM2--; // Decrement step count for counterclockwise direction if counting is enabled
        anticlockwisePlayM2=counterclockwiseStepsM2++; // Increment total counterclockwise steps
      }
      if (isFirstMoveM2) {
        initialDirectionM2 = false; // Set the initial direction to counterclockwise
        isFirstMoveM2 = false;
      }
    }
  }
  else
  {
    digitalWrite(stepPinM2, LOW);
  }

  if (initialDirectionM2) {
  
  } else if (!initialDirectionM2 && !isFirstMoveM2) {
  
  }
}

void Motor3() // Motion Function for Motor 3
{
  int joyX1 = analogRead(joyXPin1);
  if(joyX1 > 512)
  {
    // Set the direction of the stepper motor
    digitalWrite(dirPinM3, HIGH); // Clockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < 1; i++) {
      digitalWrite(stepPinM3, HIGH);
      delay(5);
      digitalWrite(stepPinM3, LOW);
      delay(5);
      if (isCountingM3) {
        stepCountM3++; // Increment step count for clockwise direction if counting is enabled
        clockwisePlayM3=clockwiseStepsM3++; // Increment total clockwise steps
      }
      if (isFirstMoveM3) {
        initialDirectionM3 = true; // Set the initial direction to clockwise
        isFirstMoveM3 = false;
      }
    }
  }

  else if(joyX1 < 512)
  {
    // Change the direction of the stepper motor
    digitalWrite(dirPinM3, LOW); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < 1; i++) {
      digitalWrite(stepPinM3, HIGH);
      delay(5);
      digitalWrite(stepPinM3, LOW);
      delay(5);
      if (isCountingM3) {
        stepCountM3--; // Decrement step count for counterclockwise direction if counting is enabled
        anticlockwisePlayM3=counterclockwiseStepsM3++; // Increment total counterclockwise steps
      }
      if (isFirstMoveM3) {
        initialDirectionM3 = false; // Set the initial direction to counterclockwise
        isFirstMoveM3 = false;
      }
    }
  }
  else
  {
    digitalWrite(stepPinM3, LOW);
  }

  if (initialDirectionM3) {
    
  } else if (!initialDirectionM3 && !isFirstMoveM3) {
  }
}

void ClockWisePlayM1() // for Clockwise motion of Motor1
{
  digitalWrite(dirPinM1, HIGH); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < clockwisePlayM1; i++) {
      digitalWrite(stepPinM1, HIGH);
      delay(5);
      digitalWrite(stepPinM1, LOW);
      delay(5);
      
    }
}

void ClockWisePlayM2() // for Clockwise motion of Motor2
{
  
  digitalWrite(dirPinM2, HIGH); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < clockwisePlayM2; i++) {
      digitalWrite(stepPinM2, HIGH);
      delay(5);
      digitalWrite(stepPinM2, LOW);
      delay(5);
      
    }
}

void ClockWisePlayM3() // for Clockwise motion of Motor3
{
  digitalWrite(dirPinM3, HIGH); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < clockwisePlayM3; i++) {
      digitalWrite(stepPinM3, HIGH);
      delay(5);
      digitalWrite(stepPinM3, LOW);
      delay(5);
      
    }
}

void AntiClockWisePlayM1() // for Anticlockwise motion of Motor1
{
  digitalWrite(dirPinM1, LOW); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < anticlockwisePlayM1; i++) 
    {
      digitalWrite(stepPinM1, HIGH);
      delay(5);
      digitalWrite(stepPinM1, LOW);
      delay(5);
      
    }
}

void AntiClockWisePlayM2()  //for Anticlockwise motion of Motor2
{
  
  digitalWrite(dirPinM2, LOW); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < anticlockwisePlayM2; i++) 
    {
      digitalWrite(stepPinM2, HIGH);
      delay(5);
      digitalWrite(stepPinM2, LOW);
      delay(5);
      
    }
}

void AntiClockWisePlayM3()  //for Anticlockwise motion of Motor3
{
  digitalWrite(dirPinM3, LOW); // Counterclockwise

    // Move the stepper motor 1 steps
    for (int i = 0; i < anticlockwisePlayM3; i++) 
    {
      digitalWrite(stepPinM3, HIGH);
      delay(5);
      digitalWrite(stepPinM3, LOW);
      delay(5);
      
    }
}

void play()  // Use to Play stored Position
{
  if(isCountingP== true)  // Check Weather Play Button is on or not
  {
    if((axsisBoth==1)||(axsisBoth==2)) //if Joystick1 moves first than this condition will work
    {
      if(axsisJoy1==1)  // if xaxsis of joystick1 gives the values first than this condition will work
      {
        // Xaxsis of Joystick 1
        if (initialDirectionM1) 
        {
          ClockWisePlayM1();
          delay(3000);
          AntiClockWisePlayM1();
          delay(3000);
        }  
        else if (!initialDirectionM1 && !isFirstMoveM1) 
        {
          AntiClockWisePlayM1();
          delay(3000);
          ClockWisePlayM1();
          delay(3000);
        }
        delay(1000);

        // Yaxsis of Joystick 1
        if (initialDirectionM2) 
        {
          ClockWisePlayM2();
          delay(3000);
          AntiClockWisePlayM2();
          delay(3000);
        }  
        else if (!initialDirectionM2 && !isFirstMoveM2) 
        {
          AntiClockWisePlayM2();
          (3000);
          ClockWisePlayM2();
          delay(3000);
        }

        delay(3000);

        // Once Joystick Complete now Joystick 2 starts
        if(axsisJoy2==1)   // if Xaxsis of joystick2 gives values first than this condition will work
        {
          // Xaxsis of Joystick 2
          if (initialDirectionM3) 
          {
            ClockWisePlayM3();
            delay(3000);
            AntiClockWisePlayM3();
            delay(3000);
          }  
          else if (!initialDirectionM3 && !isFirstMoveM3) 
          {
            AntiClockWisePlayM3();
            delay(3000);
            ClockWisePlayM3();
            delay(3000);
          }
          delay(3000);

          // Yaxsis of Joystick 2

          stepperPlay();
        }
        else if(axsisJoy2==2) // if Yaxsis of joystick2 gives values first than this condition will work
        {
          // Yaxsis of Joystick2
          stepperPlay();
          delay(3000);

          // Xaxsis of joystick2
          if (initialDirectionM3) 
          {
            ClockWisePlayM3();
            delay(3000);
            AntiClockWisePlayM3();
            delay(3000);
          }  
          else if (!initialDirectionM3 && !isFirstMoveM3) 
          {
            AntiClockWisePlayM3();
            delay(3000);
            ClockWisePlayM3();
            delay(3000);
          }
        }
      }
      
      if(axsisJoy1==2) // if Yaxsis of joystick1 gives values first than this condition will work
      {
        // Y axsis of Joystick1
        if (initialDirectionM2) 
        {
          ClockWisePlayM2();
          delay(3000);
          AntiClockWisePlayM2();
          delay(3000);
        }  
        else if (!initialDirectionM2 && !isFirstMoveM2) 
        {
          AntiClockWisePlayM2();
          (3000);
          ClockWisePlayM2();
          delay(3000);
        }
        delay(3000);
        // X axsis of Joystick1
        if (initialDirectionM1) 
        {
          ClockWisePlayM1();
          delay(3000);
          AntiClockWisePlayM1();
          delay(3000);
        }  
        else if (!initialDirectionM1 && !isFirstMoveM1) 
        {
          AntiClockWisePlayM1();
          delay(3000);
          ClockWisePlayM1();
          delay(3000);
        }
        delay(3000);

        // Once Joystick Complete now Joystick 2 starts
        if(axsisJoy2==1) // if Xaxsis of Joystick2 Moves first
        {
          // Xaxsis of Joystick 2
          if (initialDirectionM3) 
          {
            ClockWisePlayM3();
            delay(3000);
            AntiClockWisePlayM3();
            delay(3000);
          }  
          else if (!initialDirectionM3 && !isFirstMoveM3) 
          {
            AntiClockWisePlayM3();
            delay(3000);
            ClockWisePlayM3();
            delay(3000);
          }
          delay(3000);

          // Yaxsis of Joystick 2
          stepperPlay();
        }
        else if(axsisJoy2==2) // if Yaxsis of Joystick2 Moves first
        {
          // Yaxsis of Joystick2
          stepperPlay();
          delay(3000);

          // Xaxsis of joystick2
          if (initialDirectionM3) 
          {
            ClockWisePlayM3();
            delay(3000);
            AntiClockWisePlayM3();
            delay(3000);
          }  
          else if (!initialDirectionM3 && !isFirstMoveM3) 
          {
            AntiClockWisePlayM3();
            delay(3000);
            ClockWisePlayM3();
            delay(3000);
          }
        }
      }
    }

    if((axsisBoth==3)||(axsisBoth==4)) //if Joystick2 moves first than this condition will work
    {
      if(axsisJoy2==1) // if Xaxsis of joystick2 gives the values first than this condition will work
      {
        // Xaxsis of Joystick 2
        if (initialDirectionM3) 
        {
          ClockWisePlayM3();
          delay(3000);
          AntiClockWisePlayM3();
          delay(3000);
        }  
        else if (!initialDirectionM3 && !isFirstMoveM3) 
        {
          AntiClockWisePlayM3();
          delay(3000);
          ClockWisePlayM3();
          delay(3000);
        }
        delay(3000);

        // Yaxsis of Joystick 2
        stepperPlay();
        delay(3000);

          // After Joystick2 ,  Joystick 1 will start
        if(axsisJoy1==1)  //Check axsis of 1st Joystick
        {
          // Xaxsis of Joystick1
          if (initialDirectionM1) 
          {
            ClockWisePlayM1();
            delay(3000);
            AntiClockWisePlayM1();
            delay(3000);
          }  
          else if (!initialDirectionM1 && !isFirstMoveM1) 
          {
            AntiClockWisePlayM1();
            delay(3000);
            ClockWisePlayM1();
            delay(3000);
          }
          delay(1000);

          // Yaxsis of Joystick 1
          if (initialDirectionM2) 
          {
            ClockWisePlayM2();
            delay(3000);
            AntiClockWisePlayM2();
            delay(3000);
          }  
          else if (!initialDirectionM2 && !isFirstMoveM2) 
          {
            AntiClockWisePlayM2();
            delay(3000);
            ClockWisePlayM2();
            delay(3000);
          }
        }

        if(axsisJoy1==2) //Check axsis of 1st Joystick
        {
          // Yaxsis of Joystick1
          if (initialDirectionM2) 
          {
            ClockWisePlayM2();
            delay(3000);
            AntiClockWisePlayM2();
            delay(3000);
          }  
          else if (!initialDirectionM2 && !isFirstMoveM2) 
          {
            AntiClockWisePlayM2();
            delay(3000);
            ClockWisePlayM2();
            delay(3000);
          }
          delay(1000);

          // Xaxsis of Joystick 1
          if (initialDirectionM1) 
          {
            ClockWisePlayM1();
            delay(3000);
            AntiClockWisePlayM1();
            delay(3000);
          }  
          else if (!initialDirectionM1 && !isFirstMoveM1) 
          {
            AntiClockWisePlayM1();
            delay(3000);
            ClockWisePlayM1();
            delay(3000);
          }
        }
      }

      if(axsisJoy2==2) // if Yaxsis of joystick2 gives values first than this condition will work
      {
        // Yaxsis of Joystick 2
        stepperPlay();
        delay(3000);

        // Xaxsis of Joystick 2
        if (initialDirectionM3) 
        {
          ClockWisePlayM3();
          delay(3000);
          AntiClockWisePlayM3();
          delay(3000);
        }  
        else if (!initialDirectionM3 && !isFirstMoveM3) 
        {
          AntiClockWisePlayM3();
          delay(3000);
          ClockWisePlayM3();
          delay(3000);
        }
        delay(3000);
        
        // After Joystick2 ,  Joystick 1 will start
        if(axsisJoy1==1)  //Check axsis of 1st Joystick
        { 
          // Xaxsis of Joystick1
          if (initialDirectionM1) 
          {
            ClockWisePlayM1();
            delay(3000);
            AntiClockWisePlayM1();
            delay(3000);
          }  
          else if (!initialDirectionM1 && !isFirstMoveM1) 
          {
            AntiClockWisePlayM1();
            delay(3000);
            ClockWisePlayM1();
            delay(3000);
          }
          delay(1000);

          // Yaxsis of Joystick 1
          if (initialDirectionM2) 
          {
            ClockWisePlayM2();
            delay(3000);
            AntiClockWisePlayM2();
            delay(3000);
          }  
          else if (!initialDirectionM2 && !isFirstMoveM2) 
          {
            AntiClockWisePlayM2();
            delay(3000);
            ClockWisePlayM2();
            delay(3000);
          }
        }

        if(axsisJoy1==2) //Check axsis of 1st Joystick
        {
          //Yaxsis of Joystick1
          if (initialDirectionM2) 
          {
            ClockWisePlayM2();
            delay(3000);
            AntiClockWisePlayM2();
            delay(3000);
          }  
          else if (!initialDirectionM2 && !isFirstMoveM2) 
          {
            AntiClockWisePlayM2();
            delay(3000);
            ClockWisePlayM2();
            delay(3000);
          }
          delay(1000);

          // Xaxsis of Joystick 1
          if (initialDirectionM1) 
          {
            ClockWisePlayM1();
            delay(3000);
            AntiClockWisePlayM1();
            delay(3000);
          }  
          else if (!initialDirectionM1 && !isFirstMoveM1) 
          {
            AntiClockWisePlayM1();
            delay(3000);
            ClockWisePlayM1();
            delay(3000);
          }
        }
      }
    }
  }
}
void CheckBothJoy() // Check Which Joystick give values first
{
  int joystickXValue7 = analogRead(joyXPin);
  int joystickYValue7 = analogRead(joyYPin);

  // Map the values to a more intuitive range (-512 to 512)
  int mappedXValue7 = map(joystickXValue7, 0, 1023, -512, 512);
  int mappedYValue7 = map(joystickYValue7, 0, 1023, -512, 512);

  // Check which axis moves first
  if (abs(mappedXValue7) > abs(mappedYValue7)) 
  {
    if(axsisBoth == 0)
    {
      axsisBoth=1;
    }
    else
    {
      axsisBoth = axsisBoth;
    }
  } 
  else if (abs(mappedYValue7) > abs(mappedXValue7)) 
  {
    if(axsisBoth == 0)
    {
      axsisBoth=2;
    }
    else
    {
      axsisBoth = axsisBoth;
    }
    
  }

  int joystickXValue8 = analogRead(joyXPin1);
  int joystickYValue8 = analogRead(joyYPin1);
  int mappedXValue8 = map(joystickXValue8, 0, 1023, -512, 512);
  int mappedYValue8 = map(joystickYValue8, 0, 1023, -512, 512);

  // Check which axis moves first
  if (abs(mappedXValue8) > abs(mappedYValue8)) 
  {
    if(axsisBoth == 0)
    {
      axsisBoth=3;
    }
    else
    {
      axsisBoth = axsisBoth;
    }
  } 
  else if (abs(mappedYValue8) > abs(mappedXValue8)) 
  {
    if(axsisBoth == 0)
    {
      axsisBoth=4;
    }
    else
    {
      axsisBoth = axsisBoth;
    }
    
  }
}

void checkaxsisJoy1() // check which axsis of Joystick1 give value first
{
  int joystickXValue = analogRead(joyXPin);
  int joystickYValue = analogRead(joyYPin);

  // Map the values to a more intuitive range (-512 to 512)
  int mappedXValue = map(joystickXValue, 0, 1023, -512, 512);
  int mappedYValue = map(joystickYValue, 0, 1023, -512, 512);

  if (abs(mappedXValue) > abs(mappedYValue)) {
    if(axsisJoy1 == 0)
    {
      axsisJoy1=1;
    }
    else
    {
      axsisJoy1 = axsisJoy1;
    }
  } 
  else if (abs(mappedYValue) > abs(mappedXValue)) {
    if(axsisJoy1 == 0)
    {
      axsisJoy1=2;
    }
    else
    {
      axsisJoy1 = axsisJoy1;
    }
    
  }
}

void checkaxsisJoy2() // check which axsis of Joystick2 give value first
{
  int joystickXValue3 = analogRead(joyXPin1);
  int joystickYValue3 = analogRead(joyYPin1);

  // Map the values to a more intuitive range (-512 to 512)
  int mappedXValue3 = map(joystickXValue3, 0, 1023, -512, 512);
  int mappedYValue3 = map(joystickYValue3, 0, 1023, -512, 512);

  if (abs(mappedXValue3) > abs(mappedYValue3)) {
    if(axsisJoy2 == 0)
    {
      axsisJoy2=1;
    }
    else
    {
      axsisJoy2 = axsisJoy2;
    }
  } 
  else if (abs(mappedYValue3) > abs(mappedXValue3)) {
    if(axsisJoy2 == 0)
    {
      axsisJoy2=2;
    }
    else
    {
      axsisJoy2 = axsisJoy2;
    }
  }
}

void Delete() // Will delete stored values
{
  if(isCountingD == false)
  {
    clockwisePlayM1 = 0;
    anticlockwisePlayM1 = 0;
    clockwiseStepsM1 = 0;
    counterclockwiseStepsM1 = 0;
    stepCountM1 = 0;

    clockwisePlayM2 = 0;
    anticlockwisePlayM2 = 0;
    clockwiseStepsM2 = 0;
    counterclockwiseStepsM2 = 0;
    stepCountM2 = 0;

    clockwisePlayM3 = 0;
    anticlockwisePlayM3 = 0;
    clockwiseStepsM3 = 0;
    counterclockwiseStepsM3 = 0;
    stepCountM3 = 0;

    axsisJoy1=0;
    axsisJoy2=0;
    axsisBoth=0;

    isFirstMoveM1 = true;
    isFirstMoveM2 = true;
    isFirstMoveM3 = true;
  }
}


void playB()  // for Play Function
{
  int switchStateP = digitalRead(switchPinP);
  if (switchStateP == HIGH) {
    isCountingP = true;
  } else {
    isCountingP = false;
  }
}
void deleteB() // for Delete Function
{
  int switchStateD = digitalRead(switchPinD);
  if (switchStateD == HIGH) {
    isCountingD = true;
  } else {
    isCountingD = false;
  }
}
void M1B()  // to store the values or not of motor1
{
  int switchStateM1 = digitalRead(switchPinM1);
  if (switchStateM1 == LOW) {
    isCountingM1 = true;
  } else {
    isCountingM1 = false;
  }
}
void M2B() // to store the values or not of motor2
{
  int switchStateM2 = digitalRead(switchPinM2);
  if (switchStateM2 == LOW) {
    isCountingM2 = true;
  } else {
    isCountingM2 = false;
  }
}
void M3B()  // to store the values or not of motor3
{
  int switchStateM3 = digitalRead(switchPinM3);
  if (switchStateM3 == LOW) {
    isCountingM3 = true;
  } else {
    isCountingM3 = false;
  }
}
void loop()
{
  
  stepper();
  M1B();
  Motor1();
  M2B();
  Motor2();
  M3B();
  Motor3();
  checkaxsisJoy1();
  checkaxsisJoy2();
  CheckBothJoy();
  playB();
  play();
  
  deleteB();
  Delete();

  delay(100);

}