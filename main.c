#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city_weather {
    char *name;
    float temperature;
    float wind_speed;
    float humidity;
};

void find_min_max(struct city_weather *cities, int num_cities, char *field, int *min_index, int *max_index);

float get_field_value(struct city_weather city, char *field) {
    if (strcmp(field, "temperature") == 0) {
        return city.temperature;
    } else if (strcmp(field, "wind") == 0) {
        return city.wind_speed;
    } else if (strcmp(field, "humidity") == 0) {
        return city.humidity;
    } else {
        printf("Invalid field: %s\n", field);
        return 0;
    }
}

int main() {
    int num_cities, i;

    // Prompt the user to enter the number of cities they would like to enter weather data for
    printf("Enter the number of cities you would like to enter weather data for: ");
    scanf("%d", &num_cities);

    // Dynamically allocate memory to store the city data based on the user input
    struct city_weather *cities = malloc(num_cities * sizeof(struct city_weather));

    // Prompt the user to enter weather data for each city, including the city name, temperature, wind speed and humidity
    for (i = 0; i < num_cities; i++) {
        cities[i].name = malloc(50 * sizeof(char));
        printf("\nEnter weather data for city %d:\n", i + 1);
        printf("Enter the city name: ");
        scanf("%s", cities[i].name);
        printf("Enter the temperature: ");
        scanf("%f", &cities[i].temperature);
        printf("Enter the wind speed: ");
        scanf("%f", &cities[i].wind_speed);
        printf("Enter the humidity: ");
        scanf("%f", &cities[i].humidity);
    }

   // Display a table of all the entered data
printf("\nWeather data for all cities:\n");
printf("%-20s\t%-12s\t%-12s\t%-12s\n", "City", "%Temperature", "%Wind", "%Humidity");
for (i = 0; i < num_cities; i++) {
    printf("%-20s\t%-12.1f\t%-12.1f\t%-12.1f\n", cities[i].name, cities[i].temperature, cities[i].wind_speed, cities[i].humidity);
}


    // Prompt the user to enter the weather field to find the min and max values for
   printf("\nEnter the weather field (temperature, wind, or humidity) to find the minimum and maximum values: ");
    char field[20];
    scanf("%s", field);

    // Call the find_min_max function to find the minimum and maximum values for the specified field
    int min_index, max_index;
    find_min_max(cities, num_cities, field, &min_index, &max_index);

    // Display the minimum and maximum values for the specified field, along with the name of the city where each value was found
    printf("\nMinimum value for %s: %.2f (found in %s)\n", field, get_field_value(cities[min_index], field), cities[min_index].name);
    printf("Maximum value for %s: %.2f (found in %s)\n", field, get_field_value(cities[max_index], field), cities[max_index].name);

    // Free the dynamically allocated memory for the city names
    for (i = 0; i < num_cities; i++) {
        free(cities[i].name);
    }
    free(cities);

    return 0;
}

void find_min_max(struct city_weather *cities, int num_cities, char *field, int *min_index, int *max_index) {
    int i;

   // Initialize the minimum and maximum values to the first city in the array
*min_index = 0;
*max_index = 0;
int min_value = get_field_value(cities[0], field);
int max_value = get_field_value(cities[0], field);

// Loop through the array to find the minimum and maximum values and their indices
for (i = 1; i < num_cities; i++) {
    int value = get_field_value(cities[i], field);
    if (value < min_value) {
        min_value = value;
        *min_index = i;
    }
    if (value > max_value) {
        max_value = value;
        *max_index = i;
    }
}
}
