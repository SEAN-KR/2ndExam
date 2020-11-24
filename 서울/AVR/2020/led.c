/* 스위치에 따라 LED ON/OFF */

#include <io.h>
#include <delay.h>
#include <stdio.h>

#define DELAY 150

void main(void)
{
    int i=0;
    int sel=0,led=0x01,dir=0;
    DDRA = 0xff;
    DDRE = 0x00;
    while (1)
    {  	
        if ((PINE & 0x10) == 0x00){ 	// SW1 = PE bit4
            PORTA = 0xff;		// LED = ‘ON’
            sel = 1;
        }
        else
            PORTA = 0x00;		// LED = ‘OFF’
                  
        if ((PINE & 0x20) == 0x00){ 	// SW1 = PE bit4
            PORTA = 0xff;		// LED = ‘ON’
            sel = 2;
        }
        else
            PORTA = 0x00;		// LED = ‘OFF’
                   
        if(sel == 1){
            if(dir == 0){
                PORTA = led; 
                led = (led << 1);
                delay_ms(DELAY);   
                if(PORTA == 0x80){
                    dir = 1;   
                    led = 0x80;   
                }
            }else if (dir == 1){
                PORTA = led; 
                led = (led >> 1);
                delay_ms(DELAY);
                if(PORTA == 0x01){
                    dir = 0;      
                    led = 0x01;
                }
            }            
            
        /*
            if(dir == 0){    
                PORTA = (led << 1);
                delay_ms(200);
                if(PORTA == 0x80)
                    dir = 1;
            }
            if(dir == 1){
                PORTA = (led >> 1);
                delay_ms(200);
                if(PORTA == 0x01)
                    dir = 0;
            }
        */
        }        
         if(sel == 2){
            PORTA = 0xAA;            
            delay_ms(DELAY);
            PORTA = 0x55;
            delay_ms(DELAY);
         }    
    }
}