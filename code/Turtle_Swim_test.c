 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <pthread.h>
#include <math.h>
#include <netinet/in.h>
#include <signal.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9080
#define CAN_INTERFACE "can0"

int stopFlag = 1;

typedef struct {
    int isMovingForward;
    int isMovingBackward;
    int isTurningLeft;
    int isTurningRight;
    int isStop;
} RobotState;

// 初始化机器人状态
RobotState robot = {0, 0, 0, 0, 0};

// Mutex for thread synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void receiveCommand(char command) {
    switch (command) {
        case 0:
            stopFlag = 1;
            robot.isMovingForward = 0;
            robot.isMovingBackward = 0;
            robot.isTurningLeft = 0;
            robot.isTurningRight = 0;
            robot.isStop = 1;
            break;
        case 1:
            stopFlag = 0;
            robot.isMovingForward = 1;
            robot.isMovingBackward = 0;
            robot.isTurningLeft = 0;
            robot.isTurningRight = 0;
            robot.isStop = 0;
            break;
        case 2:
            stopFlag = 0;
            robot.isMovingForward = 0;
            robot.isMovingBackward = 1;
            robot.isTurningLeft = 0;
            robot.isTurningRight = 0;
            robot.isStop = 0;
            break;
        case 3:
            stopFlag = 0;
            robot.isMovingForward = 0;
            robot.isMovingBackward = 0;
            robot.isTurningLeft = 1;
            robot.isTurningRight = 0;
            robot.isStop = 0;
            break;
        case 4:
            stopFlag = 0;
            robot.isMovingForward = 0;
            robot.isMovingBackward = 0;
            robot.isTurningLeft = 0;
            robot.isTurningRight = 1;
            robot.isStop = 0;
            break;
        default:
            // 处理未知指令
            break;
    }
}

void moveStop(int s) {
    stopFlag = 1;
    struct can_frame frame;
    frame.can_id = 0x01;
    frame.can_dlc = 6;
    frame.data[0] = 0x01;
    frame.data[1] = 0x11;
    frame.data[2] = 0x00;
    frame.data[3] = 0x00;
    frame.data[4] = 0x00;
    frame.data[5] = 0x01;
    write(s, &frame, sizeof(frame));
	frame.can_id = 0x02;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x03;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x04;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x05;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x06;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x07;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x08;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x09;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0B;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0C;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x11;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
}

//Padding Gait
void moveForward(int s) {
    stopFlag = 0;
    struct can_frame frame;

	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);

	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xD8;
	frame.data[5] = 0xE4;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x006;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x27;
	frame.data[5] = 0x1B;
	write(s, &frame, sizeof(frame));
	sleep(1);

	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xCE;
	frame.data[5] = 0x39;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x31;
	frame.data[5] = 0xC7;
	write(s, &frame, sizeof(frame));
	sleep(1);

	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x006;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);

	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x3C;
	frame.data[5] = 0x71;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xC3;
	frame.data[5] = 0x8F;
	write(s, &frame, sizeof(frame));
	
	frame.can_id = 0x003;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x23;
	frame.data[5] = 0x8E;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x004;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xDC;
	frame.data[5] = 0x72;
	write(s, &frame, sizeof(frame));
	sleep(2);

	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);

	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);

}
//游泳手臂向前摆测试
void turnLeft(int s) {
    stopFlag = 0;
    struct can_frame frame;
	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);

	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xCE;
	frame.data[5] = 0x39;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x31;
	frame.data[5] = 0xC7;
	write(s, &frame, sizeof(frame));
    sleep(1);

	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x3C;
	frame.data[5] = 0x71;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xC3;
	frame.data[5] = 0x8F;
	write(s, &frame, sizeof(frame));
	sleep(1);
}
//Flapping Gaiting
void turnRight(int s) {
    stopFlag = 0;
    struct can_frame frame;
	//45度
	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xE0;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x20;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);
	//50度
	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xDC;
	frame.data[5] = 0x72;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x006;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x23;
	frame.data[5] = 0x8E;
	write(s, &frame, sizeof(frame));
	//50度
	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xDC;
	frame.data[5] = 0x72;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x23;
	frame.data[5] = 0x8E;
	write(s, &frame, sizeof(frame));
	sleep(2);

	//45度
	frame.can_id = 0x0A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xE0;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x20;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);
	//50度
	frame.can_id = 0x006;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xDC;
	frame.data[5] = 0x72;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x23;
	frame.data[5] = 0x8E;
	write(s, &frame, sizeof(frame));
	//50度
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[1] = 0x0A;
	frame.data[2] = 0xFF;
	frame.data[3] = 0xFF;
	frame.data[4] = 0xDC;
	frame.data[5] = 0x72;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x23;
	frame.data[5] = 0x8E;
	write(s, &frame, sizeof(frame));
	sleep(2);
}

void moveBackward(int s) {
    stopFlag = 0;

}

void* threadMoveStop(void* arg) {
    printf("SS\n");
    int s = *((int*)arg);
    while(1){
        if (robot.isStop){
            if(stopFlag != 1){
                stopFlag = 1;
                moveStop(s);
                printf("Stop\n");
        }
    }
}}

void* threadMoveForward(void* arg) {
    printf("FF\n");
    int s = *((int*)arg);
    while(1){
        if (robot.isMovingForward){
            stopFlag = 0;
            moveForward(s);
            printf("F");
        }
    }
}

void* threadMoveBackward(void* arg) {
    printf("BB\n");
    int s = *((int*)arg);
    while(1){
        if (robot.isMovingBackward){
            stopFlag = 0;
            moveBackward(s);
            printf("B\n");
        }
    }
}

void* threadTurnLeft(void* arg) {
    printf("LL\n");
    int s = *((int*)arg);
    while(1){
        if (robot.isTurningLeft){
            stopFlag = 0;
            turnLeft(s);
            printf("L");
        }
    }
}

void* threadTurnRight(void* arg) {
    printf("RR\n");
    int s = *((int*)arg);
    while(1){
        if (robot.isTurningRight){
            stopFlag = 0;
            turnRight(s);
            printf("R");
        }
    }
}

int main() {
    system("set can0");
    system("ip link set can0 down");
    system("ip link set can0 up type can bitrate 1000000");
    system("candump cam0 -L &");
    int client_socket;
    struct sockaddr_in server_addr;

    // 创建套接字
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址信息
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");
    char username[] = "limb";
    char message[] = "Sent username to the server\n";
    send(client_socket, username, sizeof(username), 0);
    send(client_socket, message, sizeof(message), 0);
    printf("Sent username to the server\n");
    sleep(0.5);

    // 打开CAN设备
    int s, loop;
    struct sockaddr_can can_addr;
    struct ifreq ifr;
    struct can_frame frame;

    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    strcpy(ifr.ifr_name, CAN_INTERFACE);
    ioctl(s, SIOCGIFINDEX, &ifr);
    can_addr.can_family = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr *)&can_addr, sizeof(can_addr));

    pthread_t threadStop, threadForward, threadBackward, threadLeft, threadRight;

	
	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x003;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x003;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x004;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x004;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x006;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x006;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x007;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x007;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x008;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x008;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x55;
	frame.data[5] = 0x55;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x00A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x00A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x55;
	frame.data[5] = 0x55;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x00B;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x00B;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);
	frame.can_id = 0x00C;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x10;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x01;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x00C;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x09;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x2A;
	frame.data[5] = 0xAA;
	write(s, &frame, sizeof(frame));
	sleep(0.1);

	frame.can_id = 0x001;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x002;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x003;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x004;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);
	frame.can_id = 0x005;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x006;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	
	frame.can_id = 0x007;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	
	frame.can_id = 0x008;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	sleep(1);
	frame.can_id = 0x009;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x00A;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	
	frame.can_id = 0x00B;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));
	frame.can_id = 0x00C;
	frame.can_dlc = 6;
	frame.data[0] = 0x01;
	frame.data[1] = 0x0A;
	frame.data[2] = 0x00;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	write(s, &frame, sizeof(frame));

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    pthread_mutex_lock(&mutex); // Lock mutex to avoid race condition

    pthread_create(&threadStop, NULL, threadMoveStop, (void*)&s);
    pthread_create(&threadForward, NULL, threadMoveForward, (void*)&s);
    pthread_create(&threadBackward, NULL, threadMoveBackward, (void*)&s);
    pthread_create(&threadLeft, NULL, threadTurnLeft, (void*)&s);
    pthread_create(&threadRight, NULL, threadTurnRight, (void*)&s);
    
    pthread_mutex_unlock(&mutex); // Unlock mutex
    while (1) {
        // 从服务器接收指令
        char server_code;
        //char stop = 0;
        //ssize_t bytes_received = recv(client_socket, &server_code, sizeof(server_code), 0);

        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(client_socket, &readSet);

        struct timeval timeout;
        timeout.tv_sec = 1;  
        timeout.tv_usec = 0;

        int ready = select(client_socket + 1, &readSet, NULL, NULL, &timeout);

        if (ready == -1) {
            perror("Select failed");
            break;
        }

        if (ready > 0) {
            // 有数据可读，接收指令
            int receivedCommand;
            ssize_t bytesRead = recv(client_socket, &receivedCommand, sizeof(receivedCommand), 0);

            if (bytesRead <= 0) {
                // 处理接收错误或连接断开的情况
                printf("Connection closed or error in receiving command\n");
                break;
            }

            // 处理接收到的指令
            // 这里可以调用你的处理函数，比如调用 receiveCommand(receivedCommand);
            receiveCommand(receivedCommand);
            printf("%d\n%d\n%d\n%d\n%d\n",robot.isStop,robot.isMovingForward,robot.isMovingBackward,robot.isTurningLeft,robot.isTurningRight);
        } else {
            // 在没有收到消息时执行的代码
            if(stopFlag != 1){
                //char abc = 0;
                //printf("No message received. Performing other tasks...\n");
                
                //receiveCommand(abc);
                
                
            }
            //printf("No message received. Performing other tasks...\n");
            //receiveCommand(stop);
            
        }
    

        /*if (bytes_received <= 0) {
            // 处理连接中断或错误
            perror("Error receiving data from server");
            break;
        }
        if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
        perror("Set socket timeout failed");
        receiveCommand(stop);
        printf("Time Out! Stop command received\n");
        }

        receiveCommand(server_code);
        printf("%d\n%d\n%d\n%d\n%d\n",robot.isStop,robot.isMovingForward,robot.isMovingBackward,robot.isTurningLeft,robot.isTurningRight);

        // 根据接收到的指令创建相应的线程
        /*pthread_mutex_lock(&mutex); // Lock mutex to avoid race condition

        pthread_create(&threadStop, NULL, threadMoveStop, (void*)&s);
        pthread_create(&threadForward, NULL, threadMoveForward, (void*)&s);
        pthread_create(&threadLeft, NULL, threadTurnLeft, (void*)&s);
        pthread_create(&threadRight, NULL, threadTurnRight, (void*)&s);

        /*switch (server_code) {
            case 0:
                pthread_create(&threadStop, NULL, threadMoveStop, (void*)&s);
                break;
            case 1:
                pthread_create(&threadForward, NULL, threadMoveForward, (void*)&s);
                break;
            case 2:
                pthread_create(&threadLeft, NULL, threadTurnLeft, (void*)&s);
                break;
            case 3:
                pthread_create(&threadRight, NULL, threadTurnRight, (void*)&s);
                break;
            default:
                printf("Unknown code received: %d\n", server_code);
                break;
        }

        pthread_mutex_unlock(&mutex); // Unlock mutex
        */
    }

    // 等待线程结束
    pthread_join(threadStop, NULL);
    pthread_join(threadForward, NULL);
    pthread_join(threadLeft, NULL);
    pthread_join(threadRight, NULL);

    // 关闭套接字
    close(client_socket);
    close(s);

    return 0;
}