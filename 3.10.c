__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
#define STK_CTRL ((volatile unsigned int *)(0xE000E010))  
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))  
#define STK_VAL ((volatile unsigned int *)(0xE000E018))  
}

__attribute__((naked))
void graphic_initialize(void){
	__asm volatile(".HWORD 0XDFF0\n");
	__asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_set(int x, int y){
	__asm volatile(".HWORD 0XDFF2\n");
	__asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y){
	__asm volatile(".HWORD 0XDFF3\n");
	__asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_clear_screen(void){
	__asm volatile(".HWORD 0XDFF1\n");
	__asm volatile(" BX LR\n");
}

void main(void){
	int i;
	graphic_initialize();
	graphic_clear_screen();
	for(i=1; i<= 128; i++)
		graphic_pixel_set(i,10);
	for(i=1; i<= 64; i++)
		graphic_pixel_set(10,i);
	delay_milli(500);
	for(i=1; i<= 128; i++)
		graphic_pixel_clear(i,10);
	for(i=1; i<= 64; i++)
		graphic_pixel_clear(10,i);
	}


void delay_250ns( void ){
	*STK_CTRL = 0;
	*STK_LOAD = ( (168/4) -1 );
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while( (*STK_CTRL & 0x10000 )== 0 );
	*STK_CTRL = 0;
}

void delay_milli(unsigned int ms)
{
	while(ms>0){
		int i = 50;
		while(i>0){
			delay_250ns();
			i = i-1;
		
		}
	ms--;
	}
}
