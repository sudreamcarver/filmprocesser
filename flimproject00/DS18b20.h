#ifndef __DS18B20_H__
#define __DS18B20_H__

unsigned char PORT_init(void);
unsigned char PORT_receivebit(void);
void PORT_Sendbit(unsigned char bit);
void PORT_sendbyte(unsigned char byte);
unsigned char PORT_receivebyte(void);
float DS18b20_read_T(void);
void DS18b20_convert_T(void);

#endif
