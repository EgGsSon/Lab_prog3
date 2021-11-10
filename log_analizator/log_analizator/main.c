#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    FILE *file = fopen("/Users/dastardmoron/Documents/Программирование/NASA_access_log_Jul95","r");
    FILE *fileout = fopen("/Users/dastardmoron/product_folder/test.txt","w");
    
    int amount_errors = 0;
    int amount_date = 1;
    int date = 0;
    int index = 11;
    int n;
    int k;
    int max = 0;
    int time;
    int array[2000000];
    
    char request[400];
    char c;
    
    printf("Enter time: ");
    scanf("%d", &time);
    printf("Wait...\n");
    
    while(feof(file) == 0) {
        
        char string[400] = { 0 };
        fscanf(file, "%s", string);
        if(string[0] == '[') {
            n = 60 * 60;
            date = ((string[1] - '0') * 10 + (string[2] - '0') - 1) * 24 * n;
            k = 13;
            while(string[k] != '\0') {
                date += ((string[k] - '0') * 10 + (string[k + 1] - '0')) * n;
                n = n / 60;
                k += 3;
            }
            array[index] = date;
            index++;
        }
        
        if(string[0] == '"') {
            amount_date++;
            n = 0;
            while(string[n] != '\0')
                n++;
            while((c = fgetc(file) ) != '"') {
                string[n] = c;
                n++;
            }
            string[n] = c;
            string[n + 1] = '\0';
            strcpy(request, string);
            fscanf(file, "%s", string);
            if(string[0] == '5') {
                fprintf(fileout, "%s\n", request);
                amount_errors++;
            }
            strcpy(request, "");
        }
    }
    
    int i = 0;
    while(i < index) {
        amount_date = 1;
        if(array[i] != array[i - 1] || i == 0) {
            for(int v = i + 1; (array[v] - array[i] < time) && (v < index); v++) {
                amount_date++;
            }
        }
        
        if(amount_date > max)
            max = amount_date;
        i++;
    }
    
    printf("Amount of errors is %d\n", amount_errors);
    printf("Max is %d\n",max);
    
    fclose(fileout);
    fclose(file);
    return 0;
}
