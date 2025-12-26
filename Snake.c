#include <raylib.h>
#include <stdio.h>

#define SNAKE_LENGTH 256
#define SQUARE_SIDE 30

typedef struct Snake{
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
}Snake;
typedef struct Food{
    Vector2 position;
    Vector2 size;
    bool isEaten;
    Color color;
}Food;

static const int gameSpeed = 10;
static const int screenWidth = 800;
static const int screenHeight = 450;

static Vector2 snakePosition[SNAKE_LENGTH] = {0};
static Vector2 offset = {0};
static Snake snake[SNAKE_LENGTH] = {0};
static Food food = {0};
static int snakeTail = 0;
static bool gameRun = true;
static int score = 0;
static char buffer[100]; // for score text

int main(){
    InitWindow(screenWidth, screenHeight, "window");
    snakeTail = 1;
    offset = (Vector2){screenWidth%SQUARE_SIDE, screenHeight%SQUARE_SIDE};
    for(int i = 0; i < SNAKE_LENGTH; i++){
        snake[i].position = (Vector2){0.0f + offset.x/2, 0.0f + offset.y/2};
        snake[i].speed = (Vector2){(float)SQUARE_SIDE, 0.0f};
        snake[i].size = (Vector2){SQUARE_SIDE, SQUARE_SIDE};
    }
    food.size = (Vector2){SQUARE_SIDE, SQUARE_SIDE};
    // food.position.x = offset.x/2 + GetRandomValue(0, screenWidth/SQUARE_SIDE-1)*SQUARE_SIDE;
    // food.position.y = offset.y/2 + GetRandomValue(0, screenHeight/SQUARE_SIDE-1)*SQUARE_SIDE;
    food.isEaten = true;
    SetTargetFPS(gameSpeed);
        while(!WindowShouldClose()){
            if (gameRun == true){
                if(food.isEaten == true){
                food.isEaten = false;
                food.position.x = offset.x/2 + GetRandomValue(0, screenWidth/SQUARE_SIDE-1)*SQUARE_SIDE;
                food.position.y = offset.y/2 + GetRandomValue(0, screenHeight/SQUARE_SIDE-1)*SQUARE_SIDE;
                for(int i = 0; i < snakeTail; i++){
                    while(food.position.x == snake[i].position.x && food.position.y == snake[i].position.y){
                        food.position.x = offset.x/2 + GetRandomValue(0, screenWidth/SQUARE_SIDE-1)*SQUARE_SIDE;
                        food.position.y = offset.y/2 + GetRandomValue(0, screenHeight/SQUARE_SIDE-1)*SQUARE_SIDE;
                        
                    }
                }
            }

            // Movement
            if (IsKeyDown(KEY_D) && snake[0].speed.x != -(float)SQUARE_SIDE){
                snake[0].speed = (Vector2){(float)SQUARE_SIDE, 0.0f};
                } 
            else if (IsKeyDown(KEY_A) && snake[0].speed.x != (float)SQUARE_SIDE){
                snake[0].speed = (Vector2){-(float)SQUARE_SIDE, 0.0f};
                }
            else if (IsKeyDown(KEY_W) && snake[0].speed.y != (float)SQUARE_SIDE){
                snake[0].speed = (Vector2){0.0f , -(float)SQUARE_SIDE};
                } 
            else if (IsKeyDown(KEY_S) && snake[0].speed.y != -(float)SQUARE_SIDE){   
                snake[0].speed = (Vector2){0.0f , (float)SQUARE_SIDE};
                }
            else if (IsKeyDown(KEY_SPACE)){
                snake[0].speed = (Vector2){0.0f, 0.0f}; // pause the game
                }
            

            for(int i = 0; i < snakeTail; i++) snakePosition[i] = (Vector2){snake[i].position.x, snake[i].position.y};
            BeginDrawing();
            for(int i = 0; i < snakeTail; i++){
                if(i != 0){
                    snake[i].position.x= snakePosition[i-1].x;
                    snake[i].position.y= snakePosition[i-1].y;
                    DrawRectangleV(snake[i].position, snake[i].size, DARKBLUE);
                }
                else{
                    snake[i].position.x = snake[i].position.x + snake[i].speed.x;
                    snake[i].position.y = snake[i].position.y + snake[i].speed.y;
                    if(snake[i].position.x>(screenWidth-offset.x/2)){
                        snake[i].position.x = offset.x/2;
                    }
                    else if(snake[i].position.x<offset.x/2){
                        snake[i].position.x = screenWidth-offset.x/2;
                    }
                    else if(snake[i].position.y<offset.y/2){
                        snake[i].position.y = screenHeight-offset.y/2;
                    }
                    else if(snake[i].position.y>(screenHeight-offset.y/2-30)){
                        snake[i].position.y = offset.y/2;
                    }
                    if(snake[i].position.x==food.position.x && snake[i].position.y==food.position.y){
                        snakeTail++;
                        food.isEaten = true;
                        score++;
                    }
                    DrawRectangleV(snake[i].position, snake[i].size, BLUE);
                }
            }
            for(int i = 1; i<snakeTail; i++){
                if(snake[0].position.x == snake[i].position.x && snake[0].position.y == snake[i].position.y){
                    gameRun = false;
                } 
            }

            sprintf(buffer, "Your Score: %d", score);
            printf("%f %f\n", snake[0].position.x, snake[0].position.y);
            DrawRectangleV(food.position, food.size, RED);
            DrawText(buffer, 0, 0, 10, BLACK);
            ClearBackground(WHITE);
            EndDrawing();
            }

            else{
                BeginDrawing();
                DrawText(buffer, screenWidth/2-80, screenHeight/2-20, 20, BLACK);
                DrawText("You Lose", screenWidth/2-60, screenHeight/2, 20, BLACK);
                DrawText("Press ENTER to Play Again", screenWidth/2-150, screenHeight/2+20, 20, BLACK);
                if(IsKeyDown(KEY_ENTER)){
                    gameRun = true;
                    snakeTail = 1;
                    score = 0;
                    snake[0].position = (Vector2){0.0f + offset.x/2, 0.0f + offset.y/2};
                    snake[0].speed = (Vector2){(float)SQUARE_SIDE, 0.0f};
                    }
                EndDrawing();
            }
               
    }
    return 0;
}