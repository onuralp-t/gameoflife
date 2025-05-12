#include "common.h" // IWYU pragma: keep

#include "constants.h"

typedef struct cellstate
{
    Rectangle rect; // 4 floats, 4*4 == 16 bytes
    Color color;    // 4 u8's == 4 bytes
    u8 neighbours;
    bool alive;
} cellstate;

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
            cells[i].neighbours = 0;
            cells[i].alive = false;
        }
    }

} Grid;

void draw(Grid &grid)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        DrawRectangleRec(grid.cells[i].rect, grid.cells[i].color);
        DrawRectangleLines(grid.cells[i].rect.x, grid.cells[i].rect.y, grid.cells[i].rect.width, grid.cells[i].rect.width, COLOR_BORDER);
    }
}

void reset(Grid &grid)
{
    grid.generation_count = 0;

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        grid.cells[i].rect.x = (i % GRID_LEN) * CELL_WIDTH + (WINDOW_WIDTH - GRID_LEN * CELL_WIDTH) * 0.5;
        grid.cells[i].rect.y = ((int)(i / GRID_LEN)) * CELL_WIDTH + (WINDOW_HEIGHT - GRID_LEN * CELL_WIDTH + TOP_REGION_HEIGHT) * 0.5;

        grid.cells[i].rect.width = CELL_WIDTH;
        grid.cells[i].rect.height = CELL_WIDTH;

        grid.cells[i].color = COLOR_OFF;
        grid.cells[i].neighbours = 0;
        grid.cells[i].alive = false;
    }
}

int get_idx(Grid &grid, Vector2 mousepos)
{
    bool mouse_within_grid_x = mousepos.x > grid.cells[0].rect.x && (mousepos.x < (grid.cells[GRID_LEN - 1].rect.x + CELL_WIDTH));
    bool mouse_within_grid_y = mousepos.y > grid.cells[0].rect.y && (mousepos.y < (grid.cells[GRID_SIZE - GRID_LEN].rect.y + CELL_WIDTH));

    if (mouse_within_grid_x && mouse_within_grid_y)
    {
        int col = (mousepos.x - grid.cells[0].rect.x) / CELL_WIDTH;
        int row = (mousepos.y - grid.cells[0].rect.y) / CELL_WIDTH;
        return (row * GRID_LEN + col);
    }

    return -1;
}

void turn_cell_on(Grid &grid, int idx)
{
    grid.cells[idx].alive = true;
    grid.cells[idx].color = COLOR_ON;
}

void turn_cell_off(Grid &grid, int idx)
{
    grid.cells[idx].alive = false;
    grid.cells[idx].color = COLOR_OFF;
}

void update_neighbours(Grid &grid)
{
    auto is_alive = [&](int idx)
    {
        if (idx < 0 || (idx > (GRID_SIZE - 1))) {
            return false;
        } else {
            bool boing = grid.cells[idx].alive;
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

        grid.cells[i].neighbours = neighbour_count;
    }
}

void put_glider_on_idx(Grid &grid, int idx)
{
    turn_cell_off(grid, idx);
    turn_cell_off(grid, idx+1);
    turn_cell_off(grid, idx+2);
    turn_cell_off(grid, idx+GRID_LEN);
    turn_cell_off(grid, idx+GRID_LEN+1);
    turn_cell_off(grid, idx+GRID_LEN+2);
    turn_cell_off(grid, idx+2*GRID_LEN);
    turn_cell_off(grid, idx+2*GRID_LEN+1);
    turn_cell_off(grid, idx+2*GRID_LEN+2);

    turn_cell_on(grid, idx);
/*         turn_cell_on(grid, idx+1); */
    turn_cell_on(grid, idx+2);
/*         turn_cell_on(grid, idx+GRID_LEN); */
    turn_cell_on(grid, idx+GRID_LEN+1);
    turn_cell_on(grid, idx+GRID_LEN+2);
/*         turn_cell_on(grid, idx+2*GRID_LEN); */
    turn_cell_on(grid, idx+2*GRID_LEN+1);
/*         turn_cell_on(grid, idx+2*GRID_LEN+2); */
}

void period_31(Grid &grid, int idx)
{
    turn_cell_on(grid, idx + 7);
    turn_cell_on(grid, idx + 8);
    turn_cell_on(grid, idx + 10);

    turn_cell_on(grid, idx + 13);
    turn_cell_on(grid, idx + 15);
    turn_cell_on(grid, idx + 16);

    turn_cell_on(grid, idx + GRID_LEN);
    turn_cell_on(grid, idx + GRID_LEN + 1);
    turn_cell_on(grid, idx + GRID_LEN + 6);
    turn_cell_on(grid, idx + GRID_LEN + 9);

    turn_cell_on(grid, idx + GRID_LEN + 14);
    turn_cell_on(grid, idx + GRID_LEN + 17);
    turn_cell_on(grid, idx + GRID_LEN + 22);
    turn_cell_on(grid, idx + GRID_LEN + 23);

    turn_cell_on(grid, idx + 2*GRID_LEN);
    turn_cell_on(grid, idx + 2*GRID_LEN + 1);
    turn_cell_on(grid, idx + 2*GRID_LEN + 7);
    turn_cell_on(grid, idx + 2*GRID_LEN + 9);

    turn_cell_on(grid, idx + 2*GRID_LEN + 14);
    turn_cell_on(grid, idx + 2*GRID_LEN + 16);
    turn_cell_on(grid, idx + 2*GRID_LEN + 22);
    turn_cell_on(grid, idx + 2*GRID_LEN + 23);

    turn_cell_on(grid, idx + 3*GRID_LEN + 8);
    turn_cell_on(grid, idx + 3*GRID_LEN + 15);

    turn_cell_on(grid, idx + 9*GRID_LEN + 8);
    turn_cell_on(grid, idx + 9*GRID_LEN + 15);

    turn_cell_on(grid, idx + 10*GRID_LEN);
    turn_cell_on(grid, idx + 10*GRID_LEN + 1);
    turn_cell_on(grid, idx + 10*GRID_LEN + 7);
    turn_cell_on(grid, idx + 10*GRID_LEN + 9);

    turn_cell_on(grid, idx + 10*GRID_LEN + 14);
    turn_cell_on(grid, idx + 10*GRID_LEN + 16);
    turn_cell_on(grid, idx + 10*GRID_LEN + 22);
    turn_cell_on(grid, idx + 10*GRID_LEN + 23);

    turn_cell_on(grid, idx + 11*GRID_LEN);
    turn_cell_on(grid, idx + 11*GRID_LEN + 1);
    turn_cell_on(grid, idx + 11*GRID_LEN + 6);
    turn_cell_on(grid, idx + 11*GRID_LEN + 9);

    turn_cell_on(grid, idx + 11*GRID_LEN + 14);
    turn_cell_on(grid, idx + 11*GRID_LEN + 17);
    turn_cell_on(grid, idx + 11*GRID_LEN + 22);
    turn_cell_on(grid, idx + 11*GRID_LEN + 23);

    turn_cell_on(grid, idx + 12*GRID_LEN + 7);
    turn_cell_on(grid, idx + 12*GRID_LEN + 8);
    turn_cell_on(grid, idx + 12*GRID_LEN + 10);

    turn_cell_on(grid, idx + 12*GRID_LEN + 13);
    turn_cell_on(grid, idx + 12*GRID_LEN + 15);
    turn_cell_on(grid, idx + 12*GRID_LEN + 16);
}

void update_neighbours_wraparound_360(Grid &grid)
{
    auto is_alive = [&](int idx)
    {
        if (idx < 0 || (idx > (GRID_SIZE - 1))) {
            return false;
        } else {
            return grid.cells[idx].alive;
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
        printf("somehow reached default/n");
        break;

        }
        grid.cells[i].neighbours = neighbour_count;
    }
}

void conway_tick(Grid &grid)
{
    /* update_neighbours(grid); */
    update_neighbours_wraparound_360(grid);

    for (int i=0; i<GRID_SIZE; ++i)
    {
        if (grid.cells[i].alive)
        {
            if (grid.cells[i].neighbours < 2 || grid.cells[i].neighbours > 3) {turn_cell_off(grid, i);}
        }
        else
        {
            if (grid.cells[i].neighbours == 3) {turn_cell_on(grid, i);}
        }
    }
    grid.generation_count++;
}

int main(void)
{
    Grid grid;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "goool");

    Image windowIconOriginal = LoadImage("assets/icon.png");

    if (windowIconOriginal.data != NULL) {
        // Check if the format is already R8G8B8A8, if not, convert it
        if (windowIconOriginal.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
        {
            ImageFormat(&windowIconOriginal, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            TraceLog(LOG_INFO, "RUNTIME ICON: Converted window icon to R8G8B8A8 format.");
        }
        SetWindowIcon(windowIconOriginal); // SetWindowIcon expects the Image by value
        UnloadImage(windowIconOriginal);   // Unload the original (or converted) image data
    } else {
        TraceLog(LOG_WARNING, "RUNTIME ICON: Failed to load window icon from PNG.");
    }

    SetTargetFPS(0);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))   {turn_cell_on(grid, get_idx(grid, GetMousePosition()));}
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {turn_cell_off(grid, get_idx(grid, GetMousePosition()));}

        if (IsKeyPressed(KEY_ENTER)) {conway_tick(grid);}
        if (IsKeyDown(KEY_SPACE))    {conway_tick(grid);}

        if (IsKeyPressed(KEY_R)) {reset(grid);}

        if (IsKeyPressed(KEY_G)) {put_glider_on_idx(grid, get_idx(grid, GetMousePosition()));}

        if (IsKeyPressed(KEY_B))
        {
            period_31(grid, get_idx(grid, GetMousePosition()));
        }

        std::string idx           = "idx=" + std::to_string(get_idx(grid, GetMousePosition()));
        std::string generation    = "gen=" + std::to_string(grid.generation_count);
        std::string instructions  = "LMB: draw, RMB: erase, ENTER: single_step, SPACE: fastforward";
        std::string instructions2 = "r: reset, g: glide, b: period_31";

        BeginDrawing();

            ClearBackground(COLOR_BACKGROUND);
            
            draw(grid);

            DrawText(idx.c_str(),         50, 15, FONTSIZE, DARKGRAY);
            DrawText(generation.c_str(), 200, 15, FONTSIZE, DARKGRAY);

            int inst1x = (WINDOW_WIDTH - MeasureText(instructions.c_str(),  FONTSIZE)) * 0.5;
            int inst2x = (WINDOW_WIDTH - MeasureText(instructions2.c_str(), FONTSIZE)) * 0.5;

            DrawText(instructions.c_str(),  inst1x, 45, FONTSIZE, DARKGRAY);
            DrawText(instructions2.c_str(), inst2x, 75, FONTSIZE, DARKGRAY);

            DrawFPS(WINDOW_WIDTH-85, 75);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}