/*
 * spidev ioctl test
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define DEFAULT_DEVICE "/dev/spidev1.0"

void usage()
{
    printf("\nUsage: spidev-ioc [-d <device>] [-h]\n");
    printf("  -d <device>     Device, defaults to /dev/spidev1.0\n");
    printf("  -h              Show this help\n\n");  
    printf("Use Ctrl-C to stop.\n\n");

    exit(1);
} 

int main(int argc, char *argv[])
{
    int opt, fd;
    uint32_t val;
    char device[32];

    memset(device, 0, sizeof(device));
    strcpy(device, DEFAULT_DEVICE);
 
    while ((opt = getopt(argc, argv, "d:h")) != -1) {
        switch (opt) {
        case 'd':
            if (strlen(optarg) == 0 || strlen(optarg) > sizeof(device) - 1) {
                printf("\nInvalid device: %s\n", optarg);
                usage();
            }
           
            strcpy(device, optarg); 
            break;

        case 'h':
        default:
            usage();
            break;
        }
    }

    fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // MODE
    val = 0;

    if (ioctl(fd, SPI_IOC_RD_MODE, &val) == -1) {
        perror("ioctl(SPI_IOC_RD_MODE)");
        exit(1);
    }
    else {
        printf("\nRead mode = %u (0x%08X)\n", val, val);
    }

    if (ioctl(fd, SPI_IOC_WR_MODE, &val) == -1) {
        perror("ioctl(SPI_IOC_WR_MODE)");
        exit(1);
    }
    else {
        printf("Wrote mode = %u (0x%08X)\n\n", val, val);
    }

    // BITS PER WORD
    val = 0;

    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &val) == -1) {
        perror("ioctl(SPI_IOC_RD_BITS_PER_WORD)");
        exit(1);
    }
    else {
        printf("Read bits per word = %u (0x%08X)\n", val, val);
    }

    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &val) == -1) {
        perror("ioctl(SPI_IOC_WR_BITS_PER_WORD)");
        exit(1);
    }
    else {
        printf("Wrote bits per word = %u (0x%08X)\n\n", val, val);
    }

    // SPEED
    val = 0;

    if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &val) == -1) {
        perror("ioctl(SPI_IOC_RD_MAX_SPEED_HZ)");
        exit(1);
    }
    else {
        printf("Read speed = %u (0x%08X)\n", val, val);
    }

    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &val) == -1) {
        perror("ioctl(SPI_IOC_WR_MAX_SPEED_HZ)");
        exit(1);
    }
    else {
        printf("Wrote speed = %u (0x%08X)\n\n", val, val);
    }

    // LSB FIRST 
    val = 0;

    if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &val) == -1) {
        perror("ioctl(SPI_IOC_RD_LSB_FIRST)");
        exit(1);
    }
    else {
        printf("Read lsb first = %u (0x%08X)\n", val, val);
    }

    if (ioctl(fd, SPI_IOC_WR_LSB_FIRST, &val) == -1) {
        perror("ioctl(SPI_IOC_WR_LSB_FIRST)");
        exit(1);
    }
    else {
        printf("Wrote lsb first = %u (0x%08X)\n\n", val, val);
    }

    // MODE32 
    val = 0;

    if (ioctl(fd, SPI_IOC_RD_MODE32, &val) == -1) {
        perror("ioctl(SPI_IOC_RD_MODE32)");
        exit(1);
    }
    else {
        printf("Read mode32 first = %u (0x%08X)\n", val, val);
    }

    if (ioctl(fd, SPI_IOC_WR_MODE32, &val) == -1) {
        perror("ioctl(SPI_IOC_WR_MODE32)");
        exit(1);
    }
    else {
        printf("Wrote mode32 = %u (0x%08X)\n\n", val, val);
    }

    close(fd);

    return 0;
}
