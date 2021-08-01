#include "config.h"
#include "pic18f4520.h"
#include "delay.h"
#include "lcd.h"
#include "teclado.h"
#include "time.h"
#include "stdlib.h"

//Variáveis globais
unsigned int atrasoMax = 1000;
int acertou = 0;
int errou = 0;
unsigned char tmp = 0;

//Função para limpar as linhas do LCD
void apagaTela() {
    unsigned char i;

    lcd_cmd(L_L1);
    for (i = 0; i < 16; i++) {
        lcd_dat(i % 2);
    }
    lcd_cmd(L_L2);
    for (i = 0; i < 16; i++) {
        lcd_dat(i % 2);
    }
    lcd_cmd(L_L3);
    for (i = 0; i < 16; i++) {
        lcd_dat(i % 2);
    }
    lcd_cmd(L_L4);
    for (i = 0; i < 16; i++) {
        lcd_dat(i % 2);
    }
    atraso_ms(atrasoMax);
}

//Função auxiliar para o LCD
void telaLevel(int level) {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("////////////////");
    lcd_cmd(L_L2);
    lcd_str("     LEVEL      ");
    lcd_cmd(L_L3 + 7);
    lcd_dat(level + 0x30);
    lcd_cmd(L_L4);
    lcd_str("////////////////");
    atraso_ms(4 * atrasoMax);
    apagaTela();
    BitClr(PORTC,2);

}

//Função auxiliar para o LCD
void telaAcertos() {
    BitSet(PORTC,2);
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Acertos: ");
    lcd_cmd(L_L2);
    lcd_dat(acertou + 0x30);
    lcd_cmd(L_L3);
    lcd_str("Erros: ");
    lcd_cmd(L_L4);
    lcd_dat(errou + 0x30);
    atraso_ms(8 * atrasoMax);
}

//Função auxiliar para o LCD
void gameOver() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("****************");
    lcd_cmd(L_L2);
    lcd_str("   Game Over    ");
    lcd_cmd(L_L3);
    lcd_str("   Game Over    ");
    lcd_cmd(L_L4);
    lcd_str("****************");
    atraso_ms(12 * atrasoMax);
    apagaTela();
    BitClr(PORTC,2);
}

//Função auxiliar para o LCD
void youWin() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("!!!!!!!!!!!!!!!!");
    lcd_cmd(L_L2);
    lcd_str("!!!!YOU WIN!!!!!");
    lcd_cmd(L_L3);
    lcd_str("!!!!YOU WIN!!!!!");
    lcd_cmd(L_L4);
    lcd_str("!!!!!!!!!!!!!!!!");
    atraso_ms(12 * atrasoMax);
    apagaTela();
    BitClr(PORTC,2);
}

//Função que cria a toupeira e verifica se acertou ou não
void Toupeira(int j) {
    int aux = (rand() % 3 + 2); //Variável auxiliar para gerar números randômicos
    unsigned char posicao = aux + 0x2F;
    
    PORTD = 0x7F;
    BitSet(PORTA, aux); //Liga o display para aparecer a Toupeira na posição determinada por aux
    TRISC=0x01;

    
    TRISD = 0x0F;
    tmp = tc_tecla(15000/j) + 0x30; //A variável tmp recebe o valor da tecla pressionada num dado intervalo
    TRISD = 0x00;
    

    if (tmp == posicao) {//Se a tecla pressionada for a que estiver a toupeira surgirá a mensagem de acerto
        PORTD = 0x76;
        BitSet(PORTA, aux);
        atraso_ms(atrasoMax);
        BitClr(PORTA, aux);
        lcd_cmd(L_L1);
        lcd_str("ACERTOUUUU");
        atraso_ms(3 * atrasoMax);
        acertou++;
    } else { // Caso contrário será exibida a mensagem de erro
        PORTD = 0x3F;
        BitSet(PORTA, aux);
        atraso_ms(atrasoMax);
        BitClr(PORTA, aux);
        lcd_cmd(L_L4);
        lcd_str("ERROUUUUUU");
        atraso_ms(3 * atrasoMax);
        errou++;
    }
    apagaTela();
}

void main() {
    unsigned char i, j;
    srand(time(NULL));
    
    //Inicialização dos PORTs
    ADCON1 = 0x06;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    PORTD = 0x00;

    lcd_init();

    //Tela Inicial
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("****************");
    lcd_cmd(L_L2);
    lcd_str(">*Whack A Mole*<");
    lcd_cmd(L_L3);
    lcd_str(">*Whack A Mole*<");
    lcd_cmd(L_L4);
    lcd_str("****************");
    atraso_ms(8 * atrasoMax);
    TRISD = 0x0F;
    tmp = tc_tecla(0) + 0x30; //A variável tmp recebe o valor da tecla pressionada num dado intervalo
    TRISD = 0x00;
    
    apagaTela();

    for (j = 1; j < 6; j++) {    //O jogo rodará cinco fases 
        acertou = 0;
        errou = 0;
        telaLevel(j);
        
        for (i = 0; i < 4 + j; i++) { //O número de toupeiras por fase inicia em 5 e vai até 9
            Toupeira(j);
        }
        telaAcertos();
        if (acertou <= errou){//Se o jogador teve mais erros que acertos numa fase GAME OVER
            gameOver();
            atraso_ms(4 * atrasoMax);
            return;
        }
        atraso_ms(4 * atrasoMax);
    }
    youWin();//Se o jogador completar todas fases YOU WIN
}

