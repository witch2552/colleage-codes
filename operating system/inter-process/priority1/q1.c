#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Structure for message queue
struct message {
    long priority;  // Priority of the message (lower value = higher priority)
    char text[100]; // Message content
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key
    key = ftok("progfile", 65);
    
    // Create a message queue with read and write permissions
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Writing messages with different priorities
    printf("Writing messages to queue...\n");
    
    msg.priority = 2;
    strcpy(msg.text, "Message with priority 2");
    msgsnd(msgid, &msg, sizeof(msg.text), 0);
    
    msg.priority = 1;
    strcpy(msg.text, "Message with priority 1");
    msgsnd(msgid, &msg, sizeof(msg.text), 0);
    
    msg.priority = 3;
    strcpy(msg.text, "Message with priority 3");
    msgsnd(msgid, &msg, sizeof(msg.text), 0);
    
    printf("Messages written successfully.\n\nReading messages in priority order:\n");

    // Reading messages in priority order
    for (int i = 1; i <= 3; i++) {
        msgrcv(msgid, &msg, sizeof(msg.text), i, 0); // Retrieve based on priority
        printf("Priority %ld: %s\n", msg.priority, msg.text);
    }

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
    
    return 0;
}
