#include "raylib.h"

int main(){
    int screenWidth = 600;
    int screenHeight = 500;

    Vector2 ballPos = {
        .x = 0.5 * screenWidth,
        .y = 0.5 * screenHeight
    };

    Vector2 paddleSize = {
        .x = 15,
        .y = 90
    };

    Vector2 paddleL_X = {
        .x = 10,
        .y = 0.5 * screenHeight - (paddleSize.y / 2)
    };

    Vector2 paddleR_X = {
        .x = screenWidth - 10 - paddleSize.x,
        .y = 0.5 * screenHeight - (paddleSize.y / 2)
    };

    int radius = 10;

    InitWindow(screenWidth, screenHeight, "Ping Pong");

    Rectangle paddleL = {paddleL_X.x, paddleL_X.y, paddleSize.x, paddleSize.y};
    Rectangle paddleR = {paddleR_X.x, paddleR_X.y, paddleSize.x, paddleSize.y};

    float ballVel = 0.03f;
    float ballYVel = 0.01f;
    float paddleSpeed = 0.1f;

    while (!WindowShouldClose())
    {
        


        // Ball movement
        ballPos.x += ballVel;
        ballPos.y += ballYVel;

        if(CheckCollisionCircleRec(ballPos, radius, paddleL) || CheckCollisionCircleRec(ballPos, radius, paddleR)){
            ballVel = 0 - ballVel; 
        }
        
        // Establishing Ball Bounds
        if(ballPos.y < 0){
            ballPos.y = 0;
            ballYVel = 0 - ballYVel;
        }
        if(ballPos.y > GetScreenHeight() - ballPos.y){
            ballPos.y = GetScreenHeight() - ballPos.y;
            ballYVel = 0 - ballYVel;
        }
        // Establishing Paddle Bounds
        //  -left
        if(paddleL.y < 0) paddleL.y = 0;
        if(paddleL.y > GetScreenHeight() - paddleSize.y) paddleL.y = GetScreenHeight() - paddleSize.y;
        //  -right
        if(paddleR.y < 0) paddleR_X.y = 0;
        if(paddleR.y > GetScreenHeight() - paddleSize.y) paddleR.y = GetScreenHeight() - paddleSize.y;
        
        // Paddle Movement
        //  -left
        if(IsKeyDown(KEY_W)) paddleL.y -= paddleSpeed;
        if(IsKeyDown(KEY_S)) paddleL.y += paddleSpeed;

        //  -right
        if(IsKeyDown(KEY_UP)) paddleR.y -= paddleSpeed;
        if(IsKeyDown(KEY_DOWN)) paddleR.y += paddleSpeed;




        BeginDrawing();
        // Drawing
        ClearBackground(BLACK);

        DrawCircleV(ballPos, radius, WHITE);
        DrawRectangleRec(paddleL, WHITE);
        DrawRectangleRec(paddleR, WHITE);

        EndDrawing();
    }

    while(!WindowShouldClose){
        WaitTime(5.0);
        ballVel += 0.02f;
    }

    CloseWindow();
    return 0;  
}
