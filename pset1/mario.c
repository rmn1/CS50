#include <stdio.h>
#include <cs50.h>

int main(void){
   
    // prompt user to enter height and verify response is non-negative number <= 23
    int height = 0;
    
    do {
        printf("Enter desired height of pyramid (2 > h > 23): ");
        height = GetInt();
        if (height == 0) return 0;
        
    } while (height > 23 || height < 1); 
    
    // create loop to run through lines of the pyramid
    for (int i = 0; i < height; i++) {
        
        // first nested loop generates spaces to right-align the pyramid
        for (int j = 0; j < height-i-1; j++) {
            printf(" ");
        }
        
        // second nested loop generates hashmarks for pyramid itself
        for (int k = 0; k < i+2; k++) {
            printf("#");
        }
        
        // new line so next row of pyramid starts on new line...
        printf("\n");
    }  
    return 0;
}
