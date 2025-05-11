#include <vector>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include "raylib.h"

#define comptime static constexpr

comptime int GRID_LEN = 50;
comptime float CELL_WIDTH = 15.0f;

comptime int TOP_REGION_HEIGHT = 100;
comptime int WINDOW_PADDING = 20;

comptime Color COLOR_ON = PURPLE;
comptime Color COLOR_OFF = DARKPURPLE;
comptime Color COLOR_BORDER = BLACK;
comptime Color COLOR_BACKGROUND = LIGHTGRAY;

comptime int WINDOW_WIDTH = GRID_LEN * CELL_WIDTH + WINDOW_PADDING;
comptime int WINDOW_HEIGHT = GRID_LEN * CELL_WIDTH + WINDOW_PADDING + TOP_REGION_HEIGHT;

comptime int GRID_SIZE = GRID_LEN * GRID_LEN;

struct Grid
{
    std::vector<Rectangle> cells;
    std::vector<Color> colors;
    std::vector<uint32_t> neighbours;
    std::vector<bool> lives;
    uint64_t generation_count;

    Grid() : cells(GRID_SIZE), colors(GRID_SIZE, COLOR_OFF), neighbours(GRID_SIZE, 0), lives(GRID_SIZE, false), generation_count(0)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            cells[i].x = (i % GRID_LEN) * CELL_WIDTH + (WINDOW_WIDTH - GRID_LEN * CELL_WIDTH) * 0.5;
            cells[i].y = (i / GRID_LEN) * CELL_WIDTH + (WINDOW_HEIGHT - GRID_LEN * CELL_WIDTH + TOP_REGION_HEIGHT) * 0.5;

            cells[i].width = CELL_WIDTH;
            cells[i].height = CELL_WIDTH;
        }
    }

    void draw()
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            DrawRectangleRec(cells[i], colors[i]);
            DrawRectangleLines(cells[i].x, cells[i].y, cells[i].width, cells[i].width, COLOR_BORDER);
        }
    }

    void put_glider_on_idx(int idx)
    {
        turn_cell_off(idx);
        turn_cell_off(idx+1);
        turn_cell_off(idx+2);
        turn_cell_off(idx+GRID_LEN);
        turn_cell_off(idx+GRID_LEN+1);
        turn_cell_off(idx+GRID_LEN+2);
        turn_cell_off(idx+2*GRID_LEN);
        turn_cell_off(idx+2*GRID_LEN+1);
        turn_cell_off(idx+2*GRID_LEN+2);

        turn_cell_on(idx);
/*         turn_cell_on(idx+1); */
        turn_cell_on(idx+2);
/*         turn_cell_on(idx+GRID_LEN); */
        turn_cell_on(idx+GRID_LEN+1);
        turn_cell_on(idx+GRID_LEN+2);
/*         turn_cell_on(idx+2*GRID_LEN); */
        turn_cell_on(idx+2*GRID_LEN+1);
/*         turn_cell_on(idx+2*GRID_LEN+2); */
    }

    void otuzbir(int idx)
    {
        turn_cell_on(idx + 7);
        turn_cell_on(idx + 8);
        turn_cell_on(idx + 10);

        turn_cell_on(idx + 13);
        turn_cell_on(idx + 15);
        turn_cell_on(idx + 16);

        turn_cell_on(idx + GRID_LEN);
        turn_cell_on(idx + GRID_LEN + 1);
        turn_cell_on(idx + GRID_LEN + 6);
        turn_cell_on(idx + GRID_LEN + 9);

        turn_cell_on(idx + GRID_LEN + 14);
        turn_cell_on(idx + GRID_LEN + 17);
        turn_cell_on(idx + GRID_LEN + 22);
        turn_cell_on(idx + GRID_LEN + 23);


        turn_cell_on(idx + 2*GRID_LEN);
        turn_cell_on(idx + 2*GRID_LEN + 1);
        turn_cell_on(idx + 2*GRID_LEN + 7);
        turn_cell_on(idx + 2*GRID_LEN + 9);

        turn_cell_on(idx + 2*GRID_LEN + 14);
        turn_cell_on(idx + 2*GRID_LEN + 16);
        turn_cell_on(idx + 2*GRID_LEN + 22);
        turn_cell_on(idx + 2*GRID_LEN + 23);

        turn_cell_on(idx + 3*GRID_LEN + 8);
        turn_cell_on(idx + 3*GRID_LEN + 15);

        turn_cell_on(idx + 9*GRID_LEN + 8);
        turn_cell_on(idx + 9*GRID_LEN + 15);

        turn_cell_on(idx + 10*GRID_LEN);
        turn_cell_on(idx + 10*GRID_LEN + 1);
        turn_cell_on(idx + 10*GRID_LEN + 7);
        turn_cell_on(idx + 10*GRID_LEN + 9);

        turn_cell_on(idx + 10*GRID_LEN + 14);
        turn_cell_on(idx + 10*GRID_LEN + 16);
        turn_cell_on(idx + 10*GRID_LEN + 22);
        turn_cell_on(idx + 10*GRID_LEN + 23);

        turn_cell_on(idx + 11*GRID_LEN);
        turn_cell_on(idx + 11*GRID_LEN + 1);
        turn_cell_on(idx + 11*GRID_LEN + 6);
        turn_cell_on(idx + 11*GRID_LEN + 9);

        turn_cell_on(idx + 11*GRID_LEN + 14);
        turn_cell_on(idx + 11*GRID_LEN + 17);
        turn_cell_on(idx + 11*GRID_LEN + 22);
        turn_cell_on(idx + 11*GRID_LEN + 23);

        turn_cell_on(idx + 12*GRID_LEN + 7);
        turn_cell_on(idx + 12*GRID_LEN + 8);
        turn_cell_on(idx + 12*GRID_LEN + 10);

        turn_cell_on(idx + 12*GRID_LEN + 13);
        turn_cell_on(idx + 12*GRID_LEN + 15);
        turn_cell_on(idx + 12*GRID_LEN + 16);
    }
    void reset()
    {
        generation_count = 0;

        for (int i = 0; i < GRID_SIZE; ++i)
        {
            cells[i].x = (i % GRID_LEN) * CELL_WIDTH + (WINDOW_WIDTH - GRID_LEN * CELL_WIDTH) * 0.5;
            cells[i].y = (i / GRID_LEN) * CELL_WIDTH + (WINDOW_HEIGHT - GRID_LEN * CELL_WIDTH + TOP_REGION_HEIGHT) * 0.5;

            cells[i].width = CELL_WIDTH;
            cells[i].height = CELL_WIDTH;

            colors[i] = COLOR_OFF;
            lives[i] = false;
            neighbours[i] = 0;

        }
    }

    int get_idx(Vector2 mousepos)
    {
        bool mouse_within_grid_x = mousepos.x > cells[0].x && (mousepos.x < (cells[GRID_LEN - 1].x + CELL_WIDTH));
        bool mouse_within_grid_y = mousepos.y > cells[0].y && (mousepos.y < (cells[GRID_SIZE - GRID_LEN].y + CELL_WIDTH));

        if (mouse_within_grid_x && mouse_within_grid_y)
        {
            int col = (mousepos.x - cells[0].x) / CELL_WIDTH;
            int row = (mousepos.y - cells[0].y) / CELL_WIDTH;
            return (row * GRID_LEN + col);
        }
        return -1;
    }

    void turn_cell_on(int idx)
    {
        lives[idx] = true;
        colors[idx] = COLOR_ON;
    }

    void turn_cell_off(int idx)
    {
        lives[idx] = false;
        colors[idx] = COLOR_OFF;
    }

    void update_neighbours()
    {
        auto is_alive = [&](int idx)
        {
            if (idx < 0 || idx > GRID_SIZE - 1)
            {
                return false;
            }
            else
            {
                bool boing = lives[idx];
                return boing;
            }
        };

        for (int i=0; i<GRID_SIZE; ++i)
        {
            int neighbour_count = 0;

            if (is_alive(i-GRID_LEN-1))  {++neighbour_count;}
            if (is_alive(i-GRID_LEN))    {++neighbour_count;}
            if (is_alive(i-GRID_LEN+1))  {++neighbour_count;}
            if (is_alive(i-1))           {++neighbour_count;}
            if (is_alive(i+1))           {++neighbour_count;}
            if (is_alive(i+GRID_LEN-1))  {++neighbour_count;}
            if (is_alive(i+GRID_LEN))    {++neighbour_count;}
            if (is_alive(i+GRID_LEN+1))  {++neighbour_count;}

            neighbours[i] = neighbour_count;
        }
    }

    void update_neighbours_wraparound_360()
    {
        auto is_alive = [&](int idx)
        {
            if (idx < 0 || idx > GRID_SIZE - 1)
            {
                return false;
            }
            else
            {
                bool boing = lives[idx];
                return boing;
            }
        };

        enum position
        {
            inner = 0,
            top,
            bottom,
            left,
            right
        };

        for (int i=0; i<GRID_SIZE; ++i)
        {
            position pos;
            if (i % GRID_LEN == 0) {pos = left;}
            else if (i % GRID_LEN == (GRID_LEN-1)) {pos = right;}
            else if (i > 0 && i < GRID_LEN) {pos = top;}
            else if (i > GRID_SIZE - GRID_LEN &&  i < GRID_SIZE) {pos = bottom;}
            else {pos = inner;}

            int neighbour_count = 0;

            switch (pos)
            {
            case right:
            if (is_alive(i-GRID_LEN-1))           {++neighbour_count;}
            if (is_alive(i-GRID_LEN))             {++neighbour_count;}
            if (is_alive(i-GRID_LEN+1-GRID_LEN))  {++neighbour_count;}
            if (is_alive(i-1))                    {++neighbour_count;}
            if (is_alive(i+1-GRID_LEN))           {++neighbour_count;}
            if (is_alive(i+GRID_LEN-1))           {++neighbour_count;}
            if (is_alive(i+GRID_LEN))             {++neighbour_count;}
            if (is_alive(i+GRID_LEN+1-GRID_LEN))  {++neighbour_count;}
            break;

            case left:
            if (is_alive(i-GRID_LEN-1+GRID_LEN))  {++neighbour_count;}
            if (is_alive(i-GRID_LEN))             {++neighbour_count;}
            if (is_alive(i-GRID_LEN+1))           {++neighbour_count;}
            if (is_alive(i-1+GRID_LEN))           {++neighbour_count;}
            if (is_alive(i+1))                    {++neighbour_count;}
            if (is_alive(i+GRID_LEN-1+GRID_LEN))  {++neighbour_count;}
            if (is_alive(i+GRID_LEN))             {++neighbour_count;}
            if (is_alive(i+GRID_LEN+1))           {++neighbour_count;}
            break;
            
            case bottom:
            if (is_alive(i-GRID_LEN-1))      {++neighbour_count;}
            if (is_alive(i-GRID_LEN))        {++neighbour_count;}
            if (is_alive(i-GRID_LEN+1))      {++neighbour_count;}
            if (is_alive(i-1))               {++neighbour_count;}
            if (is_alive(i+1))               {++neighbour_count;}
            if (is_alive((i%GRID_LEN)+0-1))  {++neighbour_count;}
            if (is_alive((i%GRID_LEN)+0))    {++neighbour_count;}
            if (is_alive((i%GRID_LEN)+0+1))  {++neighbour_count;}
            break;

            case top:
            if (is_alive(i+(GRID_SIZE-GRID_LEN)-1))  {++neighbour_count;}
            if (is_alive(i+(GRID_SIZE-GRID_LEN)))    {++neighbour_count;}
            if (is_alive(i+(GRID_SIZE-GRID_LEN)+1))  {++neighbour_count;}
            if (is_alive(i-1))                       {++neighbour_count;}
            if (is_alive(i+1))                       {++neighbour_count;}
            if (is_alive(i+GRID_LEN-1))              {++neighbour_count;}
            if (is_alive(i+GRID_LEN))                {++neighbour_count;}
            if (is_alive(i+GRID_LEN+1))              {++neighbour_count;}
            break;

            case inner:
            if (is_alive(i-GRID_LEN-1))  {++neighbour_count;}
            if (is_alive(i-GRID_LEN))    {++neighbour_count;}
            if (is_alive(i-GRID_LEN+1))  {++neighbour_count;}
            if (is_alive(i-1))           {++neighbour_count;}
            if (is_alive(i+1))           {++neighbour_count;}
            if (is_alive(i+GRID_LEN-1))  {++neighbour_count;}
            if (is_alive(i+GRID_LEN))    {++neighbour_count;}
            if (is_alive(i+GRID_LEN+1))  {++neighbour_count;}
            break;
            default:
            printf("somehow reached default\n");
            break;
            }
            neighbours[i] = neighbour_count;
        }
    }


    void conway_tick()
    {
/*         update_neighbours(); */
        update_neighbours_wraparound_360();

        for (int i=0; i<GRID_SIZE; ++i)
        {
            if (lives[i])
            {
                if (neighbours[i] < 2 || neighbours[i] > 3) {turn_cell_off(i);}
            }
            else
            {
                if (neighbours[i] == 3) {turn_cell_on(i);}
            }
        }
        ++generation_count;
    }
};

int main(void)
{
    Grid grid;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "window!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {grid.turn_cell_on(grid.get_idx(GetMousePosition()));}
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){grid.turn_cell_off(grid.get_idx(GetMousePosition()));}

        if (IsKeyPressed(KEY_ENTER)) {grid.conway_tick();}
        if (IsKeyDown(KEY_SPACE)) {grid.conway_tick();}

        if (IsKeyPressed(KEY_R)) {grid.reset();}

        if (IsKeyPressed(KEY_G)) {grid.put_glider_on_idx(grid.get_idx(GetMousePosition()));}

        if (IsKeyPressed(KEY_B)) {grid.otuzbir(grid.get_idx(GetMousePosition()));}

        std::string idx = "idx=" + std::to_string(grid.get_idx(GetMousePosition()));
        std::string generation = "gen=" + std::to_string(grid.generation_count);

        BeginDrawing();

            ClearBackground(COLOR_BACKGROUND);
            
            grid.draw();
            DrawText(idx.c_str(), 50, 15, 20, DARKGRAY);

            DrawText(generation.c_str(), 200, 15, 20, DARKGRAY);

            const char* instructions = "LMB: draw, RMB: erase, ENTER: single_step, SPACE: fastforward";
            DrawText(instructions, WINDOW_WIDTH*0.5 - MeasureText(instructions, 20)*0.5, 45, 20, DARKGRAY);

            const char* instructions2 = "r: reset, g: glide, b: 31";
            DrawText(instructions2, WINDOW_WIDTH*0.5 - MeasureText(instructions2, 20)*0.5, 70, 20, DARKGRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}