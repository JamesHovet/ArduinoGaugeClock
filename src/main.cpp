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

int getDialPosition(){

    //TODO: implement code to get dial position from 0 to 60

    return 30;
}

int getDialPositionInHours(){

    //TODO: implement code to get dial position from 0 to 24

    return 12;
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




void setTime(State settingValue){

    int hoursToAdd = (int)(timeCounter / 3600);
    int minutesToAdd = ((int)(timeCounter / 60)) % 60;
    int secondsToAdd = timeCounter % 60;

    switch (settingValue) {
        case setHours : {
            servo3.write((int)((float)getDialPositionInHours() * 7.5));

            timeCounter = getDialPositionInHours() * (60*60) + minutesToAdd * (60) + secondsToAdd * (1);
        }
        case setMinutes : {
            servo2.write(getDialPosition() * 3);

            timeCounter = hoursToAdd * (60*60) + getDialPosition() * (60) + secondsToAdd * (1);

        }
        case setSeconds : {
            servo1.write(getDialPosition() * 3);

            timeCounter = hoursToAdd * (60*60) + minutesToAdd * (60) + getDialPosition() * (1);

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
