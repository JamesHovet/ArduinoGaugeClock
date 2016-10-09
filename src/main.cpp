/**
 * Gague Clock
 * James Hovet, Richie Santry, Anson Jones
 * Copyright 2016
 */
 #include <Servo.h>
 #include <Arduino.h>

Servo servo1;
Servo servo2;
Servo servo3;

static int button1 = 5;

static int servoPin1 = 6;
static int servoPin2 = 7;
static int servoPin3 = 8;

static float servoZeroPoint = 0.0;
static float servoMaxPoint = 1.0;

unsigned int timeCounter = 0;

enum State {running, setHours, setMinutes, setSeconds};

State currentState = running;

//Functions

float getDialPosition(){

    //TODO: implement code to get dial position from 0.0 to 1.0

    return 1.0;
}

float getSeconds(int time){

    int seconds = time % 60;

    return float(seconds * 3);

}

float getMinutes(int time){

    int minutes = (int)(time / 60);
    minutes = minutes % 60;

    return float(minutes * 3);

}

float getHours(int time){

    int hours = (int)(time / 3600);


    return float(hours);

}

// void debugPrint(int testTime){
//     std::cout << getSeconds(testTime);
//     std::cout << "\n";
//     std::cout << getMinutes(testTime);
//     std::cout << "\n";
//     std::cout << getHours(testTime);
// }


// the setup function runs once when you press reset or power the board

void setTime(State settingValue){

    // TODO: Implement the time setting code with the potentiometer. the value of the dial should directly be parented to the potentiometer so that there is never a max limit on the time that the user can set.

    switch (settingValue) {
        case setHours : {

        }
        case setMinutes : {

        }
        case setSeconds : {

        }
        default : {
            break;
        }
    }
}

bool getButton(){

    // TODO: Add code for recognizing a button press. make sure to only receive one input for one press, and do not accept another input until the button is released.

    return false;
}

void doStep(int time){
    //seconds hand
    servo1.write(getSeconds(time));
    servo2.write(getMinutes(time));
    servo3.write(getHours(time));
}

void setup() {
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
}

// the loop function runs over and over again forever
void loop() {

    if (getButton()){
        switch(currentState){
            case running : currentState = setHours;
            case setHours : currentState = setMinutes;
            case setMinutes : currentState = setSeconds;
            case setSeconds : currentState = running;
        }
    }


    if (currentState == running) {
        // servo1.write(0);
        doStep(timeCounter);
        delay(200);
        timeCounter += 1;
    } else {
        setTime(currentState);
    }
    // servo1.write(0);

}
