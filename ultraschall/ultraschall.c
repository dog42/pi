// install wiringPI first and add "-l wiringPi" to compileinstuction

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <inttypes.h> 
 
#define TRIG 1
#define ECHO 0
uint32_t dead=0;
#define maxdead 5000
//#define LED  6
 
void setup() {
        wiringPiSetup();
        pinMode(TRIG, OUTPUT);
//        pinMode(LED, OUTPUT);
        pinMode(ECHO, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
int getCM() {
        //Send trig pulse
        //delayMicroseconds(100);
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        dead=0;
        while(digitalRead(ECHO) == LOW){dead++;if(dead>=maxdead)break;};
 
        //Wait for echo end
        long startTime = micros();
        dead=0;
        while(digitalRead(ECHO) == HIGH){dead++;if(dead>=maxdead)break;};
        long travelTime = micros() - startTime;

        //Get distance in cm
        //distance = (travelTime / 2 * 1000000[s]) * (331,5 * 100[cm]) 
        //distance = (travelTime * 331,5) / 20000 
        //--> 331.5/20000 =~ 1/58

        int distance = travelTime / 58;

        return distance;
}
int main(void) {
        setup();
        int dist;
        printf("waiting\n");
        while(TRUE){
                printf("Distance: %dcm\n", dist=getCM());
                //digitalWrite(LED, (dist<=10 ? HIGH:LOW));
//              delay(500);
        }
        return 0;
}


