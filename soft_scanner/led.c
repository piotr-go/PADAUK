/*
  Copyright (C) 2019 Piotr Gozdur <piotr_go>.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/


__sfr __at(0x03) clkmd;
__sfr __at(0x0d) padier;
__sfr __at(0x10) pa;
__sfr __at(0x11) pac;
__sfr __at(0x12) paph;

unsigned char _sdcc_external_startup(void){
	clkmd = 0xF4;	// ILRC
	clkmd = 0xE4;
	return 0;	// perform normal initialization
}

//const unsigned short tablica[20] = {0x0818, 0x1018, 0x1011, 0x0111, 0x0181, 0x8081, 0x80C0, 0x40C0, 0x4048, 0x0848, 0x0809, 0x0109, 0x1090, 0x8090, 0x0141, 0x4041, 0x0888, 0x8088, 0x1050, 0x4050};
const unsigned char tablica1[20] = {0x18, 0x18, 0x11, 0x11, 0x81, 0x81, 0xC0, 0xC0, 0x48, 0x48, 0x09, 0x09, 0x90, 0x90, 0x41, 0x41, 0x88, 0x88, 0x50, 0x50};
const unsigned char tablica2[20] = {0x08, 0x10, 0x10, 0x01, 0x01, 0x80, 0x80, 0x40, 0x40, 0x08, 0x08, 0x01, 0x10, 0x80, 0x01, 0x40, 0x08, 0x80, 0x10, 0x40};

void main(void){
	unsigned char i;
	volatile unsigned char j;

	paph = 0x00;		// disable pull-high
	pac = 0x00;		// output
	pa = 0x00;

	i = 0;

	while(1){
		while(1){
			pa = 0;
			pac = tablica1[i];
			pa = tablica2[i];

			for(j=0; j<50; j++){}

			if(i==19){
				i--;
				break;
			}
			else i++;
		}

		while(1){
			pa = 0;
			pac = tablica1[i];
			pa = tablica2[i];

			for(j=0; j<50; j++){}

			if(i==0){
				i++;
				break;
			}
			else i--;
		}
	}
}
