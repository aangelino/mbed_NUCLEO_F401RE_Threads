#include "mbed.h"

#define DEBUG_PRINT_PULSES 0
#define US 0

DigitalOut led1(LED1);
DigitalOut test_out(D7);
DigitalIn start_in(D8,PullDown);
PwmOut pwm_out_9(D9);
Timer timer;

Serial pc(SERIAL_TX, SERIAL_RX);
int pulses_number;

void callback_func1()
{
  int i;
  for (i=0;i<10;i++)
  {
    pc.printf("\n\r func1");
    
  }
}



void callback_func2()
{
  int i;
  for (i=0;i<10;i++)
  {
    pc.printf("\n\r func2");

  }
}

// main() runs in its own thread in the OS
int main()
{
  //GPIOA->AFR[0] &= 0xfffffff0;
    //test_out.write(0);
    /*Pwm Settings*/
    //pwm_out_9.period_ms(10);
    //pwm_out_9.write(0);

    /*start directly thread, callback needs to contain argument f(void const *args) */
    //Thread thread_10Hz(callback_thread_10Hz);

    Thread thread1;
    Thread thread2;

    /*Info system clock*/
    pc.printf("\n\rSystemCoreClock=%d\r\n",SystemCoreClock);


    pc.printf("\n\r Choose Frequency/Period \n");


    while(1)
    {

      pc.printf("\n\r a. thread1    ");
      pc.printf("\n\r b. thread2 ");

      switch(pc.getc())
      {

        case 'a': pc.printf("\n\r --> sending thread1  callback_func1" );
                  thread1.start(callback_func1);
                  wait(1);
                  thread1.join();
                  break;
        case 'b': pc.printf("\n\r --> sending thread2 ");
                  thread2.start(callback_func2);
                  wait(5);
                  pc.printf("\n\r --> terminate thread2 ");
                  thread1.terminate();
                  break;

        default : pc.printf("\n\r Wrong choose");
                  break;
      }

    }

    return 0;
}
