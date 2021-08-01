#include "config.h"
#include "pic18f4520.h"
#include "delay.h"
#include "lcd.h"

unsigned int atrasoMin = 20;
unsigned int atrasoMed = 150;
unsigned int atrasoMax = 1000;

void main() {
    unsigned char i;

    ADCON1 = 0x06;
    TRISD = 0x00;
    TRISE = 0x00;

    lcd_init();

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("  Exemplo #01");
    lcd_cmd(L_L2);
    lcd_str(" Desloc. texto");
    atraso_ms(atrasoMax);

    for (i = 0; i < 10; i++) {
        atraso_ms(atrasoMed);
        lcd_cmd(0x18);
    }

    for (i = 0; i < 20; i++) {
        atraso_ms(atrasoMed);
        lcd_cmd(0x1C);
    }

    for (i = 0; i < 10; i++) {
        atraso_ms(atrasoMed);
        lcd_cmd(0x18); //display shift left
    }
    atraso_ms(atrasoMax);

    //=======================    

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("  Exemplo #02");
    lcd_cmd(L_L2);
    lcd_str("Apagar 1a linha");
    atraso_ms(atrasoMax);

    lcd_cmd(L_L1);

    for (i = 0; i < 16; i++) {
        lcd_dat(i % 2);
        atraso_ms(atrasoMed);
    }
    atraso_ms(atrasoMax);
    
    //=======================    

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("  Exemplo #03");
    lcd_cmd(L_L2);
    lcd_str("Apagar 2a linha");
    atraso_ms(atrasoMax);

    lcd_cmd(L_L2);

    for (i = 0; i < 16; i++) {
        lcd_dat(i % 2);
        atraso_ms(atrasoMed);
    }
    atraso_ms(atrasoMax);

    //=======================
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("  Exemplo #04");
    lcd_cmd(L_L2);
    lcd_str(" Desloc. cursor");
    atraso_ms(atrasoMax);

    for (i = 0; i < 15; i++) {
        atraso_ms(atrasoMed);
        lcd_cmd(0x10);
    }
    for (i = 0; i < 15; i++) {
        atraso_ms(atrasoMed);
        lcd_cmd(0x14);
    }

    //=======================

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("  Exemplo #06");
    atraso_ms(atrasoMax);

    for (i = 32; i >= 32; i++) {
        if ((i % 16) == 0) {
            lcd_cmd(L_L2);
        }
        lcd_dat(i);
        atraso_ms(atrasoMed);
    }

    atraso_ms(atrasoMax);

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("      Fim");
    while (1) {
        for (i = 0; i < 4; i++) {
            atraso_ms(atrasoMed);
            lcd_cmd(0x10);
        }
        for (i = 0; i < 4; i++) {
            atraso_ms(atrasoMed);
            lcd_cmd(0x14);
        }
    };
}