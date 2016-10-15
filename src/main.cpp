/**
 * Gague Clock
 * James Hovet, Richie Santry, Anson Jones
 * Copyright 2016
 */
 #include <Servo.h>
 #include <Arduino.h>
 #include <string.h>

Servo servo1;
Servo servo2;
Servo servo3;


int buttonState = 0;
const int buttonPin = 2;
const int ledPin =  13;

const int button1 = 2;

const int servoPin1 = 6;
const int servoPin2 = 7;
const int servoPin3 = 8;

const int dialPin1 = A0;

const int servoZeroPoint = 0;
const int servoMaxPoint = 1023;

unsigned long timeCounter = 0;

enum State {running, setHours, setMinutes, setSeconds};

State currentState = running;


// create print() function because old habits die hard

void print(char str[]){
    Serial.println(str);
}

//Functions

void printSerialTime(){

    // int hoursToAdd = (int)(timeCounter / 3600);
    // int minutesToAdd = ((int)(timeCounter / 60)) % 60;
    // int secondsToAdd = timeCounter % 60;
    //
    // Serial.println(hoursToAdd << minutesToAdd << secondsToAdd);

    Serial.println(timeCounter % 60);
    Serial.println(((int)(timeCounter / 60)) % 60);
    Serial.println((int)(timeCounter / 3600));
    Serial.println("\n");
}

int getDialPosition(){

    int sensorValue = analogRead(dialPin1);

    float res = (static_cast<float>(sensorValue) * (60.0/1024.0)) + 0.5;

    return static_cast<int>(res);
}

int getDialPositionInHours(){

    int sensorValue = analogRead(dialPin1);

    float res = (static_cast<float>(sensorValue) * (24.0/1024.0)) + 0.5;

    return static_cast<int>(res);
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


    return float((float)hours * 2.5);

}

// void debugPrint(int testTime){
//     std::cout << getSeconds(testTime);
//     std::cout << "\n";
//     std::cout << getMinutes(testTime);
//     std::cout << "\n";
//     std::cout << getHours(testTime);
// }




int setTime(){

    int hoursToAdd = (int)(timeCounter / 3600);
    int minutesToAdd = ((int)(timeCounter / 60)) % 60;
    int secondsToAdd = timeCounter % 60;

    int newTimeCounter = timeCounter;

    // Serial.println(settingValue);

    switch (currentState) {
        case setHours : {
            servo3.write((int)((float)getDialPositionInHours() * 7.5));

            newTimeCounter = getDialPositionInHours() * (60*60) + minutesToAdd * (60) + secondsToAdd * (1);
            break;
        }
        case setMinutes : {
            servo2.write(getDialPosition() * 3);

            newTimeCounter = hoursToAdd * (60*60) + getDialPosition() * (60) + secondsToAdd * (1);
            break;
        }
        case setSeconds : {
            servo1.write(getDialPosition() * 3);

            newTimeCounter = hoursToAdd * (60*60) + minutesToAdd * (60) + getDialPosition() * (1);
            break;
        }
        default : {
            break;
        }
    }

    return newTimeCounter;
}

bool getButton(){

    // TODO: Add code for recognizing a button press. make sure to only receive one input for one press, and do not accept another input until the button is released.

    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
        Serial.println("BUTTON HIGH");
        return true;
    } else {
        return false;
    }


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
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);

    Serial.begin(9600);
}


void loop() {

    // Serial.println(getDialPosition());
    // Serial.println(getDialPositionInHours());
    // delay(20);

    // Serial.println(currentState);
    // Serial.println(timeCounter);


    if (getButton()){



        // currentState = setHours;

        if(currentState == running){
            currentState = setHours;
        }else if(currentState == setHours){
            currentState = setMinutes;
        }else if(currentState == setMinutes){
            currentState = setSeconds;
        }else if(currentState == setSeconds){
            currentState = running;
        }


        Serial.println("newState:");
        Serial.println(currentState);

        // switch(currentState){
        //     case running : currentState = setHours;
        //     case setHours : currentState = setMinutes;
        //     case setMinutes : currentState = setSeconds;
        //     case setSeconds : currentState = running;
        // }
    }


    if (currentState == running) {
        // servo1.write(0);
        printSerialTime();
        doStep(timeCounter);
        delay(300);
        timeCounter += 1;
    } else {
        // print("in not running state");
        timeCounter = setTime();
    }

    delay(200);

}
