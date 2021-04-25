#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/select.h>
#define INPUT_DEVICE "/dev/input/event6"

int main(int argc, char **argv)
{
	int fd;
	struct input_event event;
	ssize_t bytesRead;
	int ret;
	fd_set readfds;
	fd = open(INPUT_DEVICE, O_RDONLY);
	/* Let's open our input device */
	if(fd < 0){
		fprintf(stderr, "Error opening %s for reading", INPUT_DEVICE);
		exit(EXIT_FAILURE);
	}
	while(1){
#if 0
		bytesRead = read(fd, &event, sizeof(struct input_event));
		if(bytesRead == -1) {
			/* Process read input error*/
			fprintf(stderr, "read error");
		}
		if(bytesRead != sizeof(struct input_event)) {
			/* Read value is not an input even */
			fprintf(stderr, "read value is not an input even");
		}
		/*
		 * We could have done a switch/case if we had
		 * many codes to look for
		 */
		if(event.code == BTN_0) {
			/* it concerns our button */
			if(event.value == 0){
				/* Process Release */
				printf("Key Release\n");
			} else if(event.value == 1){
				/* Process KeyPress */
				printf("Key Press\n");
			}
		}
#else
		/* Wait on fd for input */
		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);

		ret = select(fd + 1, &readfds, NULL, NULL, NULL);
		if (ret == -1) {
			fprintf(stderr, "select call on %s: an error occurred",
					INPUT_DEVICE);
			break;
		} else if (!ret) { /* If we have decided to use timeout */
			fprintf(stderr, "select on %s: TIMEOUT", INPUT_DEVICE);
			break;
		}

		/* File descriptor is now ready */
		if (FD_ISSET(fd, &readfds)) {
			bytesRead = read(fd, &event, sizeof(struct input_event));
			if(bytesRead == -1) {
				/* Process read input error*/
				fprintf(stderr, "read error");
			}
			if(bytesRead != sizeof(struct input_event)) {
				/* Read value is not an input even */
				fprintf(stderr, "read value is not an input even");
			}
			/*
			 * We could have done a switch/case if we had
			 * many codes to look for
			 */
			if(event.code == BTN_0) {
				/* it concerns our button */
				if(event.value == 0) {
					/* Process Release */
					printf("BTN_0 Release\n");
				} else if(event.value == 1) {
					/* Process KeyPress */
					printf("BTN_0 Press\n");
				} 
			} else if (event.code == KEY_1) {
				if (event.value == 0)
					printf("KEY_1 Release\n");
				else if (event.value == 1)
					printf("KEY_1 Press\n");
			}
		}
#endif
	}
	close(fd);
	return EXIT_SUCCESS;
}
