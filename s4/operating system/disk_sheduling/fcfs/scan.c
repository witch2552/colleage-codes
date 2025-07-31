#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Bubble sort function to sort the requests
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// SCAN disk scheduling algorithm
void scan(int request[], int n, int head, int disk_size, int direction) {
    int seek_count = 0, distance, current_track;
    int left[MAX], right[MAX], left_size = 0, right_size = 0;

    // Splitting requests into left and right arrays
    for (int i = 0; i < n; i++) {
        if (request[i] < head)
            left[left_size++] = request[i];
        else
            right[right_size++] = request[i];
    }

    // Sorting requests in ascending order
    sort(left, left_size);
    sort(right, right_size);

    printf("\nSeek Sequence: ");

    if (direction == 1) { // Moving right first
        for (int i = 0; i < right_size; i++) {
            current_track = right[i];
            printf("%d -> ", current_track);
            distance = abs(current_track - head);
            seek_count += distance;
            head = current_track;
        }

        // Move to disk end
        printf("%d -> ", disk_size - 1);
        seek_count += abs(disk_size - 1 - head);
        head = disk_size - 1;

        // Moving left
        for (int i = left_size - 1; i >= 0; i--) {
            current_track = left[i];
            printf("%d -> ", current_track);
            distance = abs(current_track - head);
            seek_count += distance;
            head = current_track;
        }
    } else { // Moving left first
        for (int i = left_size - 1; i >= 0; i--) {
            current_track = left[i];
            printf("%d -> ", current_track);
            distance = abs(current_track - head);
            seek_count += distance;
            head = current_track;
        }

        // Move to disk start
        printf("0 -> ");
        seek_count += abs(head - 0);
        head = 0;

        // Moving right
        for (int i = 0; i < right_size; i++) {
            current_track = right[i];
            printf("%d -> ", current_track);
            distance = abs(current_track - head);
            seek_count += distance;
            head = current_track;
        }
    }

    printf("\nTotal Seek Count: %d\n", seek_count);
}

// Main function
int main() {
    int n, head, disk_size, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int request[MAX];

    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    scan(request, n, head, disk_size, direction);

    return 0;
}
