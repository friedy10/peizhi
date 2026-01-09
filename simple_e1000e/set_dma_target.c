#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEBUGFS_PATH "/sys/kernel/debug/simple_e1000e/next_rx_addr"

int main(int argc, char *argv[]) {
  int fd;
  unsigned long long addr;
  char buf[32];
  int len;

  if (argc != 2) {
    printf("Usage: %s <hex_address>\n", argv[0]);
    printf("Example: %s 0x12345678\n", argv[0]);
    return 1;
  }

  errno = 0;
  addr = strtoull(argv[1], NULL, 16);
  if (errno != 0) {
    perror("strtoull");
    return 1;
  }

  printf("Setting next RX DMA address to 0x%llx\n", addr);

  fd = open(DEBUGFS_PATH, O_WRONLY);
  if (fd < 0) {
    perror("open debugfs");
    fprintf(stderr, "Is debugfs mounted? Is the driver loaded? (path: %s)\n",
            DEBUGFS_PATH);
    return 1;
  }

  /* Format as hex string with 0x prefix just in case, though debugfs simple
   * attrs usually take simple ints */
  /* Using %llx for u64 */
  len = snprintf(buf, sizeof(buf), "0x%llx", addr);

  if (write(fd, buf, len) < 0) {
    perror("write");
    close(fd);
    return 1;
  }

  close(fd);
  printf("Successfully set next RX DMA address.\n");
  return 0;
}
