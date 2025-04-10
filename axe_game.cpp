// #include "raylib.h"
// #include <iostream>
// using namespace std;

// int main()
// {
//    // Always initialize window before drawing
//    int width = 800, height = 460;
//    InitWindow(width, height, "Axe Game");
//    SetTargetFPS(60); // Optional: limits FPS for smoother animation
   
//    // Circle Coordinate
//    int circle_x = 400, circle_y = 230;
//    int circle_radius = 25;

//    // Circle Edge Coordinate
//    int l_circle_x = circle_x - circle_radius; // to move right to left
//    int r_circle_x = circle_x + circle_radius; // to move left to right
//    int t_circle_y = circle_y - circle_radius; // to move bottom to top
//    int b_circle_y = circle_y + circle_radius; // to move top to bottom

//    // Axe Coordinate
//    int axe_x = 400, axe_y = 0;
//    int axe_length = 50;

//    // Axe Edge Coordinate
//    int l_axe_x = axe_x;
//    int r_axe_x = axe_x + axe_length;
//    int t_axe_y = axe_y;
//    int b_axe_y = axe_y + axe_length;

//    // Direction of the objects
//    int direction = 10;

//    bool collision_with_axe = false;

//    int move_speed = 5;

//    while (!WindowShouldClose()){
//         BeginDrawing();
//         ClearBackground(WHITE);

//         // // Circle edges
//         // int l_circle_x = circle_x - circle_radius;
//         // int r_circle_x = circle_x + circle_radius;
//         // int t_circle_y = circle_y - circle_radius;
//         // int b_circle_y = circle_y + circle_radius;

//         // // Axe edges
//         // int l_axe_x = axe_x;
//         // int r_axe_x = axe_x + axe_length;
//         // int t_axe_y = axe_y;
//         // int b_axe_y = axe_y + axe_length;


//         if (b_axe_y >= t_circle_y && t_axe_y <= b_circle_y && r_axe_x >= l_circle_x && l_axe_x <= r_circle_x) {
//             collision_with_axe = true;
//         }

//         if (collision_with_axe) {
//             // DrawText("Game Over", 400, 230, 20, RED);
//             DrawText("Game Over", width / 2 - MeasureText("Game Over", 20) / 2, height / 2, 20, RED);
//         }
//         else {
//             // Draw a circle in the middle of the screen
//             DrawCircle(circle_x, circle_y, circle_radius, RED);  // Center x and Ceter y took half of the screen size

//             // if (IsKeyPressed(KEY_A) && circle_x > 0){
//             //     circle_x -= 100;
//             // }
//             // if (IsKeyPressed(KEY_D) && circle_x < width){
//             //     circle_x += 100;
//             // }
//             // if (IsKeyPressed(KEY_W) && circle_y > 0){
//             //     circle_y -= 100;
//             // }
//             // if (IsKeyPressed(KEY_S) && circle_y < height){
//             //     circle_y += 100;
//             // }


//             if (IsKeyDown(KEY_LEFT_SHIFT)) move_speed = 10;

//             if (IsKeyDown(KEY_LEFT) && circle_x - move_speed > 0) circle_x -= move_speed;
//             if (IsKeyDown(KEY_RIGHT) && circle_x + move_speed < width) circle_x += move_speed;
//             if (IsKeyDown(KEY_UP) && circle_y - move_speed > 0) circle_y -= move_speed;
//             if (IsKeyDown(KEY_DOWN) && circle_y + move_speed < height) circle_y += move_speed;

//             DrawRectangle(axe_x, axe_y, axe_length, axe_length, GREEN);
//             axe_y += direction;

//             if (axe_y > height || axe_y < 0) {
//                 direction = -direction;  // Its just flip the sign of the direction that's it!
//             }

//         }

//         EndDrawing();
//     }


//     CloseWindow(); // Always close the window

//     return 0;
    

// }

#include "raylib.h"
#include <cstdlib>   // For rand(), srand()
#include <ctime>     // For time()

int main()
{
    const int width = 800;
    const int height = 460;
    InitWindow(width, height, "Smooth LERP + Random Axe Movement");
    SetTargetFPS(60);

    srand(time(0));  // ✅ Seed for randomness

    // Circle setup
    float circle_radius = 25.0f;
    float circle_x = width / 2.0f;
    float circle_y = height / 2.0f;

    float target_x = circle_x;
    float target_y = circle_y;

    const float move_step = 10.0f;
    const float lerp_speed = 0.2f;

    // Axe setup
    int axe_x = 400, axe_y = 0;
    int axe_length = 50;

    // Random initial direction
    int dir_x = (rand() % 3 - 1) * 5;  // -5, 0, 5
    int dir_y = (rand() % 3 - 1) * 5;
    if (dir_x == 0 && dir_y == 0) dir_x = 5; 

    int frameCount = 0;

    bool collision_with_axe = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // === Collision detection edges ===
        float l_circle_x = circle_x - circle_radius;
        float r_circle_x = circle_x + circle_radius;
        float t_circle_y = circle_y - circle_radius;
        float b_circle_y = circle_y + circle_radius;

        int l_axe_x = axe_x;
        int r_axe_x = axe_x + axe_length;
        int t_axe_y = axe_y;
        int b_axe_y = axe_y + axe_length;

        // === COLLISION DETECTION ===
        if (b_axe_y >= t_circle_y && t_axe_y <= b_circle_y &&
            r_axe_x >= l_circle_x && l_axe_x <= r_circle_x)
        {
            collision_with_axe = true;
        }

        if (collision_with_axe)
        {
            DrawText("Game Over", width / 2 - MeasureText("Game Over", 30) / 2, height / 2, 30, RED);
        }
        else
        {
            // === Circle input movement ===
            if (IsKeyDown(KEY_RIGHT) && target_x + circle_radius < width) target_x += move_step;
            if (IsKeyDown(KEY_LEFT) && target_x - circle_radius > 0) target_x -= move_step;
            if (IsKeyDown(KEY_DOWN) && target_y + circle_radius < height) target_y += move_step;
            if (IsKeyDown(KEY_UP) && target_y - circle_radius > 0) target_y -= move_step;

            // Smooth movement
            circle_x += (target_x - circle_x) * lerp_speed;
            circle_y += (target_y - circle_y) * lerp_speed;

            // === Axe movement ===
            axe_x += dir_x;
            axe_y += dir_y;

            // Bounce off edges
            if (axe_x <= 0 || axe_x + axe_length >= width) dir_x = -dir_x;
            if (axe_y <= 0 || axe_y + axe_length >= height) dir_y = -dir_y;

            // Periodically change direction (every 2 seconds at 60 FPS)
            frameCount++;
            if (frameCount > 120)
            {
                dir_x = (rand() % 3 - 1) * 5;
                dir_y = (rand() % 3 - 1) * 5;
                if (dir_x == 0 && dir_y == 0) dir_x = 5;
                frameCount = 0;
            }

            // === Drawing ===
            DrawText("Avoid the Axe!", 10, 10, 20, GRAY);
            DrawCircle((int)circle_x, (int)circle_y, circle_radius, RED);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
