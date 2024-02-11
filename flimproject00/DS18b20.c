#include"at89x52.h"
__sbit __at (0xB7) PORT_data;
//#define PORT_data P3_7
unsigned char PORT_init(void)
{		
	unsigned char inire;
	unsigned char i;
	PORT_data=1;
	PORT_data=0;
	i = 247;while(--i);
	PORT_data=1;
	i = 32;while(--i);
	inire = PORT_data;
	i = 247;while(--i);

	return inire;
}
void PORT_Sendbit(unsigned char bit)
{
	unsigned char i;
	PORT_data=0;
	i=4;while(--i);
	PORT_data=bit;
	i=24;while(--i);
	PORT_data=1;
}
unsigned char PORT_receivebit(void)
{
	unsigned char i;
	unsigned char bit;
	PORT_data=0;
	i=2;while(--i);
	PORT_data=1;
	i=2;while(--i);
	bit=PORT_data;
	i=24;while(--i);
	return bit;
}
void PORT_sendbyte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		PORT_Sendbit(byte&(0x01<<i));
	}
}
unsigned char PORT_receivebyte(void)
{
	unsigned char i;
	unsigned char byte = 0x00;
	byte = 0x00;
	for (i=0;i<8;i++)
	{
		if(PORT_receivebit())
		{
			byte|=(0x01<<i);
		}
	}
	return byte;
}
void DS18b20_convert_T(void)
{
	PORT_init();
	PORT_sendbyte(0xCC);
	PORT_sendbyte(0x44);
}
float DS18b20_read_T(void)
{
	unsigned char TLSB,TMSB;
	int temp;
	float T;
	PORT_init();
	PORT_sendbyte(0xCC);
	PORT_sendbyte(0xBE);
	TLSB=PORT_receivebyte();
	TMSB=PORT_receivebyte();
	temp=(TMSB<<8)|TLSB;
	T=temp/16.0;
	return T;
	
}
