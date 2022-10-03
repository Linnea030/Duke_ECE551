#include "pandemic.h"

#include <stdio.h>

country_t parseLine(char * line) {
  //WRITE ME
  //If there is no input, report error and exit
  if (line == NULL) {
    printf("There is no input!\n");
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

  //If there is no comma or the data of population is null, report and exit
  if (line[i] == '\0' || line[i] == '\n') {
    printf("The format of this input  is invalid!\n");
    exit(EXIT_FAILURE);
  }

  int j = i;  //use to put population char into a string

  //while loop to put remaining char into population_c
  while (line[i] != '\0' && line[i] != '\n') {
    //If population number is not a digit number, report error and exit
    if (line[i] < '0' || line[i] > '9') {
      printf("Invalid input of population part, it is not a digit number!\n");
    }
    population_c[i - j] = line[i];
    i++;  //count i
  }
  population_c[i - j + 1] = '\0';  //put a null-terminator at the end to make it a string
  ans.population = atoi(population_c);  //convert the string into int by atoi

  //If there is nothing in the line,report error and exit
  if (ans.name[0] == '\0') {
    printf("No data for country name!\n");
    exit(EXIT_FAILURE);
  }
  if (ans.population == 0) {
    printf("No data for population!\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
