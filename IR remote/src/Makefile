# Makefile for SDCC with PDK14 target assembler project

SDCC=sdcc
SDLD=sdld
SDAS=sdaspdk
OBJCOPY=sdobjcopy
TARGET=main.hex
ASFLAGS=-lo
LDFLAGS=-mpdk14 -lpdk14 --out-fmt-ihx
CFLAGS = 

SRCS    := $(wildcard *.c $(LIBDIR)/*.c)
ASRCS   := $(wildcard *.s $(LIBDIR)/*.s)

OBJS     = $(SRCS:.c=.rel)
OBJS 	+= $(ASRCS:.s=.rel)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(SDCC) $(LDFLAGS) $(OBJS) -o $@

%.rel: %.s
	$(SDAS) $(ASFLAGS) $<

%.rel: %.c
	$(SDCC) -mpdk14 $(CFLAGS) $(INCLUDE) -c $< -o $@

size:
	$(OBJCOPY) -I ihex -O binary $(TARGET) $(TARGET).bin
	@echo "Image size:"
	@stat -L -c %s $(TARGET).bin

clean:
	rm -f $(OBJECTS) *.map *.asm *.rel *.ihx *.o *.sym *.lk *.lst *.rst *.cdb *.bin *.mem

.PHONY: all clean flash
