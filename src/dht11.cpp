#include <dht11.h>
#include <wiringPi.h>
#include <stdint.h>

#define MAXTIMINGS 85;

Dht11::Dht11(int pin_num){
  pin = pin_num;
}

float* Dht11::getTempAndHumidity(){
  int dht11_dat[5] = { 0, 0, 0, 0, 0};
  uint8_t laststate	= HIGH;
  uint8_t counter		= 0;
  uint8_t j		= 0, i;
  float	f; /* fahrenheit */

  pinMode( pin, OUTPUT );
  digitalWrite( pin, LOW);
  delay( 18 );

  digitalWrite( pin, HIGH );
  delayMicroseconds( 40 );

  pinMode( pin, INPUT );

  for ( i = 0; i < MAXTIMINGS; i++ )
  {
    counter = 0;
    while ( digitalRead( pin ) == laststate )
    {
    counter++;
    delayMicroseconds( 1 );
    if ( counter == 255 )
    {
      break;
    }
  }
  laststate = digitalRead( pin );

  if ( counter == 255 )
  break;

  /* ignore first 3 transitions */
  if ( (i >= 4) && (i % 2 == 0) )
  {
    /* shove each bit into the storage bytes */
    dht11_dat[j / 8] <<= 1;
    if ( counter > 16 )
      dht11_dat[j / 8] |= 1;
      j++;
    }
  }

  /*
   * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
   * print it out if data is good
   */
  int checksum = (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]);
  if ( (j >= 40) && (dht11_dat[4] == ( checksum & 0xFF) ) )
  {
    float c = dht11_dat[2] + (dht11_dat[3]/100);
    float h = dht11_dat[0] + (dht11_dat[1]/100);
    f = c * 9. / 5. + 32;
	float ret[2] = { c, h };
    return ret;
  }
}
