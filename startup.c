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

void
plot_line (int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    graphic_pixel_set (x0,y0);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

typedef struct POINT
{
	char x;
	char y;
}*PPOINT;

typedef struct
{
	char x0,y0,x1,y1;
	
	struct POINT p0;
	p0.x=x0;
	p0.y=y0;
	struct POINT p1;
	p1.x=x1;
	p1.y=y1;
	

}LINE, *PLINE;

void main(void){
	int i;

	graphic_initialize();
	graphic_clear_screen();
	LINE linje = {20,10,60,10};
	
	plot_line(linje.x0,linje.y0,linje.x1,linje.y1);
	//for(i=1; i<= 128; i++)
	//	graphic_pixel_set(i,10);
	//for(i=1; i<= 64; i++)
	//	graphic_pixel_set(10,i);
	//delay_milli(500);
	//for(i=1; i<= 128; i++)
	//	graphic_pixel_clear(i,10);
	//for(i=1; i<= 64; i++)
	//	graphic_pixel_clear(10,i);
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

