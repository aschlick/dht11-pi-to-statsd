#include <dht11.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main( void )
{
  const int pin = 7;
  Dht11 sensor = Dht11( pin );
  printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );

  if ( wiringPiSetup() == -1 )
    exit( 1 );

  while ( 1 )
  {
    float *data = sensor.getTempAndHumidity();
    printf("Temperature: %f", data[0]);
    printf("Humidity: %f", data[1]);
    delay( 1000 ); /* wait 1sec to refresh */
  }

  return(0);
}
