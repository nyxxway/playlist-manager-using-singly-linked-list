#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a Song node in the playlist
struct Song {
    char title[100];
    char artist[100];
    struct Song *next; // Pointer to the next song
};

struct Song *head = NULL; // Head pointer for the playlist

// Function to create a new song node
struct Song* createSong(char title[], char artist[]) {
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song)); // Allocate memory
    strcpy(newSong->title, title);   // Copy title into the node
    strcpy(newSong->artist, artist); // Copy artist name
    newSong->next = NULL;            // Set next to NULL as it's the last node initially
    return newSong;
}

// Function to add a song at the end of the playlist
void addSong(char title[], char artist[]) {
    struct Song *newSong = createSong(title, artist); // Create new song node

    if (head == NULL) {
        head = newSong; // If playlist is empty, new song becomes head
    } else {
        struct Song *temp = head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to the end of the list
        }
        temp->next = newSong; // Link new song at the end
    }
    printf("Song added: %s by %s\n", title, artist);
}

// Function to display all songs in the playlist
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    struct Song *temp = head;
    int index = 1;
    printf("\n--- Playlist ---\n");
    while (temp != NULL) {
        // Print each song with its index
        printf("%d. %s by %s\n", index++, temp->title, temp->artist);
        temp = temp->next;
    }
}

// Function to delete a song by title
void deleteSong(char title[]) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song *temp = head, *prev = NULL;

    // Traverse the list to find the song
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        // Song not found
        printf("Song not found: %s\n", title);
        return;
    }

    // If the song to delete is the first song
    if (prev == NULL) {
        head = head->next;
    } else {
        prev->next = temp->next; // Bypass the node to delete it
    }

    free(temp); // Free memory of deleted node
    printf("Song deleted: %s\n", title);
}

// Function to play the next song (first song in the list)
void playNext() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    // Display and remove the first song
    printf("Now playing: %s by %s\n", head->title, head->artist);
    struct Song *temp = head;
    head = head->next; // Move head to the next song
    free(temp); // Free memory of the played song
}

// Main function with menu interface
int main() {
    int choice;
    char title[100], artist[100];

    while (1) {
        // Show menu
        printf("\n1. Add Song\n2. Delete Song\n3. Display Playlist\n4. Play Next\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                // Add a new song
                printf("Enter song title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove newline
                printf("Enter artist name: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = '\0'; // Remove newline
                addSong(title, artist);
                break;

            case 2:
                // Delete a song by title
                printf("Enter song title to delete: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove newline
                deleteSong(title);
                break;

            case 3:
                // Display the playlist
                displayPlaylist();
                break;

            case 4:
                // Play the next song
                playNext();
                break;

            case 5:
                // Exit the program
                printf("Exiting...\n");
                return 0;

            default:
                // Invalid input
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
