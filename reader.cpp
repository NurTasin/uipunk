#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>






int main(int argc,char** argv)
{
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	FILE* bin=fopen("mahib.bin","r");
	int winHeight,winWidth;
	char r,g,b,a,pr=0,pg=0,pb=0;
	{
		char w0,w1,h0,h1;
		fscanf(bin,"%c%c%c%c",&w0,&w1,&h0,&h1);
		winWidth=int(int(w0<<8)+w1);
		winHeight=int(int(h0<<8)+h1);
	}
	printf("Width: %d px and Height: %d px",winWidth,winHeight);
	SDL_CreateWindowAndRenderer(winWidth,winHeight,0,&window,&renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	int x,y;
	long long pixCount=0;
	for(y=0;y<winWidth;y++)
	{
		for(x=0;x<winHeight;x++)
		{
			fscanf(bin,"%c%c%c%c",&r,&g,&b,&a);
			if(!(pr==r && pg==g && pb==b))
			{
				SDL_SetRenderDrawColor(renderer,r,g,b,a);
				pr=r;
				pg=g;
				pb=b;
			}
			SDL_RenderDrawPoint(renderer,x,y);
			pixCount++;
		}
	}
	printf("Total Pixel Count: %ld",pixCount);
	fclose(bin);
	SDL_RenderPresent(renderer);
	while(1)
	{
		if(SDL_PollEvent(&event) && event.type==SDL_QUIT)
		{
			break;
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}