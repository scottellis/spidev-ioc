CC = gcc
CFLAGS = -O2 -Wall

TARGET=spidev-ioc

$(TARGET): spidev-ioc.c
	$(CC) $(CFLAGS) spidev-ioc.c -o $(TARGET)

clean:
	rm -rf $(TARGET) 
 
