//--app-key.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
// 运行方法 ： ./app /dev/input/event2

/*
   struct input_event {
   struct timeval time;
   __u16 type; //
   __u16 code; //状态
   __s32 value;//键值
   };
 */
int main(int argc, char **argv)
{
	int count, i;
	int fd;

	//struct input_event 专门用来存放基于输入子系统上报的数据的结构
	struct input_event ev_key;

	if(argc != 2)
		printf("usge：%s /dev/eventX\r\n",argv[0]);

	fd = open(argv[1], O_RDWR);//根据实际情况 有可能不是
	if (fd < 0)
	{
		perror("open device key!");
		exit(1);
	}

	while (1) {
		count = read(fd, &ev_key, sizeof(struct input_event));
		if (EV_KEY == ev_key.type) {
			printf("type:%d,code:%d,value:%d\n", ev_key.type, ev_key.code, ev_key.value);
			if(ev_key.value==1) {
				printf("key down\r\n");
			} else {
				printf("key up\r\n");
			}
		}

		if (EV_SYN == ev_key.type)
			printf("syn event\n");
	}
	close(fd);

	return 0;
}
