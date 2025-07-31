#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGES 3

struct message {
    long priority;
    char text[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg, messages[MAX_MESSAGES];
    
    key = ftok("progfile", 65);
    
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Writing messages to queue...\n");

    // Sending messages
    long priorities[] = {2, 1, 3}; 
    char *texts[] = {"Message with priority 2", "Message with priority 1", "Message with priority 3"};

    for (int i = 0; i < MAX_MESSAGES; i++) {
        msg.priority = priorities[i];
        strcpy(msg.text, texts[i]);
        msgsnd(msgid, &msg, sizeof(msg.text), 0);
    }

    printf("\nReading messages sorted by priority:\n");

    // Retrieve all messages first
    for (int i = 0; i < MAX_MESSAGES; i++) {
        msgrcv(msgid, &messages[i], sizeof(msg.text), 0, 0); // 0 means retrieve any message
    }

    // Sorting messages by priority (Bubble Sort)
    for (int i = 0; i < MAX_MESSAGES - 1; i++) {
        for (int j = i + 1; j < MAX_MESSAGES; j++) {
            if (messages[i].priority > messages[j].priority) {
                struct message temp = messages[i];
                messages[i] = messages[j];
                messages[j] = temp;
            }
        }
    }

    // Printing sorted messages
    for (int i = 0; i < MAX_MESSAGES; i++) {
        printf("Priority %ld: %s\n", messages[i].priority, messages[i].text);
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
