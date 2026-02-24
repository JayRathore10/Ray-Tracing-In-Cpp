#include<SDL2/SDL.h>
#include<cmath>

#define WIDTH 1200
#define HEIGHT 600
#define CIRCLE_RADIUS 60 
#define SHADOW_CIRCLE_RADIUS 140
#define RAY_NUMBERS 100

#define COLOR_WHITE 0xffffff

typedef struct Circle{
  double x ;
  double y ;
  double radius;
} Circle;

typedef struct Ray{
  double x_start ;
  double y_start ;
  double angle ;
}Ray;

void FillCircle(SDL_Surface* surface , Circle circle , Uint32 color){

  double radius_squared = pow(circle.radius , 2);

  /**
   * We try to make a  Circle inside the rectangle 
   * where the rectangle start from the (x - r) and goes to (x + r) in x-axis and in y axis it start from the (y - r) and goes to (y + r) 
   * and then generate the pixel of the width and height 1 X 1 to fill the whole area 
   */

  for(double x = circle.x - circle.radius ; x <= circle.x + circle.radius ; x++){
    for(double y = circle.y - circle.radius ; y <= circle.y + circle.radius ; y++){ 
      double distance_squared = pow(x - circle.x , 2) + pow(y - circle.y  , 2);
      
      if(distance_squared < radius_squared){
        SDL_Rect pixel = (SDL_Rect) {int(x), int(y), 1 , 1};
        SDL_FillRect(surface , &pixel  , color);
      }
    }
  }

}

void generate_rays(Circle circle , Ray rays[RAY_NUMBERS]){
  for(int i = 0 ; i < RAY_NUMBERS ; i++){
    double angle = (double)i / RAY_NUMBERS * 2 * M_PI;
    Ray ray = {circle.x , circle.y  , angle};
    rays[i] = ray;
  }
}

int main(int argc  , char** args){
  SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT, 0);

  SDL_Surface* surface = SDL_GetWindowSurface(window);
  
  Circle circle = {100 , 100 , CIRCLE_RADIUS};
  Circle shadow_circle = {600 , 300, SHADOW_CIRCLE_RADIUS};
  
  Ray rays[RAY_NUMBERS];
  generate_rays(circle , rays);
  
  SDL_Event event ;
  int running = 1;
  
  while(running){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running = 0;
        SDL_Delay(10);
      }
      
      FillCircle(surface  , circle , COLOR_WHITE);
      FillCircle(surface , shadow_circle , COLOR_WHITE);
      SDL_UpdateWindowSurface(window);
    }
  }
  
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}