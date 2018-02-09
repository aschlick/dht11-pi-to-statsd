#include <dht11.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  const int pin = 15; //TxD is 15 in wpi
  float data[2];

  if ( wiringPiSetup() == -1 )
    exit( 1 );

  while ( 1 ){
    if(GetTempAndHumidity(data, pin) == 0){
      printf("Temperature: %f\n", data[0]);
      printf("Humidity: %f\n", data[1]);
    }
    delay( 1000 ); /* wait 1sec to refresh */
  }

  return 0;
}
