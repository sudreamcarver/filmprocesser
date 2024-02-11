CC = sdcc
CFLAGS = -c
OBJS = main.rel LCD1602.rel DS18b20.rel pwm.rel motor.rel keyfun.rel minsconts.rel

all: main.ihx
	@echo "Build complete------"

main.ihx: $(OBJS)
	$(CC) $(OBJS)
	@echo "Linked: $@------"

%.rel: %.c
	$(CC) $(CFLAGS) $<
	@echo "Compiled: $<------"

clean:
	rm -f $(OBJS) main.ihx
	rm -f *.lst
	de
	@echo "Clean complete------"

cleaneed:
	rm -f *.rst
	rm -f *.sym
	rm -f *.mem
	rm -f *.asm
	rm -f *.map
	rm -f *.lk
	@echo "No need files cleaned------"
.PHONY: all clean cleaneed

