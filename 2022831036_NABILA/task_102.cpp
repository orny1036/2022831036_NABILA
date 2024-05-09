#include<stdio.h>

#include<SDL.h>

#include<math.h>

int SCREEN_WIDTH = 800;

int SCREEN_HEIGHT = 800;

SDL_Window* WIN = NULL;

SDL_Renderer* REN = NULL;

bool CIRCLE_MOVING = false;

int rd = 40;

int center_x = SCREEN_WIDTH / 2;

int center_y = SCREEN_HEIGHT / 2;

bool createwindow()
{
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != NULL)
    {
        printf("error!");
        return false;
    }

    WIN = SDL_CreateWindow("ORNY_NABILA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (WIN == 0)
    {
        return false;
    }

    REN = SDL_CreateRenderer(WIN, -1, SDL_RENDERER_ACCELERATED);

    if (REN == 0) {

        return false;
    }
    return true;
}

void CreateCircle(SDL_Renderer* renderer, int c_x, int c_y, int rad)
{
    for (int x = -rad; x <= rad; x++)
    {
        for (int y = -rad; y <= rad; y++)
        {
            if (x * x + y * y <= rad * rad)
            {
                SDL_RenderDrawPoint(renderer, c_x + x, c_y + y);
            }
        }
    }
}

void run()
{
    rd += 10;

    if (rd >= 420)
    {
        rd = 40;
    }

    SDL_RenderClear(REN);

    SDL_SetRenderDrawColor(REN, 0, 200, 100, 0);

    SDL_RenderClear(REN);

    SDL_SetRenderDrawColor(REN, 0, 0, 0, 0);
}

int main(int argc, char* argv[])
{
    SDL_SetRenderDrawColor(REN, 0, 200, 0, 200);

    SDL_RenderClear(REN);

    SDL_Color color = { 0,0,0,0 };

    SDL_SetRenderDrawColor(REN, color.r, color.g, color.b, color.a);

    CIRCLE_MOVING = createwindow();

    while (CIRCLE_MOVING != false)
    {
        rd += 10;

        if (rd >= 420)
        {
            rd = 40;
        }

        SDL_RenderClear(REN);

        SDL_SetRenderDrawColor(REN, 0, 200, 100, 0);

        SDL_RenderClear(REN);

        SDL_SetRenderDrawColor(REN, 0, 0, 0, 0);

        CreateCircle(REN, center_x, center_y, rd);

        SDL_RenderPresent(REN);
    }

    SDL_DestroyRenderer(REN);
    SDL_DestroyWindow(WIN);
    SDL_Quit();

    return 0;
}