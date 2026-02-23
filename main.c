#include<SDL2/SDL.h>

#define WIDTH 1200
#define HEIGHT 400

int main(int argc  , char** args){
  SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT, 0);

  SDL_Delay(3000);

  return 0;
}