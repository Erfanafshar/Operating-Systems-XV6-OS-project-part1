#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

// concat two string 
void concatt(char* str1,char* str2,char* res){
    int i = 0;
    int j = 0;
    for(i = 0;i < 100;i++){
        if(str1[i] == '\0')
            break;
        res[i] = str1[i];
    }
    for(i,j;i < 100;i++,j++){
        if(str2[j] == '\0')
            break;
        res[i] = str2[j];
    }
    res[i] = '\0';
}

// convert integer to corresponding string
void convert(int number, char* string){
    sprintf(string,"%d",number);
}

// calculate sum of even digits 
int calculateSum(int number){
    int digit = 0;
    int sum = 0;
    int i = 0;
    for(i; i < 100;i++){
        digit = number % 10;
        if((digit % 2) == 0){
            sum += digit;
        }
        number = number / 10;
    }
    return sum;
}

int main() {
    int input;
    int inputInt;
    int result;
    char output1 [200];
    char output2 [300];
    char outputString [300];
    char str1 [100];
    char str2 [100] = " The sum of even digits in the input number:";
    char str3 [100];
    int ptoc[2];
    int ctop[2];
    pid_t pid;
    
    // create two pipes for communication between parent and child 
    if(pipe(ptoc)<0) // parent to child
        exit(1);
    if(pipe(ctop)<0) // child to parent
        exit(1);
    
    // create parent and child 
    pid = fork();
    
    if(pid < 0) 
    // failed to create child 
        exit(1);
    else {
    	if(pid > 0) { 
    	    // parent 
    	    scanf("%d",&input); 
    	    close(ptoc[0]);// close ptoc reader 
    	    write(ptoc[1],&input,sizeof(input));// write to ptoc pipe 
    	    close(ptoc[1]);// close ptoc writer 
    	    wait(NULL);// wait for child to exit
    	    close(ctop[1]);// close ctop writer 
    	    read(ctop[0],outputString,sizeof(output2));// read from ctop pipe
    	    close(ctop[0]);// close ctop reader 
    	    printf("%s \n",outputString);
    	}
    	else { 
    	    // child
    	    close(ptoc[1]);// close ptoc writer 
    	    read(ptoc[0],&inputInt,sizeof(input));// read from ptoc pipe
    	    close(ptoc[0]);// close ptoc reader 
    	    convert(inputInt,str1);
    	    concatt(str1,str2,output1);
    	    result = calculateSum(inputInt);
    	    convert(result,str3);
    	    concatt(output1,str3,output2);
    	    close(ctop[0]);// close ctop reader 
    	    write(ctop[1],output2,sizeof(output2));// write to ctop pipe 
    	    close(ctop[1]);// close ctop writer
    	    exit(0);
    	}
    }
	return 0;
}
