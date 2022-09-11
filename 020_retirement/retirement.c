#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double premonth(double m_initial, double m_rate, double con) {
  double interest = m_initial * m_rate;
  double ans = con + interest + m_initial;
  return ans;
}

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired
  double m_rate = working.rate_of_return / 12;
  while (working.months > 0) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    initial = premonth(initial, m_rate, working.contribution);
    startAge++;
    working.months--;
  }
  double m_r_rate = retired.rate_of_return / 12;
  while (retired.months > 0) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    initial = premonth(initial, m_r_rate, retired.contribution);
    startAge++;
    retired.months--;
  }
}
int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
