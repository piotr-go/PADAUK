/*
  LG TV remote (AKB73715686)

  Copyright (C) 2022 Piotr Gozdur <piotr_go>.

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
__sfr __at(0x0b) ihrcr;
__sfr __at(0x0d) padier;
__sfr __at(0x0e) pbdier;
__sfr __at(0x10) pa;
__sfr __at(0x11) pac;
__sfr __at(0x12) paph;

unsigned char _sdcc_external_startup(void){
	clkmd = 0x78;	// IHRC/32
	ihrcr = 0x85;	// ~494kHz
	return 0;
}

void irS(void){
__asm
	mov	a, #0x98
10$:
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	10$
	mov	a, #0x98
11$:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	11$
__endasm;
}

void ir0(void){
__asm
	mov	a, #0x13
20$:
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	20$
	mov	a, #0x13
21$:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	21$
__endasm;
}

void ir1(void){
__asm
	mov	a, #0x13
30$:
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	30$
	mov	a, #0x39
31$:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	31$
__endasm;
}

void ir_tx(unsigned char c0, unsigned char c1){
	unsigned char i, tmp;
	irS();
	tmp = c0;
	for(i=0;i<8;i++){
		if(tmp&1) ir1();
		else ir0();
		tmp>>=1;
	}
	tmp = ~c0;
	for(i=0;i<8;i++){
		if(tmp&1) ir1();
		else ir0();
		tmp>>=1;
	}
	tmp = c1;
	for(i=0;i<8;i++){
		if(tmp&1) ir1();
		else ir0();
		tmp>>=1;
	}
	tmp = ~c1;
	for(i=0;i<8;i++){
		if(tmp&1) ir1();
		else ir0();
		tmp>>=1;
	}
	ir0();
}

void irR(void){
__asm
	mov	a, #0x98
40$:
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	40$
	mov	a, #0x4C
41$:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	41$
	mov	a, #0x13
42$:
	set0.io	_pa,#5
	nop
	nop
	nop
	set1.io	_pa,#5
	nop
	nop
	nop
	nop
	nop
	dzsn	a
	goto	42$
__endasm;
}

void _delay(unsigned short cnt){
	while(cnt--) __asm__("nop\n");
}

void main(void){
	pa  = (1<<5);					// Enable PA __5_____ high
	pac = (1<<5);					// Enable PA __5_____ output
	paph = 0xFF;					// Enable PA ALL      pull-high
	padier = (1<<7)|(1<<6)|(1<<4)|(1<<3)|(1<<0);	// Enable PA 76_43__0 wake up event
	pbdier = 0;

	while(1){
		__asm__("stopsys");

		if((pa&(1<<0)) == 0){	// press PWR
			ir_tx(0x04, 0x08);
			_delay(4000);
			while((pa&(1<<0)) == 0){
				irR();
				_delay(4000);
			}
		}

		if((pa&(1<<3)) == 0){	// press CH+
			ir_tx(0x04, 0x00);
			_delay(4000);
			while((pa&(1<<3)) == 0){
				irR();
				_delay(4000);
			}
		}

		if((pa&(1<<4)) == 0){	// press CH-
			ir_tx(0x04, 0x01);
			_delay(4000);
			while((pa&(1<<4)) == 0){
				irR();
				_delay(4000);
			}
		}

		if((pa&(1<<6)) == 0){	// press V+
			ir_tx(0x04, 0x02);
			_delay(4000);
			while((pa&(1<<6)) == 0){
				irR();
				_delay(4000);
			}
		}

		if((pa&(1<<7)) == 0){	// press V-
			ir_tx(0x04, 0x03);
			_delay(4000);
			while((pa&(1<<7)) == 0){
				irR();
				_delay(4000);
			}
		}
	}
}
