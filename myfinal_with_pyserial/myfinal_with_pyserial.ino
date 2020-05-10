#include<avr/io.h>
#include<math.h>
#include<util/delay.h>
void Wait()
{
  uint8_t i;
  for(i=0;i<120;i++)
  {
    _delay_loop_2(0);
    _delay_loop_2(0);
    _delay_loop_2(0);
  }
}
int main()
{
  Serial.begin(9600);
  float integer1 = 0, integer2=0;
  
  char incoming[1];
  char cyc,cxc;
  if(Serial.available()>=2)
  {
    for( int i=0;i<2;i++)
    incoming[i]=Serial.read();
    integer1 = 0;
    integer2=0;
    while(1)
    {
      cyc=incoming[0];
      if(cyc== '\n')
      break;
      if(cyc== -1)
      continue;
      integer1 *=10;
      integer1 = ((cyc-48) + integer1);
    }
    while(1)
    {
      cxc=incoming[1];
      if(cxc== '\n')
      break;
      if(cxc== -1)
      continue;
      integer2 *=10;
      integer2 = ((cxc-48) + integer2);
    }
  }
  float cx=integer1;
  float cy=integer1;
  Serial.print(cx);
 
  float x,y,X,Y;
  float m,n,o,p,q,l,z,a;
  x=cx * 0.052;
  y=cy * 0.061;
  X=x+6;
  Y=y;
  

  p=sqrt(X*X+ Y*Y);
  m=atan(Y/X)*57.3;
  q=sqrt(p*p + 100);
  n=acos(q/36)*57.3;
  a=(acos(q/36) - atan(10/p))*57.3;
  o=(2*n);
  z=180-o;
  TCCR0A |= (1<<COM0A1) |(1<<WGM01) | (1<< WGM00);
  TCCR0B |=   (1<< CS02) ;
  DDRD= 0xFF;
  DDRC= 0xFF;
   //Configure TIMER1
   TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

   ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).

   DDRB|=0xFF;   //PWM Pins as Out
   

   while(1)
   {
       
  
      OCR1B=(180+(2.28*m))+15;//BASE
      OCR1A=(180+(2.28*a))-8; //0 degree
      OCR0A=(50+(0.56*z));
      
      PORTC=0b00000001;
      Wait();
      while(1)
      {
        OCR1B=170;//BASE
        OCR1A=260; //0 degree
        OCR0A=90;
        PORTC=0b00000001;
        
        Wait();
        PORTC=0b00000000;
        PORTC=0b00000000;
        
        while(1)
        {
            OCR1B=180;//BASE
            OCR1A=370; //0 degree
            OCR0A=180;
          
        }
      }
      
   }
}

