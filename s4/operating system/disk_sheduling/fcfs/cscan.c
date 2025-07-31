#include <stdio.h>
#include <stdlib.h>

#define MAX 100


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

void c_scan(int request[], int n, int head, int disk_size) {
    int seek_count = 0, distance, current_track;
    int left[MAX], right[MAX], left_size = 0, right_size = 0;

    // Adding head position to left and right arrays
    for (int i = 0; i < n; i++) {
        if (request[i] < head)
            left[left_size++] = request[i];
        else
            right[right_size++] = request[i];
    }

    // Sorting left and right parts
    sort(left, left_size);
    sort(right, right_size);

    printf("Seek Sequence: ");
    
    // Moving to the right side
    for (int i = 0; i < right_size; i++) {
        current_track = right[i];
        printf("%d -> ", current_track);
        distance = abs(current_track - head);
        seek_count += distance;
        head = current_track;
    }

    // Move to the maximum disk size (simulate jump)
    printf("%d -> ", disk_size - 1);
    seek_count += abs(disk_size - 1 - head);
    head = 0; // Jump back to start

    // Moving to the left side
    for (int i = 0; i < left_size; i++) {
        current_track = left[i];
        printf("%d -> ", current_track);
        distance = abs(current_track - head);
        seek_count += distance;
        head = current_track;
    }

    printf("\nTotal Seek Count: %d\n", seek_count);
}

int main() {
    int n, head, disk_size;

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

    c_scan(request, n, head, disk_size);

    return 0;
}
