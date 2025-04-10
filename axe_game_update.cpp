#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <math.h>

struct Axe {
    int x, y;
    int width, height;
    int dir_x, dir_y;

    Axe(int posX, int posY)
    {
        x = posX;
        y = posY;
        width = 50;
        height = 50;

        dir_x = (rand() % 3 - 1) * 5;
        dir_y = (rand() % 3 - 1) * 5;
        if (dir_x == 0 && dir_y == 0) dir_x = 5;
    }

    void Move(int screenW, int screenH)
    {
        x += dir_x;
        y += dir_y;

        if (x <= 0 || x + width >= screenW) dir_x = -dir_x;
        if (y <= 0 || y + height >= screenH) dir_y = -dir_y;
    }

    void RandomizeDirection()
    {
        dir_x = (rand() % 3 - 1) * 5;
        dir_y = (rand() % 3 - 1) * 5;
        if (dir_x == 0 && dir_y == 0) dir_x = 5;
    }
};

int main()
{
    const int width = 800;
    const int height = 460;
    InitWindow(width, height, "Raylib Game - Advanced Mode");
    SetTargetFPS(60);

    srand(time(0));

    // Player setup
    float radius = 25;
    float circle_x = width / 2.0f;
    float circle_y = height / 2.0f;
    float target_x = circle_x;
    float target_y = circle_y;
    const float move_step = 10.0f;
    const float lerp_speed = 0.2f;

    // Game state
    bool gameOver = false;
    int frameCount = 0;
    float survivalTime = 0;

    // Multiple axes
    std::vector<Axe> axes;
    axes.push_back(Axe(100, 0));
    axes.push_back(Axe(300, 200));
    axes.push_back(Axe(600, 100));

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // === Restart game ===
        if (gameOver && IsKeyPressed(KEY_R)) {
            circle_x = width / 2.0f;
            circle_y = height / 2.0f;
            target_x = circle_x;
            target_y = circle_y;
            survivalTime = 0;
            frameCount = 0;
            gameOver = false;
            axes.clear();
            axes.push_back(Axe(100, 0));
            axes.push_back(Axe(300, 200));
            axes.push_back(Axe(600, 100));
        }

        if (!gameOver)
        {
            // Input
            if (IsKeyDown(KEY_RIGHT) && target_x + radius < width) target_x += move_step;
            if (IsKeyDown(KEY_LEFT) && target_x - radius > 0) target_x -= move_step;
            if (IsKeyDown(KEY_DOWN) && target_y + radius < height) target_y += move_step;
            if (IsKeyDown(KEY_UP) && target_y - radius > 0) target_y -= move_step;

            circle_x += (target_x - circle_x) * lerp_speed;
            circle_y += (target_y - circle_y) * lerp_speed;

            // Timer
            survivalTime += GetFrameTime();

            // Move and draw axes
            for (Axe &axe : axes)
            {
                axe.Move(width, height);
                DrawRectangle(axe.x, axe.y, axe.width, axe.height, GREEN);

                // Collision detection
                float l_circle_x = circle_x - radius;
                float r_circle_x = circle_x + radius;
                float t_circle_y = circle_y - radius;
                float b_circle_y = circle_y + radius;

                int l_axe_x = axe.x;
                int r_axe_x = axe.x + axe.width;
                int t_axe_y = axe.y;
                int b_axe_y = axe.y + axe.height;

                if (b_axe_y >= t_circle_y && t_axe_y <= b_circle_y &&
                    r_axe_x >= l_circle_x && l_axe_x <= r_circle_x)
                {
                    gameOver = true;
                }
            }

            // Change direction every 2 sec
            frameCount++;
            if (frameCount > 120)
            {
                for (Axe &axe : axes)
                    axe.RandomizeDirection();
                frameCount = 0;
            }

            DrawText(TextFormat("Survival Time: %.2f", survivalTime), 10, 10, 20, DARKGRAY);
            DrawCircle((int)circle_x, (int)circle_y, radius, RED);
        }
        else
        {
            DrawText("Game Over", width / 2 - MeasureText("Game Over", 30) / 2, height / 2 - 20, 30, RED);
            DrawText(TextFormat("You survived %.2f seconds", survivalTime), width / 2 - 150, height / 2 + 20, 20, WHITE);
            DrawText("Press R to restart", width / 2 - 90, height / 2 + 50, 20, WHITE);

            // Tiny animation: flicker background circle
            DrawCircle((int)circle_x, (int)circle_y, radius + 5 * sinf(GetTime() * 10), Fade(RED, 0.3f));
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
