// A simple program, loosely remaking 'The Sound of Sorting - "Audibilization" and Visualization of Sorting Algorithms' by Timo Bingmann, with Raylib.
// handmade to help me study and vizualize sorting algorithms, a major topic in the third semester of my graduation (ADS) at Cesar School.

// by Miglito

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>


#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"


void swap(int a, int b, int *arr) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}


void bubble_sort(int *arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(j,j+1, arr);
            }
        }
    }
}

void sort_step(int *arr, int size, int *i) {
    if (arr[*i] > arr[*i + 1])
    {
        swap(*i, *i + 1, arr);
    }

    *i = (*i + 1) % (size-1);
}

int main(int argc, char *argv[])
{

    float speed = 1000;
    float frame_acc = 0;

    int ARRAY_SIZE = 16;
    if (argc > 1) sscanf(argv[1], "%d", &ARRAY_SIZE);
    int my_array[ARRAY_SIZE];

    int idx = 0;
    bool array_is_sorted = false;
    
    int iteration_count = 0;
    int comparassion_count = 0;
    int array_access_count = 0;
    
    int MAX = 100;
    for (int i = 0; i < ARRAY_SIZE; i++) my_array[i] = GetRandomValue(1, MAX);
    
    bool running = false;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(600,600, "sortviz");
    SetTargetFPS(60);
    GuiLoadStyle("./assets/style_advance.rgs");
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R))
        {
                idx = 0;
                iteration_count = 0;
                comparassion_count = 0;
                array_access_count = 0;
                array_is_sorted = false;

                for (int i = 0; i < ARRAY_SIZE; i++) my_array[i] = GetRandomValue(1, MAX);
                
                running = false;
        }

        if (IsKeyPressed(KEY_X))
        {
            running = !running;
        }
        

        if (running)
        {
            while (frame_acc > 1)
            {
                frame_acc = frame_acc - 1;

                { // check if sorted already
                    for (int i = 0; i < ARRAY_SIZE - 1; i++)
                    {
                        if (my_array[i] > my_array[i + 1])
                        {
                            array_is_sorted = false;
                            break;
                        }
                        array_is_sorted = true;
                    }
                }
        
        
                if (!array_is_sorted)
                {
                    // perform a sorting step in the selected algo (bubble for now)
                    sort_step(my_array, ARRAY_SIZE, &idx);
        
                    iteration_count    += 1;
                    comparassion_count += 1;
                    array_access_count += 5;
                }
            }
            frame_acc += speed * GetFrameTime();
        }


        BeginDrawing();

        ClearBackground(BLACK);


        { // draw array
            float step_x = (float) GetScreenWidth() / ARRAY_SIZE;
            float screen_height = GetScreenHeight();

            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                float height = (screen_height / MAX) * my_array[i];
                Color base_color = ColorFromHSV(((180 / MAX) * my_array[i]) + 180, 1, 1);
                Color col = array_is_sorted ? base_color : ((i == idx) ? BLUE : base_color);
                // DrawRectangle(step_x * i, screen_height- height, step_x, screen_height, col);
                DrawRectanglePro((Rectangle){step_x * i, screen_height - height, step_x, screen_height}, (Vector2){0,0}, 0.0, col);
            }
        }



        { // draw interface

            float screen_height = GetScreenHeight();
            float screen_width = GetScreenWidth();

            DrawText(TextFormat("Iterations: %d ", iteration_count), 20, 20, 20, WHITE);
            DrawText(TextFormat("Comparassions: %d ", comparassion_count), 20, 40, 20, WHITE);
            DrawText(TextFormat("Array Access: %d ", array_access_count), 20, 60, 20, WHITE);
            DrawText(TextFormat("%s", array_is_sorted ? "Sorted" : "Unsorted"), 20, 80, 20, WHITE);
            
            if (GuiButton((Rectangle) {.x = 20, .y = screen_height - 70, .width = 100, .height = 30}, running ? "Stop" : "Run"))
            {
                running = !running;
            }
            
            
            GuiSlider((Rectangle){20, screen_height - 30, screen_width - 40, 10}, "", "", &speed, 1, 24000);
        }

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}

