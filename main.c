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

    int score_L = 0;
    int score_R = 0;

    while (!WindowShouldClose())
    {
        


        // Ball movement
        ballPos.x += ballVel;
        ballPos.y += ballYVel;

        if(CheckCollisionCircleRec(ballPos, radius, paddleL) || CheckCollisionCircleRec(ballPos, radius, paddleR)){
            ballVel = 0 - ballVel; 
        }


        
        // Establishing Ball Bounds
        //  -bottom
        if(ballPos.y < 0 + radius){
            ballPos.y = 0 + radius;
            ballYVel = 0 - ballYVel;
        }
        //  -top
        if(ballPos.y > GetScreenHeight() - radius){
            ballPos.y = GetScreenHeight() - radius;
            ballYVel = 0 - ballYVel;
        }

        if(ballPos.x <= 0 + radius){
            score_R += 1;
            ballPos.x = 0.5 * screenWidth;
            ballPos.y = 0.5 * screenHeight;

            ballVel = 0 - ballVel;

        } else if (ballPos.x >= GetScreenWidth() - radius){
            score_L += 1;
            ballPos.x = 0.5 * screenWidth;
            ballPos.y = 0.5 * screenHeight;

            ballVel = 0 - ballVel;  
        }

        // Establishing Paddle Bounds
        //  -left
        if(paddleL.y < 0) paddleL.y = 0;
        if(paddleL.y > GetScreenHeight() - paddleSize.y) paddleL.y = GetScreenHeight() - paddleSize.y;
        //  -right
        if(paddleR.y < 0) paddleR.y = 0;
        if(paddleR.y > GetScreenHeight() - paddleSize.y) paddleR.y = GetScreenHeight() - paddleSize.y;
        
        // Paddle Movement
        //  -left
        if(IsKeyDown(KEY_W)) paddleL.y -= paddleSpeed;
        if(IsKeyDown(KEY_S)) paddleL.y += paddleSpeed;

        //  -right
        if(IsKeyDown(KEY_UP)) paddleR.y -= paddleSpeed;
        if(IsKeyDown(KEY_DOWN)) paddleR.y += paddleSpeed;

        if(ballVel > 0){
            ballVel += 0.00001f * GetFrameTime();
        } else if (ballVel < 0){
            ballVel -= 0.00001f * GetFrameTime();
        }

        BeginDrawing();
        // Drawing
        ClearBackground(BLACK);

        // "SCORE BOARD" - vietnamese guy
        //  -left
        DrawText(TextFormat("%i", score_L), screenWidth / 4 * 3, screenHeight / 2 - 32, 64, GRAY);
        //  -right
        DrawText(TextFormat("%i", score_R), screenWidth / 4, screenHeight / 2 - 32, 64, GRAY);
        
        // DEBUG TEXT
        DrawText(TextFormat("Ball x speed: %f", ballVel), 20, screenHeight - 20, 10, GRAY);
        DrawText(TextFormat("Ball y speed: %f", ballYVel), 20, screenHeight - 40, 10, GRAY);

        DrawText(TextFormat("Ball x position: %f", ballPos.x), 20, screenHeight - 80, 10, GRAY);
        DrawText(TextFormat("Ball y position: %f", ballPos.y), 20, screenHeight - 60, 10, GRAY);

        // SHAPES
        DrawCircleV(ballPos, radius, WHITE);
        DrawRectangleRec(paddleL, WHITE);
        DrawRectangleRec(paddleR, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;  
}
