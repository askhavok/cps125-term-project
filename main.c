#include <stdio.h>

//VARIABLE DECLARATIONS
FILE *laketemps;
double sum[6] = {0, 0, 0, 0, 0, 0};
double avgtemp[6] = {0, 0, 0, 0, 0, 0};
double totalavgtemp = 0;
//maxtemps-> row 0 for temp, row 1 for the lake it is, row 2 for the day it is.
double maxavg, minavg, maxwarmtemp[3][1], maxcoldtemp[3][1];
int warmtoswim[6] = { 0,0,0,0,0,0 }, coldtoswim[6] = { 0,0,0,0,0,0 };
double warmestday[2][6], coldestday[2][6]= { {0,0,0,0,0,0}, { 10000, 10000, 10000, 10000, 10000, 10000}};
int initialspot[] = { 0,1,2,3,4,5 };
char* initials[] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Claire"};
double data[8][365];

void sort(double x[], char order, int y[]){
    double temp1;
    int temp2;
    int n=6;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (order == 'd') {
                if (x[i] < x[j]) {
                    temp1 = x[i];
                    x[i] = x[j];
                    x[j] = temp1;
                    temp2 = y[i];
                    y[i] = y[j];
                    y[j] = temp2;
                }
            } else if(order == 'a'){
                if (x[i] > x[j]) {
                    temp1 = x[i];
                    x[i] = x[j];
                    x[j] = temp1;
                    temp2 = y[i];
                    y[i] = y[j];
                    y[j] = temp2;
                }
            }
        }
    }
    for(int z=0;z<n;z++){
        int j = y[z];
        printf("%.2lf at %s, ",x[z], initials[j]);
    }
}

int main() {
    laketemps = fopen("C:\\Users\\erioh\\CLionProjects\\WeatherProject\\glsea-temps2019_1024.txt","r"); //fix the directory

    //if the file doesnt exist or isnt in the right place, exit program
    if (laketemps == NULL) {
        printf("Cannot open file, does it exist?\n");
        return -1;
    }

    for (int i = 0; i < 365; i++) {
        //collect data from the file
        for (int j = 0; j < 8; j++) {
            fscanf(laketemps, "%lf", &data[j][i]);
        }
        //printf("%lf \n", data[1][i]);

        //calculate sum
        for (int j = 0; j < 6; j++) {
            sum[j] += data[j + 2][i];
            if(data[j+2][i]>warmestday[1][j]){
                warmestday[1][j]= data[j+2][i];
                warmestday[0][j] = i;
            }
            if(data[j+2][i]<coldestday[1][j]){
                coldestday[1][j]= data[j+2][i];
                coldestday[0][j] = i;
            }
            if(data[j+2][i]>20){
                warmtoswim[j]++;
            }
            if(data[j+2][i]<0){
                coldtoswim[j]++;
            }
        }
    }


    //calculate avg temp and total avg temp
    for (int i = 0; i < 6; i++) {
        maxavg = avgtemp[0];
        minavg = avgtemp[0];
        avgtemp[i] = sum[i] / 365;
        totalavgtemp += avgtemp[i];
        if (avgtemp[i] > maxavg) {
            maxavg = avgtemp[i];
        }
        if (avgtemp[i] < minavg) {
            minavg = avgtemp[i];
        }
    }
    totalavgtemp = totalavgtemp / 6;
    maxwarmtemp[0][0] = warmestday[1][0];
    maxcoldtemp[0][0] =  coldestday[1][0];
    //Find the warmest lake, and see which are above/below avg temp
    for (int i = 0; i < 6; i++) {
        if (avgtemp[i] > totalavgtemp) {
            printf("Lake %s is above the average temperature of all the lakes \n", initials[i]);
        } else if (avgtemp[i] < totalavgtemp) {
            printf("Lake %s is below the average temperature of all the lakes \n", initials[i]);
        }

        if(maxavg==avgtemp[i]){
            printf("The warmest lake is lake %s\n", initials[i]);
        }
        if(minavg==avgtemp[i]){
            printf("The coldest lake is lake %s\n", initials[i]);
        }
        printf("Warmest temperature for lake %s: %.2lf on day %.lf \n", initials[i], warmestday[1][i], warmestday[0][i]+1);
        printf("Coldest temperature for lake %s: %.2lf on day %.lf \n", initials[i], coldestday[1][i], coldestday[0][i]+1);

        if(warmestday[1][i]>maxwarmtemp[0][0]){
            maxwarmtemp[0][0] = warmestday[1][i];
            maxwarmtemp[1][0] = i;
            maxwarmtemp[2][0] = warmestday[0][i];
        }
        if(coldestday[1][i]<maxcoldtemp[0][0]) {
            maxcoldtemp[0][0] = coldestday[1][i];
            maxcoldtemp[1][0] = i;
            maxcoldtemp[2][0] = coldestday[0][i];
        }
        printf("For %d days, the water's warm enough to swim in this lake\n", warmtoswim[i]);
        printf("For %d days, the water's too cold to swim in this lake\n", coldtoswim[i]);
        printf("\n");
    }
    int initial1 = maxwarmtemp[1][0];
    printf("The warmest overall temperature is %.2lf at lake %s on day %.lf\n",maxwarmtemp[0][0], initials[initial1], maxwarmtemp[2][0]+1);
    printf("The coldest overall temperature is %.2lf on multiple days in multiple lakes \n",maxcoldtemp[0][0]);

    double summersum[6] = {0,0,0,0,0,0};
    double summeravg[6] = {0,0,0,0,0,0};
    for(int i=171; i<265;i++){
        for (int j = 0; j < 6; j++) {
            summersum[j] += data[j + 2][i];
            }
        }
    for(int i=0;i<6;i++){
        summeravg[i] = summersum[i]/95;
    }
    printf("\n");
    printf("The sorted warmest average temperatures, in degrees, during the summer are ");
    sort(summeravg,'d', initialspot);

    printf("\n");

    double wintersum[6] = {0,0,0,0,0,0};
    double winteravg[6] = {0,0,0,0,0,0};
    for(int i=0;i<79;i++){
        for(int j=0; j<6;j++){
            wintersum[j] += data[j+2][i];
        }
    }
    for(int i=354;i<365;i++){
        for(int j=0; j<6; j++){
            wintersum[j] += data[j+2][i];
        }
    }
    for(int i=0; i<6; i++){
        winteravg[i] = wintersum[i]/90;
    }
    printf("The sorted warmest average temperatures, in degrees, during the winter are ");
    sort(winteravg,'d',initialspot);



    return 0;
    }

