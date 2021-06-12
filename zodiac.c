#include <stdio.h>

struct date{
    int year;
    int month;
    int day;
    int zodiac;
};
typedef struct date date;

struct zodiac{
    int marker[60];
    int byteSize[60];
};
typedef struct zodia zodiac;

void knowSign(struct date *d);
void printSign(struct date *d);
int charCount(FILE *const fp);

int main(){

    FILE *fp = fopen("data.for", "r");
    FILE* fp2 = fopen("data.in","a+");

    if(!fp || !fp2){
        printf("Oh no, an error occured!\n");
        return -1;
    }

    struct date d = {0,0,0,0};
    
    //reads input from the user
    do{
        scanf("%i", &d.year);
    }while(d.year < 1970 || d.year > 2038);
    
    do{
        scanf("%i", &d.month);
    }while(d.month < 1 || d.month > 12);

    do{
        scanf("%i", &d.day);
    }while(d.day < 1 || d.day > 31);

    //counts the size of each line
    int arrSize = 60;
    int byteSize[arrSize];

    for(int i = 0; i < arrSize; i++){
        byteSize[i] = charCount(fp);
    }

    //initializes marker for each line corresponding to a horoscope's fortune
    int zodiacMarker[arrSize];

    int i = 0, j, locationMark;
    while(i < arrSize){
        for(int j = 0; j < 12; j++, i++){
            zodiacMarker[i] = j+1;
        }
    }

    knowSign(&d);
    
    //gets position in the array
    struct date d2 = {0,0,0,0};
    int count = 0; 

    rewind(fp2);
    
    //places input in the file
    while(!feof(fp2)){
        fscanf(fp2, "%d-%d-%d",&d2.year,&d2.month,&d2.day);
        knowSign(&d2);
        if(d.zodiac == d2.zodiac){
            count++;
        }
    }

    if(count > 0){
        count--;
    }

    int ok = 0;
    i = 0;
    j = d.zodiac;
    
    //marks the position of the fortunes that have already been read
    while(count > 0 && i < arrSize || ok != 1){
        if(j == zodiacMarker[i]){
            zodiacMarker[i] = -1;
            if(count > 0){
                count--;
            }else if(count == 0){
                ok = 1;
            }
        }
        i++;
    }
    
    locationMark = i;

    if(locationMark > 60){
        printf("\nYou are out of fortunes.\n");
    }else if(locationMark <= 60){

        locationMark = i - 1;

        //get byteSize location
        int finalSize = 0;
        for(int i = 0; i < locationMark; i++){
            finalSize += byteSize[i];
        }

        //gets to that location in the file
        fseek(fp, finalSize + locationMark, SEEK_SET);
        char arr[byteSize[locationMark+1]];
        fgets(arr, byteSize[locationMark]+1, fp);
        printSign(&d);
        printf("%s", arr);

    }
    
    fprintf(fp2, "%04d-%02d-%02d\n", d.year,d.month,d.day);

    fclose(fp);
    fclose(fp2);

    return 0;
}

void knowSign(struct date *d){

    if(((d->month == 3) && (d->day >= 21 && d->day <= 31)) || ((d->month == 4) && (d->day >= 1 && d->day <= 19))){
        d->zodiac = 3;
    }else if((d->month == 4) && (d->day >= 20 && d->day <= 31) || ((d->month == 5) && (d->day >= 1 && d->day <= 20))){
        d->zodiac = 4;
    }else if(((d->month == 5) && (d->day >= 21 && d->day <= 31)) || ((d->month == 6) && (d->day >= 1 && d->day <= 20))){
        d->zodiac = 5;
    }else if(((d->month == 6) && (d->day >= 21 && d->day <= 31)) || ((d->month == 7) && (d->day >= 1 && d->day <= 22))){
        d->zodiac = 6;
    }else if(((d->month == 7) && (d->day >= 23 && d->day <= 31)) || ((d->month == 8) && (d->day >= 1 && d->day <= 22))){
        d->zodiac = 7;
    }else if(((d->month == 8) && (d->day >= 23 && d->day <= 31)) || ((d->month == 9) && (d->day >= 1 && d->day <= 22))){
        d->zodiac = 8;
    }else if(((d->month == 9) && (d->day >= 23 && d->day <= 31)) || ((d->month == 10) && (d->day >= 1 && d->day <= 22))){
        d->zodiac = 9;
    }else if(((d->month == 10) && (d->day >= 23 && d->day <= 31)) || ((d->month == 11) && (d->day >= 1 && d->day <= 21))){
        d->zodiac = 10;
    }else if(((d->month == 11) && (d->day >= 22 && d->day <= 31)) || ((d->month == 12) && (d->day >= 1 && d->day <= 21))){
        d->zodiac = 11;
    }else if(((d->month == 12) && (d->day >= 22 && d->day <= 31)) || ((d->month == 1) && (d->day >= 1 && d->day <= 19))){
        d->zodiac = 12;
    }else if(((d->month == 1) && (d->day >= 20 && d->day <= 31)) || ((d->month == 2) && (d->day >= 1 && d->day <= 18))){
        d->zodiac = 1;
    }else if(((d->month == 2) && (d->day >= 19 && d->day <= 31)) || ((d->month == 3) && (d->day >= 1 && d->day <= 20))){
        d->zodiac = 2;
    }

}

void printSign(struct date *d){

    if(d->zodiac == 1){
        printf("Aquarius: ");
    }else if(d->zodiac == 2){
        printf("Pisces: ");
    }else if(d->zodiac == 3){
        printf("Aries: ");
    }else if(d->zodiac == 4){
        printf("Taurus: ");
    }else if(d->zodiac == 5){
        printf("Gemini: ");
    }else if(d->zodiac == 6){
        printf("Cancer: ");
    }else if(d->zodiac == 7){
        printf("Leo: ");
    }else if(d->zodiac == 8){
        printf("Virgo: ");
    }else if(d->zodiac == 9){
        printf("Libra: ");
    }else if(d->zodiac == 10){
        printf("Scorpio: ");
    }else if(d->zodiac == 11){
        printf("Saggitarius: ");
    }else if(d->zodiac == 12){
        printf("Capricorn: ");
    }

}

int charCount( FILE *const fp ){
    char c;
    int count = 0;

    for( ;; ){
        c = fgetc(fp);
        if( c == EOF || c == '\n' )
            break;
        ++count;
    }

    return sizeof(char)*count;
}


