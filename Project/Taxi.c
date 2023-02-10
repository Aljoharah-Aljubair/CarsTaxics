#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Taxi {
  int id;
  char driver[20];
  char category[20];
  char plate[7];
  char color[20];
  float rate;
  float minCharge;
  char state;
  struct Taxi *next;
}*list;

void addTripCar() {
  FILE *fp = fopen("Taxies.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    exit(1);
  }
  int id;
  char driver[20] , category[20] , plate[7] , color[20];
  float rate , minCharge;
  struct Taxi *temp , *currnt; 

 char line[100];
 fgets(line, 100, fp);
 while (fscanf(fp,"%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%f\t%f\n", &id, driver, category, plate, color, &rate, &minCharge) != EOF) {   
        temp = (struct Taxi*)malloc(sizeof(struct Taxi));
        temp->id = id;
        strcpy(temp->driver, driver);
        strcpy(temp->category, category);
        strcpy(temp->plate, plate);
        strcpy(temp->color, color);
        temp->rate = rate;
        temp->minCharge = minCharge;
        temp->state = 'A';
        temp->next = NULL;
        if(list==NULL){
            list=temp;
            currnt=list;
        }
        else {
            currnt->next=temp;
            currnt=temp;
        }
    }
    fclose(fp);
}




void setTripCar(char* category, float* rate) { // Function 2
     if( list == NULL){
        printf("Empty list\n"); 
        return; 
    }

    struct Taxi *temp = list;
    while (temp != NULL) {
        if ( (strcmp(temp->category, category) == 0) && (temp->rate == *rate) && (temp->state == 'A'))
            temp->state = 'R';
        temp = temp->next;
    }
}


void writeCarsInRide (char* fileName){ //Function 3
     if( list == NULL){
        printf("Empty list\n"); 
        return; 
    }
    
    FILE *fp = fopen(fileName,"a");
    if(fp==NULL){
        perror("File could not be opened");
        return;    
    }

    fprintf(fp,"\n------------------------------------\nThe Cars in Ride:\n");
    fprintf(fp,"id\tdriver\tcategory\tplate\trate\tstate\n");
    struct Taxi *temp = list;
    while (temp != NULL) {
        if ( temp->state == 'R'){
            fprintf(fp,"%d\t%s\t%s\t%s\t%.2f\t%c\n",temp->id,temp->driver,temp->category,temp->plate,temp->rate,temp->state );
        }  
        temp = temp->next;
    }
    fclose(fp);
}


void printList(){
    if( list == NULL){
        printf("Empty list\n"); 
        return; 
    }

    struct Taxi *temp; 
    temp = list; 
    while(temp!=NULL){
        printf( "%d\t%s\t%s\t%s\t%.1f\t%.2f\t%c\n", temp->id , temp->driver , temp->category , temp->plate , temp->rate , temp->minCharge , temp->state );                              
        temp = temp->next ; 
    }
}
int main(){

addTripCar(); 
printf("The Available Cars.\n");
printList();
char *s1 = "Business" ; float f1 = 4.5 ; 
char *s2= "Family" ; float f2 = 5.0 ; 
char *s3= "Family" ; float f3 = 4.0 ;
char *s4= "standard" ; float f4 = 3.4 ; 
char *s5= "standard" ; float f5 = 5.0 ;

setTripCar( s1 , &f1 ); 
setTripCar( s2 , &f2 ); 
setTripCar( s3 , &f3 ); 
setTripCar( s4 , &f4 ); 
setTripCar( s5 , &f5 ); 

printf("\n----------------------------------------------------\n");
printf("the Cars in Ride :\n"); 
printList();

char *fileName = "Taxies.txt" ; 
writeCarsInRide(fileName); 

return 0; 
}