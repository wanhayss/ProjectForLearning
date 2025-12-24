#include "raylib.h"
#include "stdio.h"
#include "time.h"

typedef struct Brick {
    Rectangle block;
    bool active;
}Brick;
const int brick_count = 11;
const int screen_width = 800;
const int screen_height = 450;
const float rectangle_width = 100.0f;
const float rectangle_heigth = 10.0f;
const float rectangle_speed = 5.0f;
const float ball_radius = 4.0f;
bool run = true;

void play(bool run){
    clock_t start = clock()/100000;
    clock_t now = clock()/100000;
    int score = 0;
    char text1[100];
    InitWindow(screen_width, screen_height, "Window");
    Brick bricks[brick_count];
    for (int i = 0; i < brick_count; i++){
        if(i == 0){
            bricks[i].block.x = 20.0f;
        }
        else{
            bricks[i].block.x = bricks[i-1].block.x + 70.0f;
        }
        bricks[i].block.y = 10.0f;
        bricks[i].block.width = 60.0f;
        bricks[i].block.height = 10.0f;
        bricks[i].active = true;
    }
    // Vector2 ball_position = {(float)screen_width/2,(float)screen_height/2};
    Vector2 rectangle_position = {(float)screen_width/2, 350.0f};
    Vector2 rectangle_size = {rectangle_width, rectangle_heigth};
    Vector2 ball_pos = {(float)screen_width/2, (float)screen_height/2};
    Vector2 ball_dir = {0.0f, 4.0f};
    Rectangle paddle_rec = {
        rectangle_position.x,
        rectangle_position.y,
        rectangle_width,
        rectangle_heigth
    };
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        // printf("%ld %d\n", now, score);
        if (IsKeyDown(KEY_D)){
            if (rectangle_position.x<((float)screen_width-rectangle_width)){
                rectangle_position.x += rectangle_speed;
            }
            else{
                rectangle_position.x=(float)screen_width-rectangle_width;
            }
        } 
        if (IsKeyDown(KEY_A)){
            if (rectangle_position.x>0.0f){
                rectangle_position.x -= rectangle_speed;
            }
            else{
                rectangle_position.x=0.0f;
            }
        }
        paddle_rec.x = rectangle_position.x;
        
        ball_pos.x += ball_dir.x;
        ball_pos.y += ball_dir.y;
        if (ball_pos.x>((float)screen_width-ball_radius)){
            if(ball_dir.x>0) ball_dir.x *= -1;
        }
        else if (ball_pos.x<0.0f){
            if(ball_dir.x<0) ball_dir.x *= -1;
        }
        else if (ball_pos.y>((float)screen_height-ball_radius)){
            run=false;
            if(ball_dir.y>0) ball_dir.y *= -1;
            }
        else if (ball_pos.y<0.0f){
            if(ball_dir.y<0) ball_dir.y *= -1;
            }
        else if(CheckCollisionCircleRec(ball_pos, ball_radius, paddle_rec)){
            if(ball_pos.y <= 350.0f || ball_pos.y >= 360.0f){
                ball_dir.x = -4.0f*(1.0f-(ball_pos.x-paddle_rec.x)/50.0f);
                ball_dir.y *= -1;
            }
            else{
                ball_dir.x *= -1;
            }
        }
        for(int i = 0; i<brick_count; i++){
            if(CheckCollisionCircleRec(ball_pos, ball_radius, bricks[i].block)){
                score++;
                bricks[i].active = false;
                if(ball_pos.y <= 10.0f || ball_pos.y >= 20.0f){
                    ball_dir.y *= -1;
                }
                else{
                    ball_dir.x *= -1;
                }
            }
        }
        if(run == true){
            now = clock()/100000;
            now = now - start;
            sprintf(text1,"Score: %d Time: %lds", score, now);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            // DrawText("Move Your Ball", 190, 200, 20, LIGHTGRAY);
            DrawCircleV(ball_pos, 4.0f, BLUE);
            DrawRectangleV(rectangle_position, rectangle_size, BLACK);
            for(int i = 0; i<brick_count; i++){
                if(bricks[i].active){
                    DrawRectangleRec(bricks[i].block, BLACK);
                }
                else{
                    Rectangle null = {-100.0f, -100.0f, 0, 0};
                    bricks[i].block = null;                
                }
            }
            EndDrawing();
        }
        else if(run == false){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(text1, 200, 175, 30, LIGHTGRAY);
            DrawText("Press ENTER To Play Again", 200, 225, 30, LIGHTGRAY);
            DrawText("Press ESC To Quit", 200, 275, 30, LIGHTGRAY);
            start = clock()/100000;
            if (IsKeyDown(KEY_ENTER)) {
                ball_pos.x = (float)screen_width/2;
                ball_pos.y = (float)screen_height/2;
                score = 0;
                for (int i = 0; i < brick_count; i++){
                    if(i == 0){
                        bricks[i].block.x = 20.0f;
                    }
                    else{
                        bricks[i].block.x = bricks[i-1].block.x + 70.0f;
                    }
                    bricks[i].block.y = 10.0f;
                    bricks[i].block.width = 60.0f;
                    bricks[i].block.height = 10.0f;
                    bricks[i].active = true;
                }
                run=true;
            }
            else if(IsKeyDown(KEY_ESCAPE)){
                EndDrawing();
                CloseWindow();
            }
            else{
                EndDrawing();
            }
            
        }
    }
}
int main(void){
    play(run);
    return 0;
}