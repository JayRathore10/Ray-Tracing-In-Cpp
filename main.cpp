#include<SDL2/SDL.h>
#include<cmath>

#define WIDTH 1200
#define HEIGHT 600
#define CIRCLE_RADIUS 40 
#define SHADOW_CIRCLE_RADIUS 140
#define RAY_NUMBERS 100
#define RAY_THICKNESS 3

#define COLOR_WHITE 0xffffff
#define COLOR_BLACK 0x000000

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

void FillRays(SDL_Surface* surface , Ray rays[RAY_NUMBERS] , Uint32 color , Circle circle){
  double radius_sqaured = pow(circle.radius , 2);

  for(int i =0 ; i< RAY_NUMBERS ; i++){
    Ray ray = rays[i];

    /**
     * We fill the windows with the ray if the ray hit the object ot it touch the end of the screen then we stop
     */

    bool end_of_screen = false;

    double x_draw = ray.x_start;
    double y_draw = ray.y_start;

    while(!end_of_screen){
      x_draw += cos(ray.angle);
      y_draw += sin(ray.angle);

      SDL_Rect ray_point = (SDL_Rect){(int)x_draw , (int)y_draw , RAY_THICKNESS , RAY_THICKNESS};

      SDL_FillRect(surface  , &ray_point ,  color);

      if(x_draw < 0 || x_draw > WIDTH){
        end_of_screen = true;
      }

      if(y_draw < 0 || y_draw > HEIGHT ){
        end_of_screen = true;
      }

      double distance_squared = pow(x_draw - circle.x  , 2) + pow(y_draw - circle.y , 2);

      if(distance_squared < radius_sqaured){
        break;
      }
    }
  }
}

int main(int argc  , char** args){
  SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT, 0);

  SDL_Surface* surface = SDL_GetWindowSurface(window);
  
  Circle circle = {200, 200 , CIRCLE_RADIUS};
  Circle shadow_circle = {550 , 300, SHADOW_CIRCLE_RADIUS};

  SDL_Rect earse_rect = (SDL_Rect){0 , 0 , WIDTH , HEIGHT};
  
  Ray rays[RAY_NUMBERS];
  generate_rays(circle , rays);
  
  SDL_Event event ;
  bool running = true;
  
  while(running){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running = false ;
        SDL_Delay(10);
      }

      if(event.type == SDL_MOUSEMOTION && event.motion.state != 0){
        circle.x = event.motion.x;
        circle.y = event.motion.y;
        generate_rays(circle , rays);
      }

      FillCircle(surface  , circle , COLOR_WHITE);
      SDL_FillRect(surface ,&earse_rect , COLOR_BLACK);
      FillCircle(surface , shadow_circle , COLOR_WHITE);
      FillRays(surface , rays , COLOR_WHITE ,shadow_circle);
      SDL_UpdateWindowSurface(window);
    }
  }
  
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}