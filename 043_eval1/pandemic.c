#include "pandemic.h"

#include <stdio.h>

country_t parseLine(char * line) {
  //WRITE ME
  //If there is no input, report error and exit
  if (line == NULL) {
    fprintf(stderr, "There is no input!\n");
    exit(EXIT_FAILURE);
  }

  //Initialization of variable
  int i = 0;                    //use to count the size of line
  char population_c[64] = {0};  //population number as char
  country_t ans;                //the return value of this function
  ans.name[0] = '\0';           //initialize name in ans as null
  ans.population = 0;           //initialize population in ans as 0

  //while loop to put string before comma into the ans.name
  while (line[i] != '\0' && line[i] != '\n') {
    if (line[i] == ',') {
      ans.name[i] = '\0';  //give a null-terminator at the end to make it a string
      i++;                 //count i to skip comma
      break;               //when encounter comma,quit the loop
    }
    ans.name[i] = line[i];  //put char into name
    i++;                    //count i
  }
  //If country name size is too big
  if (i > 64) {
    fprintf(stderr, "The line of country name is out of range!\n");
    exit(EXIT_FAILURE);
  }
  //If there is no comma or the data of population is null, report and exit
  if (line[i] == '\0' || line[i] == '\n') {
    fprintf(stderr, "The format of this input is invalid!\n");
    exit(EXIT_FAILURE);
  }

  int j = i;  //use to put population char into a string

  //while loop to put remaining char into population_c
  while (line[i] != '\0' && line[i] != '\n') {
    //If population number is not a digit number, report error and exit
    if (line[i] < '0' || line[i] > '9') {
      fprintf(stderr, "Invalid input of population part, it is not a digit number!\n");
      exit(EXIT_FAILURE);
    }
    population_c[i - j] = line[i];
    i++;  //count i
  }
  population_c[i - j + 1] = '\0';  //put a null-terminator at the end to make it a string
  ans.population = atoi(population_c);  //convert the string into int by atoi

  //If there is nothing in the line,report error and exit
  if (ans.name[0] == '\0') {
    fprintf(stderr, "No data for country name!\n");
    exit(EXIT_FAILURE);
  }
  if (ans.population == 0) {
    fprintf(stderr, "No data for population!\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  size_t i = 0;  //count for days
  //If there is no data
  if (data == NULL) {
    fprintf(stderr, "No data in the array!\n");
    exit(EXIT_FAILURE);
  }
  //If there is no data in array
  if (n_days == 0) {
    fprintf(stderr, "The size of data is zero!\n");
    exit(EXIT_FAILURE);
  }
  //If n_days is smaller than 7
  if (n_days < 7) {
    //printf("The data is not enough for 7 days!\n");
    return;
  }
  //If avg is NULL, no array to write into
  if (avg == NULL) {
    fprintf(stderr, "The array to write into is NULL!\n");
    exit(EXIT_FAILURE);
  }
  //If n_days is larger than 6
  for (; i < n_days - 6; i++) {
    avg[i] = (data[i] + data[i + 1] + data[i + 2] + data[i + 3] + data[i + 4] +
              data[i + 5] + data[i + 6]) /
             (double)7;  //convert it to double using cast
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  //If data is null
  if (data == NULL) {
    fprintf(stderr, "There is no input data!\n");
    exit(EXIT_FAILURE);
  }
  //If population is zero
  if (pop == 0) {
    fprintf(stderr, "Population is zero!\n");
    exit(EXIT_FAILURE);
  }
  //If there is no data cases
  if (n_days == 0) {
    fprintf(stderr, "There is no data cases!\n");
    exit(EXIT_FAILURE);
  }
  //If cum is NULL, no array to write into
  if (cum == NULL) {
    fprintf(stderr, "The array to write into is NULL!\n");
    exit(EXIT_FAILURE);
  }

  size_t base = 100000;  //per 100,000 people
  unsigned sum = 0;

  for (size_t i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = (double)sum / pop * base;  //the cumulative cases per 100,000 people
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  //If there is no data
  if (data == NULL) {
    fprintf(stderr, "There is no input data!\n");
    exit(EXIT_FAILURE);
  }
  //If there is no country
  if (countries == NULL) {
    fprintf(stderr, "There is no country!\n");
    exit(EXIT_FAILURE);
  }
  //If the n_days is invalid
  if (n_days == 0) {
    fprintf(stderr, "n_days is invalid!\n");
    exit(EXIT_FAILURE);
  }
  //If the n_countries is invalid
  if (n_countries == 0) {
    fprintf(stderr, "n_countries is invalid!\n");
    exit(EXIT_FAILURE);
  }
  unsigned tempMax = 0;
  unsigned max = 0;
  size_t index = 0;
  //using for loop to traverse the whole array
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > tempMax) {  //if there is a larger one, update tempMax
        tempMax = data[i][j];
      }
    }
    if (max <
        tempMax) {  //if tempMax(for the row) is larger than Max(for the whole array), update Max
      max = tempMax;
      index = i;
    }
  }
  printf("%s has the most daily cases with %u\n", countries[index].name, tempMax);
}
