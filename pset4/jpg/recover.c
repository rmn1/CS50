/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    char sig[] = {0xFF, 0xD8, 0xFF, 0xE0, 0xE1};
    
    // Open raw file for reading
    FILE* rawfile = fopen("card.raw", "r");
    
    if (rawfile == NULL)
        return 1;
    
    int counter = 0;
    char jpgfile[8];
    char buffer[0x200];
    
    FILE* jpeg = NULL;

    // Keep reading from rawfile while there are 512-byte blocks left
    while (fread(&buffer, sizeof(buffer), 1, rawfile))
    {
        // Check whether first bytes indicate start of new jpeg
        if(buffer[0] == sig[0] && buffer[1] == sig[1] && buffer[2] == sig[2] && (buffer[3] == sig[3] || buffer[3] == sig[4]))
        {
            // Close previous jpeg file (if it exists, i.e., do not close before 1st jpeg)
            if (jpeg != NULL)
                fclose(jpeg);
           
            // Create new jpeg file, name it, and open it
            sprintf(jpgfile, "%03i.jpg", counter);
            jpeg = fopen(jpgfile, "w");
            
            counter++;
        }
        
        // Write jpeg signature bytes (already read) to jpeg file
        if (jpeg != NULL)
            fwrite(&buffer, sizeof(buffer), 1, jpeg);
    }
    
    // Close last jpeg file
    if (jpeg != NULL)
      fclose(jpeg);
        
    fclose(rawfile);
}
