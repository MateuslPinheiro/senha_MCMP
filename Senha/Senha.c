#include <p18f4520.h>
#define RS LATCbits.LATC0
#define EN LATCbits.LATC1
#define LED LATCbits.LATC2

char c1,c2,c3,c4;


void delay_ms (void)
{
	unsigned int i;
	for (i=0;i<90;i++) {}
}
void delay_ini (void)
{
	unsigned int i;
	for (i=0;i<2000;i++) {}
}
void delay_teclado ()
{
	int i;
	for(i=0;i<30000;i++){}
}

//FUNÇÃO DRIVER
void envia_comando(unsigned char comando)
{
	RS=0;
	EN=0;
	LATD = comando;
	EN=1;
	EN=0;	//habilita LCD
	delay_ms();		// tempo pro LCD executar o comando
}

//FUNÇÃO DRIVER
void envia_dado(unsigned char dado)
{
	RS=1;	
	EN=0;
	LATD = dado;
	EN=1;
	EN=0;
	delay_ms();
}

void inicializa_lcd(void)
{
	delay_ini();
	envia_comando(0b00111000); // 2 linhas caractere 5x8
	envia_comando(0b00001100); // curson off(sétimo bit);
	envia_comando(0b00000001); 
}


unsigned char Varredura_Teclado()
{
	LATBbits.LATB0 = 1;
	LATBbits.LATB1 = 0;
	LATBbits.LATB2 = 0;
	if(PORTBbits.RB0 == 1)				//COLUNA 1
	{
		if(PORTAbits.RA0 == 1)
		{	
			return 0b00110001;        //NÚMERO 1
		}	
		if(PORTAbits.RA1 == 1)
		{
			return 0b00110100 ;        //NÚMERO 4
		}
		if(PORTAbits.RA2 == 1)
		{
			return 0b00110111;        //NÚMERO 7
		}
		if(PORTAbits.RA3 == 1)
		{
			return 0b00101010;        //SÍMBOLO *
		}
	}
	LATBbits.LATB0 = 0;
	LATBbits.LATB1 = 1;
	LATBbits.LATB2 = 0;
	if(PORTBbits.RB1 == 1)				//COLUNA 2
	{
		if(PORTAbits.RA0 == 1)
		{	
			return 0b00110010;        //NÚMERO 2
		}	
		if(PORTAbits.RA1 == 1)
		{
			return 0b00110101;        //NÚMERO 5
		}
		if(PORTAbits.RA2 == 1)
		{
			return 0b00111000;        //NÚMERO 8
		}
		if(PORTAbits.RA3 == 1)
		{
			return 0b00110000;        //NÚMERO 0
		}
	}
	LATBbits.LATB0 = 0;
	LATBbits.LATB1 = 0;
	LATBbits.LATB2 = 1;
	if(PORTBbits.RB2 == 1)				//COLUNA 3
	{
		if(PORTAbits.RA0 == 1)
		{	
			return 0b00110011;        //NÚMERO 3
		}	
		if(PORTAbits.RA1 == 1)
		{
			return 0b00110110;        //NÚMERO 6
		}
		if(PORTAbits.RA2 == 1)
		{
			return 0b00111001;        //NÚMERO 9
		}
		if(PORTAbits.RA3 == 1)
		{
			return 0b00100011;        //SÍMBOLO #
		}
	}	
	return 12;
}
void organiza_lcd()
{
	c1=12; c2=12; c3=12; c4=12;
	delay_teclado();
	while (c1==12)
	{
		c1=Varredura_Teclado();
	}
	envia_dado(c1);
	delay_teclado();
	while (c2==12)
	{
		c2=Varredura_Teclado();
	}
	envia_dado(c2);
	delay_teclado();
	while (c3==12)
	{
		c3=Varredura_Teclado();
	}
	envia_dado(c3);
	delay_teclado();
	while (c4==12)
	{
		c4=Varredura_Teclado();
	}
	envia_dado(c4);
	delay_teclado();
	if (c1==0b00110001 && c2==0b00110010 && c3==0b00110011 && c4==0b00110100)
	{
		LED=1;
	}
}



main ()
{
	//área de configuração do sistema
	//Portas do LCD

	TRISD=0b00000000;
	TRISCbits.RC0 = 0;
	TRISCbits.RC1 = 0;
	TRISCbits.RC2 = 0;

//----------------------------------
	//Portas do Teclado

	ADCON1 = 0b00001111;	//LIBERA PORTAS PARA IO
	TRISBbits.RB0 = 0;     
	TRISBbits.RB1 = 0;
	TRISBbits.RB2 = 0;
	TRISAbits.RA0 = 1;
	TRISAbits.RA1 = 1;
	TRISAbits.RA2 = 1;
	TRISAbits.RA3 = 1;

//----------------------------------

	inicializa_lcd(); //"Burocracia" para inicializar o LCD
	LED=0; //LED Desligado.


	// programa monitor
	while (1)
	{
	organiza_lcd();


	}
}
