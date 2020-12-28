





#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

// Loads as RGBA... even if file is only RGB
// Feel free to adjust this if you so please, by changing the 4 to a 0.
bool load_image(std::vector<unsigned char>& image, const char* filename, int& x, int&y)
{
    int n;
    unsigned char* data = stbi_load(filename, &x, &y, &n, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

int main(int argc, char** argv)
{
		if(argc<2){
			printf("Error 0x11011\n");
			exit(1);
		}
    
    FILE *outfile=fopen(argv[2],"w+");
    
    if(outfile==NULL){
    	printf("Error creating the outputfile...");
    	exit(1);
    }
    
    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image,argv[1], width, height);
    if (!success)
    {
        printf("Error loading image\n");
        exit(1);
    }
    //crearing a scope so that temporary variables could be destroyed...
    {
   	 short Width=(short)width;
 	   short Height=(short)height;
 	   //embedding the Width and Height into the output file
	    fprintf(outfile,"%c%c%c%c",char(Width>>8),char(short(Width<<8)>>8),char(Height>>8),char(short(Height<<8)>>8));
    }
    const size_t RGBA = 4;
    size_t index;
		for(int y=0;y<height;y++)
		{
			for(int x=0;x<width;x++)
			{
				index = RGBA * (y * width + x);
				fprintf(outfile,"%c%c%c%c",image[index],image[index+1],image[index+2],image[index+3]);
			}
		}
		fclose(outfile);
    return 0;
}