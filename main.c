#include <stdio.h>

//VARIABLE DECLARATIONS
FILE *laketemps;
FILE *laketemps2018;
double sum[6] = {0, 0, 0, 0, 0, 0};
double sum2018[6] = {0, 0, 0, 0, 0, 0};
double avgtemp[6] = {0, 0, 0, 0, 0, 0};
double avgtemp2018[6] = {0, 0, 0, 0, 0, 0};
double totalavgtemp = 0, totalavgtemp2018=0;
//maxtemps-> row 0 for temp, row 1 for the lake it is, row 2 for the day it is.
double maxwarmtemp[3][1], maxcoldtemp[3][1];
int warmtoswim[6] = { 0,0,0,0,0,0 }, coldtoswim[6] = { 0,0,0,0,0,0 };
double warmestday[2][6], coldestday[2][6]= { {0,0,0,0,0,0}, { 10000, 10000, 10000, 10000, 10000, 10000}};
int initialspot[] = { 0,1,2,3,4,5 };
char* initials[] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Claire"};
double data[8][365], data2018[8][365];

void getDate(int days) {
    int month, day;
    (1 <= days && days <= 31) ? month = 1, day = days : 1;
    (32 <= days && days <= 59) ? month = 2, day = days - 31 : 1;
    (60 <= days && days <= 90) ? month = 3, day = days - 59 : 1;
    (91 <= days && days <= 120) ? month = 4, day = days - 90 : 1;
    (121 <= days && days <= 151) ? month = 5, day = days - 120 : 1;
    (152 <= days && days <= 181) ? month = 6, day = days - 151 : 1;
    (182 <= days && days <= 212) ? month = 7, day = days - 181 : 1;
    (213 <= days && days <= 243) ? month = 8, day = days - 212 : 1;
    (244 <= days && days <= 273) ? month = 9, day = days - 243 : 1;
    (274 <= days && days <= 304) ? month = 10, day = days - 273 : 1;
    (301 <= days && days <= 334) ? month = 11, day = days - 304 : 1;
    (335 <= days && days <= 365) ? month = 12, day = days - 334 : 1;
    printf("%d/%d/2019\n", day, month); //the date can be changed to 2018 as well
}

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
    laketemps2018 = fopen("C:\\Users\\erioh\\CLionProjects\\WeatherProject\\glsea-temps2018_1024.txt", "r");

    //if the file doesnt exist or isnt in the right place, exit program
    if (laketemps == NULL || laketemps2018 == NULL) {
        printf("Cannot open file, does it exist?\n");
        return -1;
    }

    for (int i = 0; i < 365; i++) {
        //collect data from the file
        for (int j = 0; j < 8; j++) {
            fscanf(laketemps, "%lf", &data[j][i]);
            fscanf(laketemps2018, "%lf", &data2018[j][i]);
        }
        //printf("%lf \n", data[1][i]);

        //calculate sum
        for (int j = 0; j < 6; j++) {
            sum[j] += data[j + 2][i];
            sum2018[j] += data2018[j+2][i];
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
    printf("Average Lake Temperatures\n");
    for (int i = 0; i < 6; i++) {
        avgtemp2018[i] = sum2018[i] / 365;
        avgtemp[i] = sum[i] / 365;
        totalavgtemp += avgtemp[i];
        totalavgtemp2018 += avgtemp2018[i];
        printf("%lf  |", avgtemp[i]);
    }
    double maxavg=avgtemp[0], minavg=avgtemp[0];
    for(int i=0;i<6;i++){
        if (avgtemp[i] > maxavg) {
            maxavg = avgtemp[i];
        }
        if (avgtemp[i] < minavg) {
            minavg = avgtemp[i];
        }
    }
    totalavgtemp = totalavgtemp / 6;
    totalavgtemp2018 = totalavgtemp2018 / 6;
    maxwarmtemp[0][0] = warmestday[1][0];
    maxcoldtemp[0][0] =  coldestday[1][0];
    //Find the warmest lake, and see which are above/below avg temp
    printf(" The average temperature of all lakes is %.2lf in 2019, and %2.lf in 2018\n\n", totalavgtemp, totalavgtemp2018);
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
        printf("Warmest temperature for lake %s: %.2lf on ", initials[i], warmestday[1][i]); getDate(warmestday[0][i]+1);
        printf("Coldest temperature for lake %s: %.2lf on ", initials[i], coldestday[1][i]); getDate(coldestday[0][i]+1);

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
    printf("The warmest overall temperature is %.2lf at lake %s on ",maxwarmtemp[0][0], initials[initial1]); getDate(maxwarmtemp[2][0]+1);
    printf("The coldest overall temperature is %.2lf on multiple days in multiple lakes \n",maxcoldtemp[0][0]);

    double summersum[6] = {0,0,0,0,0,0};
    double summeravg[6] = {0,0,0,0,0,0};
    for(int i=171; i<265;i++){
        for (int j = 0; j < 6; j++) {
            summersum[j] += data[j + 2][i];
            }
        }
    for(int i=0;i<6;i++){
        summeravg[i] = summersum[i]/94;
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
    printf("\n\n");
    printf("Average Temperatures for each lake in 2018 vs 2019\n");
    for(int i=0;i<6;i++){
        printf("Lake %s : %.2lf | %.2lf \n", initials[i], avgtemp2018[i], avgtemp[i]);
    }
    return 0;
}
