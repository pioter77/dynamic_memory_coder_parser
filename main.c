#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define ARR_SIZE 50
#define OUTPUT_WIDTH 20

int main(int argc,char *argv[])
{
    bool flag_sum=0;
    int buff_times1=1;
        int buff_times2=1;
            int buff_times3=1;
    int extract_first_arg(char *line);
    int extract_third_arg(char *line);
    int extract_second_arg(char *line);
    int save_arr_to_file(int *arr,char *filename,int width);
    int fill_dyn_arr(int **arr,int value,int count,int *size_times,bool sum_flag);
    int arg_first=0;
    int arg_second=0;
    int arg_third=0;

    //at the edn all those variables should be equal if not sth went wrong with processing
    int count_first=0;  //for keeping count of arguments of each type
    int count_second=0;
    int count_third=0;

    char *line_buff=0;
    int *arg1_buff=0;   //first arg array
    int *arg2_buff=0;   //second arg arr
    int *arg3_buff=0;   //third arg arr
    int lines_count=0;  //1 line less couse zero start vsalue

    line_buff=malloc(120*sizeof(char));
    arg1_buff=malloc(ARR_SIZE*buff_times1*sizeof(int));
    arg2_buff=malloc(ARR_SIZE*buff_times2*sizeof(int));
    arg3_buff=malloc(ARR_SIZE*buff_times3*sizeof(int));

    printf("\n\nno of run arguments inserted:\t%d\n\n",argc-1);

    for(int i=1;argv[i]!=NULL;i++)
    {
        printf("argument %d of opening is: %s\n",i,argv[i]);
    }

    FILE *fptr;
    fptr = fopen("test2.txt", "r");

    if(fptr==NULL)  printf("\nerror while opening file\n");
    if(fptr)
    {
        if(line_buff)
        {
           // fread(buff,1,length,fptr);  //wczytaj do przygotowanego bufora plik
          //fscanf(fptr,"%s",buff);   ///albo to albo printf cos nie tak
          while(fgets(line_buff,120,fptr))  //run down tle lines in file
          {
              //tu ma byc linia koazda kolejna kopiowana do arraya buffa
             // printf("%s",line_buff);
              ++lines_count;
              arg_first=extract_first_arg(line_buff);
              arg_second=extract_second_arg(line_buff);
              arg_third=extract_third_arg(line_buff);
              //////////////////////////////////////////////////////////////////////////////////////////
              if(arg_first>0)
              {
                  count_first=fill_dyn_arr(&arg1_buff,arg_first,count_first,&buff_times1,0);
              }
                if(arg_second>0)
              {
                  count_second=fill_dyn_arr(&arg2_buff,arg_second,count_second,&buff_times2,0);
              }
                if(arg_third>0)
              {

                  count_third=fill_dyn_arr(&arg3_buff,arg_third,count_third,&buff_times3,flag_sum);
                  flag_sum=1;
              }else{
                  flag_sum=0;
              }

          }

        }
        free(line_buff);
        printf("\nline buff cleared,lines count:\t%d",lines_count);
    }
    fclose(fptr);
    printf("\narg1 count:\t%d",count_first);
    printf("\narg2 count:\t%d",count_second);
    printf("\narg3 count:\t%d",count_third);
    save_arr_to_file(arg1_buff,"arr1.txt",OUTPUT_WIDTH);
    save_arr_to_file(arg2_buff,"arr2.txt",OUTPUT_WIDTH);
    save_arr_to_file(arg3_buff,"arr3.txt",OUTPUT_WIDTH);


    //tu funcja zapisu
   // fprintf(fpwrit,"tekst testowy1 linia, ");
    //

    free(arg1_buff);
    free(arg2_buff);
    free(arg3_buff);
  // if(buff)
 //  {
//printf("\nzawartosc txt pliku to:\n");
  //     printf("\n%s\n",buff);
  // }
 //  free(buff);
 /*
   printf("\nbuffer memory cleared\n");
    int times=0;
    printf("podaj liczbe intow do wypelanienia 4kami:\n");
    scanf("%d",&times);

    printf("\nwczytano:%d",times);
    int *t1=(int*)malloc(times*sizeof(int));

    for(int i=0;i<times;i++)
    {
        *(t1+i)=4;
        printf("\n\t%d element to wartosc:\t%d",i,*(t1+i));
    }
    printf("\n\n ========SPRAEDZNIE=============:\n");
    for(int i=0;i<times;i++)
    {

        printf("\n\t%d element to wartosc:\t%d",i,*(t1+i));
    }

    free(t1);
    printf("\ndigit to finish and close\n");
    scanf("%d",&times);
    */
    return 0;

}

int extract_first_arg(char *line)
{   //musi wykrysc sekwencje
    char templ[]="tone(tonePin,";
    char res_arr[4];//={[3]='\0'};
    int i=0;
    int pos=0;
    while(isspace((line[pos]))){
            pos++;  //ommit white spaces
    }
    while(templ[i]!='\0')
    {
        if(templ[i]==line[pos]) {
                pos++;
        }else return -1;
            i++;
    }
     while(isspace(line[pos]))  pos++;  //ommit white spaces
     i=0;
     while(isdigit(line[pos]))
     {
         res_arr[i]=line[pos];
         ++i;
         pos++;
         res_arr[i]='\0';
     }

return atoi(res_arr);   //if successfull
}
int extract_second_arg(char *line)
{
        char templ[]="tone(tonePin,";
    char res_arr[5];//={[4]='\0'};
    int i=0;
    int pos=0;
    while(isspace((line[pos]))){
            pos++;  //ommit white spaces
    }
    while(templ[i]!='\0')
    {
        if(templ[i]==line[pos]) {
                pos++;
        }else return -1;
            i++;
    }
     while(isspace(line[pos]))  pos++;  //ommit white spaces
     i=0;
     while(isdigit(line[pos]))
     {
         pos++;
     }
     if(line[pos]==',') pos++;
     while(isspace(line[pos])) pos++;
     i=0;
     while(isdigit(line[pos]))
     {
        res_arr[i]=line[pos];
        pos++;
        ++i;
        res_arr[i]='\0';
     }

return atoi(res_arr);   //if successfull
return 0;
}

int extract_third_arg(char *line)
{
    char templ[]="delay(";
    char res_arr[5];//={[4]='\0'};
    int i=0;
    int pos=0;
    while(isspace((line[pos]))){
            pos++;  //ommit white spaces
    }
    while(templ[i]!='\0')
    {
        if(templ[i]==line[pos]) {
                pos++;
        }else return -1;
            i++;
    }
     while(isspace(line[pos]))  pos++;  //ommit white spaces
     i=0;
     while(isdigit(line[pos]))
     {
         res_arr[i]=line[pos];
         ++i;
         res_arr[i]='\0';
         pos++;
     }

return atoi(res_arr);   //if successfull
}

int save_arr_to_file(int *arr,char *filename,int width)
{
     FILE *fpwrit=fopen(filename,"w");
    int i=0;
    if(fpwrit)
    {
         while(arr[i]!='\0')
        {
            if((i+1)%width!=0){
                fprintf(fpwrit,"%d,",arr[i]);
            }else{
                fprintf(fpwrit,"%d,\n",arr[i]);
            }
            i++;
        }
       fclose(fpwrit);
       return 0;
    }else return -1; //could not open the file
}

int fill_dyn_arr(int **arr,int value,int count,int *size_times,bool sum_flag)
{
int *tmp=0;
                    if(!sum_flag){
                       (*arr)[count]=value;
                         ++count;
                    }else{

                         (*arr)[count-1]+=value;
                    }

                         //przy realokowanieu pamieci po przekroczeniu liczby startowej size macierzy sie dzija bledy
                if(count>((ARR_SIZE*(*size_times))-1)){
                        ++(*size_times);    //w tym if coœ nie tak jest
                      //  printf("\nsize times:%d",*size_times);
                   tmp=realloc(*arr,ARR_SIZE*(*size_times)*sizeof(int));
                   if(tmp==NULL)
                   {
                       (*arr)[count-1]='\0';
                       free(*arr);
                       return 0;
                   }else{
                       (*arr)=tmp; //tu moze btc xle
                   }
                  //if sprawdz czy jest null
                  //free(*arr);
                //  (*arr)=tmp;
                    //free(arr);
                   //arr=tmp;
                }
                     (*arr)[count]='\0';
                //printf("\nline:%d\tval:\t%d",count,value);
                 return count;

}
