#include "common.h" // IWYU pragma: keep

#include "constants.h"

typedef struct cellstate
{
    Rectangle rect; // 4 floats, 4*4 == 16 bytes
    Color color; // 4 u8's == 4 bytes
    u8 neighbours;
    bool alive;
}cellstate;

typedef struct Grid
{
    std::vector<cellstate> cells;

    u64 generation_count;

    Grid() : generation_count(0), cells(GRID_SIZE)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            cells[i].rect.x = (i % GRID_LEN) * CELL_WIDTH + (WINDOW_WIDTH - GRID_LEN * CELL_WIDTH) * 0.5;
            cells[i].rect.y = ((int)(i / GRID_LEN)) * CELL_WIDTH + (WINDOW_HEIGHT - GRID_LEN * CELL_WIDTH + TOP_REGION_HEIGHT) * 0.5;

            cells[i].rect.width = CELL_WIDTH;
            cells[i].rect.height = CELL_WIDTH;
            cells[i].color = COLOR_OFF;
        }
    }

} Grid;

void draw(Grid &g)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        DrawRectangleRec(g.cells[i].rect, g.cells[i].color);
        DrawRectangleLines(g.cells[i].rect.x, g.cells[i].rect.y, g.cells[i].rect.width, g.cells[i].rect.width, COLOR_BORDER);
    }
}

void reset(Grid &g)
{
    g.generation_count = 0;

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        g.cells[i].rect.x = (i % GRID_LEN) * CELL_WIDTH + (WINDOW_WIDTH - GRID_LEN * CELL_WIDTH) * 0.5;
        g.cells[i].rect.y = ((int)(i / GRID_LEN)) * CELL_WIDTH + (WINDOW_HEIGHT - GRID_LEN * CELL_WIDTH + TOP_REGION_HEIGHT) * 0.5;

        g.cells[i].rect.width = CELL_WIDTH;
        g.cells[i].rect.height = CELL_WIDTH;

        g.cells[i].color = COLOR_OFF;
        g.cells[i].alive = false;
        g.cells[i].neighbours = 0;

    }
}

int get_idx(Grid &g, Vector2 mousepos)
{
    bool mouse_within_g_x = mousepos.x > g.cells[0].rect.x && (mousepos.x < (g.cells[GRID_LEN - 1].rect.x + CELL_WIDTH));
    bool mouse_within_g_y = mousepos.y > g.cells[0].rect.y && (mousepos.y < (g.cells[GRID_SIZE - GRID_LEN].rect.y + CELL_WIDTH));

    if (mouse_within_g_x && mouse_within_g_y)
    {
        int col = (mousepos.x - g.cells[0].rect.x) / CELL_WIDTH;
        int row = (mousepos.y - g.cells[0].rect.y) / CELL_WIDTH;
        return (row * GRID_LEN + col);
    }
    return -1;
}

void turn_cell_on(Grid &g, int idx)
{
    g.cells[idx].alive = true;
    g.cells[idx].color = COLOR_ON;
}

void turn_cell_off(Grid &g, int idx)
{
    g.cells[idx].alive = false;
    g.cells[idx].color = COLOR_OFF;
}

void update_neighbours(Grid &g)
{
    auto is_alive = [&](int idx)
    {
        if (idx < 0 || idx > GRID_SIZE - 1)
        {
            return false;
        }
        else
        {
            bool boing = g.cells[idx].alive;
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

        g.cells[i].neighbours = neighbour_count;
    }
}

void put_glider_on_idx(Grid &g, int idx)
{
    turn_cell_off(g, idx);
    turn_cell_off(g, idx+1);
    turn_cell_off(g, idx+2);
    turn_cell_off(g, idx+GRID_LEN);
    turn_cell_off(g, idx+GRID_LEN+1);
    turn_cell_off(g, idx+GRID_LEN+2);
    turn_cell_off(g, idx+2*GRID_LEN);
    turn_cell_off(g, idx+2*GRID_LEN+1);
    turn_cell_off(g, idx+2*GRID_LEN+2);

    turn_cell_on(g, idx);
/*         turn_cell_on(g, idx+1); */
    turn_cell_on(g, idx+2);
/*         turn_cell_on(g, idx+GRID_LEN); */
    turn_cell_on(g, idx+GRID_LEN+1);
    turn_cell_on(g, idx+GRID_LEN+2);
/*         turn_cell_on(g, idx+2*GRID_LEN); */
    turn_cell_on(g, idx+2*GRID_LEN+1);
/*         turn_cell_on(g, idx+2*GRID_LEN+2); */
}

void otuzbir(Grid &g, int idx)
{
    turn_cell_on(g, idx + 7);
    turn_cell_on(g, idx + 8);
    turn_cell_on(g, idx + 10);

    turn_cell_on(g, idx + 13);
    turn_cell_on(g, idx + 15);
    turn_cell_on(g, idx + 16);

    turn_cell_on(g, idx + GRID_LEN);
    turn_cell_on(g, idx + GRID_LEN + 1);
    turn_cell_on(g, idx + GRID_LEN + 6);
    turn_cell_on(g, idx + GRID_LEN + 9);

    turn_cell_on(g, idx + GRID_LEN + 14);
    turn_cell_on(g, idx + GRID_LEN + 17);
    turn_cell_on(g, idx + GRID_LEN + 22);
    turn_cell_on(g, idx + GRID_LEN + 23);


    turn_cell_on(g, idx + 2*GRID_LEN);
    turn_cell_on(g, idx + 2*GRID_LEN + 1);
    turn_cell_on(g, idx + 2*GRID_LEN + 7);
    turn_cell_on(g, idx + 2*GRID_LEN + 9);

    turn_cell_on(g, idx + 2*GRID_LEN + 14);
    turn_cell_on(g, idx + 2*GRID_LEN + 16);
    turn_cell_on(g, idx + 2*GRID_LEN + 22);
    turn_cell_on(g, idx + 2*GRID_LEN + 23);

    turn_cell_on(g, idx + 3*GRID_LEN + 8);
    turn_cell_on(g, idx + 3*GRID_LEN + 15);

    turn_cell_on(g, idx + 9*GRID_LEN + 8);
    turn_cell_on(g, idx + 9*GRID_LEN + 15);

    turn_cell_on(g, idx + 10*GRID_LEN);
    turn_cell_on(g, idx + 10*GRID_LEN + 1);
    turn_cell_on(g, idx + 10*GRID_LEN + 7);
    turn_cell_on(g, idx + 10*GRID_LEN + 9);

    turn_cell_on(g, idx + 10*GRID_LEN + 14);
    turn_cell_on(g, idx + 10*GRID_LEN + 16);
    turn_cell_on(g, idx + 10*GRID_LEN + 22);
    turn_cell_on(g, idx + 10*GRID_LEN + 23);

    turn_cell_on(g, idx + 11*GRID_LEN);
    turn_cell_on(g, idx + 11*GRID_LEN + 1);
    turn_cell_on(g, idx + 11*GRID_LEN + 6);
    turn_cell_on(g, idx + 11*GRID_LEN + 9);

    turn_cell_on(g, idx + 11*GRID_LEN + 14);
    turn_cell_on(g, idx + 11*GRID_LEN + 17);
    turn_cell_on(g, idx + 11*GRID_LEN + 22);
    turn_cell_on(g, idx + 11*GRID_LEN + 23);

    turn_cell_on(g, idx + 12*GRID_LEN + 7);
    turn_cell_on(g, idx + 12*GRID_LEN + 8);
    turn_cell_on(g, idx + 12*GRID_LEN + 10);

    turn_cell_on(g, idx + 12*GRID_LEN + 13);
    turn_cell_on(g, idx + 12*GRID_LEN + 15);
    turn_cell_on(g, idx + 12*GRID_LEN + 16);
}

void update_neighbours_wraparound_360(Grid &g)
{
    auto is_alive = [&](int idx)
    {
        if (idx < 0 || idx > GRID_SIZE - 1)
        {
            return false;
        }
        else
        {
            bool boing = g.cells[idx].alive;
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
        g.cells[i].neighbours = neighbour_count;
    }
}

void conway_tick(Grid &g)
{
/*         update_neighbours(); */
    update_neighbours_wraparound_360(g);

    for (int i=0; i<GRID_SIZE; ++i)
    {
        if (g.cells[i].alive)
        {
            if (g.cells[i].neighbours < 2 || g.cells[i].neighbours > 3) {turn_cell_off(g, i);}
        }
        else
        {
            if (g.cells[i].neighbours == 3) {turn_cell_on(g, i);}
        }
    }
    g.generation_count++;
}

int main(void)
{
    Grid g;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "window!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {turn_cell_on(g, get_idx(g, GetMousePosition()));}
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){turn_cell_off(g, get_idx(g, GetMousePosition()));}

        if (IsKeyPressed(KEY_ENTER)) {conway_tick(g);}
        if (IsKeyDown(KEY_SPACE)) {conway_tick(g);}

        if (IsKeyPressed(KEY_R)) {reset(g);}

        if (IsKeyPressed(KEY_G)) {put_glider_on_idx(g, get_idx(g, GetMousePosition()));}

        if (IsKeyPressed(KEY_B))
        {
            otuzbir(g, get_idx(g, GetMousePosition()));
        }

        std::string idx = "idx=" + std::to_string(get_idx(g, GetMousePosition()));
        std::string generation = "gen=" + std::to_string(g.generation_count);

        BeginDrawing();

            ClearBackground(COLOR_BACKGROUND);
            
            draw(g);
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