#include<stdio.h>

#include<SDL.h>

#include<math.h>

int SCREEN_WIDTH = 640;

int SCREEN_HEIGHT = 640;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

bool GAME = false;

int rad1 = 40;

int cx1 = -rad1;

int cy1 = SCREEN_HEIGHT / 2;

int rad2 = 20;

int cx2 = SCREEN_WIDTH / 2;

int cy2 = rad2;

bool createwindow()
{
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0)
    {
        printf("failed!");
        return false;
    }

    window = SDL_CreateWindow("ORNY_NABILA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!window)
    {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        return false;
    }

    return true;
}

void CreateCircle(SDL_Renderer* renderer, int cx1, int cy1, int rad1)
{
    for (int x = -rad1; x <= rad1; x++)
    {
        for (int y = -rad1; y <= rad1; y++)
        {
            if (x * x + y * y <= rad1 * rad1)
            {
                SDL_RenderDrawPoint(renderer, cx1 + x, cy1 + y);
            }
        }
    }
}

void processcontrol()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)//to move circle pressing keys
        {
            if (SDLK_RIGHT == event.key.keysym.sym)
            {

                cx2 += 5;
            }

            else if (SDLK_LEFT == event.key.keysym.sym)
            {
                cx2 -= 5;
            }

            else if (SDLK_UP == event.key.keysym.sym)
            {
                cy2 -= 5;
            }
            else if (SDLK_DOWN == event.key.keysym.sym)
            {
                cy2 += 5;
            }
        }

        else if (event.type == SDL_QUIT)
        {
            GAME = false;
        }
    }
}

void update()
{
    cx1 += 2;

    if (cx1 - rad1 >= SCREEN_WIDTH)

        cx1 = -rad1;

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 40, 50, 100);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
void render()
{
    CreateCircle(renderer, cx1, cy1, rad1);

    SDL_RenderPresent(renderer);

    CreateCircle(renderer, cx2, cy2, rad2);

    SDL_RenderPresent(renderer);
}
void collision()
{

    int displacement = sqrt((cx1 - cx2) * (cx1 - cx2) + (cy1 - cy2) * (cy1 - cy2));

    if (displacement <= rad1 + rad2)
    {
        SDL_Rect r;
        r.x = 0;

        r.y = 0;

        r.w = SCREEN_WIDTH;

        r.h = SCREEN_HEIGHT;

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 100, 50, 255);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 150, 25, 255);

        SDL_RenderDrawRect(renderer, &r);

        SDL_RenderPresent(renderer);
    }
}

void destroyWindow()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

int main(int argc, char* argv[])
{
    GAME = createwindow();

    while (GAME != false)
    {
        processcontrol();

        update();

        render();

        collision();
    }

    destroyWindow();

    return 0;
}