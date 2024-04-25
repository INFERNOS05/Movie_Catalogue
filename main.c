#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Movie {
    char title[50];
    char genre[50];
    int release_year;
    int serial_number;
};

int CountEntries() {
    FILE *file = fopen("/Users/sehajdeep/Downloads/Movie_Catalogue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    int count = 0;
    char line[100]; // Assuming no line will be longer than 100 characters
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Title:") != NULL) {
            count++;
        }
    }
    fclose(file);
    return count;
}

void File() {
    FILE *file = fopen("/Users/sehajdeep/Downloads/Movie_Catalogue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Movie Catalogue:\n");

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}

void AddMovie() {
    int num_movies;
    printf("Enter number of movies you want to enter details about: ");
    scanf("%d", &num_movies);
    getchar(); // Consume the newline character left in the input buffer
    FILE *file = fopen("/Users/sehajdeep/Downloads/Movie_Catalogue.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_movies; ++i) {
        struct Movie movie;
        printf("Enter Serial Number of the entry: ");
        scanf("%d", &movie.serial_number);
        printf("Enter Title for Movie %d: ", i + 1);
        scanf(" %[^\n]", movie.title);
        printf("Enter Genre for Movie %d: ", i + 1);
        scanf(" %[^\n]", movie.genre);
        printf("Enter Year of Release for Movie %d: ", i + 1);
        scanf("%d", &movie.release_year);
        getchar(); // Consume the newline character left in the input buffer
        fprintf(file, "Sr No. : %d\nTitle: %s\nGenre: %s\nYear of Release: %d\n",
                movie.serial_number,movie.title, movie.genre, movie.release_year);
    }

    fclose(file);
    printf("Movie details saved!\n");
}

void DisplayMoviesByGenre(char genre[]) {
    FILE *file = fopen("/Users/sehajdeep/Downloads/Movie_Catalogue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Movies with genre \"%s\":\n", genre);
    struct Movie movie;
    while (fscanf(file, "Sr No. : %d\nTitle: %[^\n]\nGenre: %[^\n]\nYear of Release: %d\n",
                  &movie.serial_number, movie.title, movie.genre, &movie.release_year) == 4) {
        if (strcmp(movie.genre, genre) == 0) {
            printf("Sr No. : %d\nTitle: %s\nGenre: %s\nYear of Release: %d\n\n",
                   movie.serial_number,movie.title, movie.genre, movie.release_year);
        }
    }

    fclose(file);
}

void DisplayMoviesByYear(int year) {
    FILE *file = fopen("/Users/sehajdeep/Downloads/Movie_Catalogue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Movies released in the year %d:\n", year);
    struct Movie movie;
    while (fscanf(file, "Sr No. : %d\nTitle: %[^\n]\nGenre: %[^\n]\nYear of Release: %d\n",
                  &movie.serial_number, movie.title, movie.genre, &movie.release_year) == 4) {
        if (movie.release_year == year) {
            printf("Sr No. : %d\nTitle: %s\nGenre: %s\nYear of Release: %d\n\n",
                   movie.serial_number,movie.title, movie.genre, movie.release_year);
        }
    }

    fclose(file);
}
void RemoveMovie() {
    char input[50];
    printf("Enter the title or serial number of the movie to remove: ");
    scanf("%49[^\n]", input);
    getchar(); // Consume the newline character left in the input buffer

    // Open the file for reading
    FILE *file = fopen("/Users/sehajdeep/Downloads/Movie_Catalogue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Create a temporary file to store movies except the one to be removed
    FILE *tempFile = fopen("/Users/sehajdeep/Downloads/Temp_Movie_Catalogue.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    struct Movie movie;
    int found = 0; // Flag to indicate if the movie was found
    while (fscanf(file, "Sr No. : %d\nTitle: %[^\n]\nGenre: %[^\n]\nYear of Release: %d\n",
                  &movie.serial_number, movie.title, movie.genre, &movie.release_year) == 4) {
        if (strcmp(input, movie.title) == 0 || atoi(input) == movie.serial_number) {
            found = 1;
            continue; // Skip writing this movie to the temporary file
        }
        fprintf(tempFile, "Sr No. : %d\nTitle: %s\nGenre: %s\nYear of Release: %d\n",
                movie.serial_number, movie.title, movie.genre, movie.release_year);
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file to the original name
    remove("/Users/sehajdeep/Downloads/Movie_Catalogue.txt");
    rename("/Users/sehajdeep/Downloads/Temp_Movie_Catalogue.txt", "/Users/sehajdeep/Downloads/Movie_Catalogue.txt");

    if (found) {
        printf("Movie removed successfully!\n");
    } else {
        printf("Movie not found.\n");
    }
}


int main() {
    int choice;
    printf("Total number of entries: %d\n", CountEntries());
    printf("1. Enter records in the Movie Catalogue\n");
    printf("2. View the Movie Catalogue\n");
    printf("3. View movies with selected criteria (genre and year)\n");
    printf("4. Remove a movie\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character left in the input buffer

    if (choice == 1) {
        AddMovie();
    } else if (choice == 2) {
        File();
    } else if (choice == 3) {
        int criteria_choice;
        printf("Select criteria:\n");
        printf("1. Genre\n");
        printf("2. Year of Release\n");
        printf("Enter your choice: ");
        scanf("%d", &criteria_choice);
        getchar(); // Consume the newline character left in the input buffer

        if (criteria_choice == 1) {
            char genre[50];
            printf("Enter the genre to filter movies: ");
            scanf("%49[^\n]", genre);
            getchar(); // Consume the newline character left in the input buffer
            DisplayMoviesByGenre(genre);
        } else if (criteria_choice == 2) {
            int year;
            printf("Enter the year to filter movies: ");
            scanf("%d", &year);
            getchar(); // Consume the newline character left in the input buffer
            DisplayMoviesByYear(year);
        } else {
            printf("Invalid choice for criteria.\n");
        }
    } else if (choice == 4) {
        RemoveMovie();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
