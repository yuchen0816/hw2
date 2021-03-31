#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(D7);
AnalogIn ain(A3);
uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn up(A0);
DigitalIn down(A1);
DigitalIn confirm(A2);
float i;
int j;
int l;
int freq = 720;
int x;
int y;
float T = 1000/freq;
float ADCdata[128];
int conf = 0;
int main(void)
{
    uLCD.text_width(4);
    uLCD.text_height(4);
    uLCD.locate(1,2);
    uLCD.printf("%d\n", freq);
    
    while(1){
        if(up==1){
            if(freq < 970)
                freq = freq + 50;
            else
                freq = freq; 
            uLCD.text_width(4);
            uLCD.text_height(4);
            uLCD.locate(1,2);
            uLCD.printf("%d\n", freq);
        }
        if(down==1){
            if(freq > 120)
                freq = freq - 50;
            else
                freq = freq;
            uLCD.text_width(4);
            uLCD.text_height(4);
            uLCD.locate(1,2);
            uLCD.printf("%d\n", freq);
        }
        if(confirm==1){
            conf = 1;
            T = 1000 / freq;
            uLCD.text_width(4);
            uLCD.text_height(4);
            uLCD.locate(1,2);
            uLCD.printf("%d\n", freq);
        }
        if(freq == 720){
            x = 105;
            y = 70;
        }
        
        for (i = 0; i < 0.9; i +=  T / x) {
            aout = i;
        }
        for (i = 0.9; i > 0; i -=  T / y) {
            aout = i;
        }
        
        if(conf==1){
            for(j = 0; j < 128; j++){
                ADCdata[j] = ain;
                ThisThread::sleep_for(1000ms/128);
            }
            if(j == 127){
                printf("%d\r\n", freq);
                for(l=0; l<128; l++){
                    printf("%f\r\n", ADCdata[l]);
                    ThisThread::sleep_for(100ms);
                }
                j = 0;
            }
            conf = 0;
        }
    }
}