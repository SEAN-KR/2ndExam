/* 스위치에 따라 LED ON/OFF */

#include <io.h>
#include <delay.h>
#include <stdio.h>
#include <interrupt.h>

#define DELAY 150
int sel = 1;

interrupt [EXT_INT4] void ext_int4_isr(void)
{
    sel = 1;
}

interrupt [EXT_INT5] void ext_int5_isr(void)
{
    sel = 2;
}

void init(){
    DDRA = 0xff;
    DDRE = 0x00;  
    EICRB = (1<<ISC41)|(1<<ISC51); 
    EIMSK = (1<<INT4)|(1<<INT5);  
    sei();
}
    
void main(void)
{
    int led=0x01,dir=0;
    
    init();    
    while (1)
    {  	        
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
        }        
         if(sel == 2){
            PORTA = 0xAA;            
            delay_ms(DELAY);
            PORTA = 0x55;
            delay_ms(DELAY);
         }    
    }
}