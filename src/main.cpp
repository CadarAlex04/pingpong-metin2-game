#include <raylib.h>
#include <iostream>



using namespace std;

int player1_score = 0 ;
int player2_score = 0;

Texture2D player1_skin;
Texture2D player2_skin;


class Ball{
    public:
    float x,y;
    int speed_x, speed_y;
    int radius;


void Draw(){
    DrawCircle(x,y,radius,WHITE);
}

void Update(){

    x += speed_x;
    y += speed_y;


    if ( y +radius >=GetScreenHeight() || y-radius <=0)
    {
        speed_y *= -1;
    };

    if(x+radius>=GetScreenWidth() )
    {
        player1_score ++;
        ResetBall();

    }
    
    
    if (x-radius<=0)
    {
        player2_score ++;
        ResetBall();
    };
};

void ResetBall()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = {-1,1};
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y *= speed_choices[GetRandomValue(0,1)];
}

};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }

        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
    Rectangle sourceRec = {0.0f, 0.0f, (float)player1_skin.width, (float)player1_skin.height}; // întreaga imagine
    Rectangle destRec = {x, y, width, height}; // 25 x 120
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(player1_skin, sourceRec, destRec, origin, 0.0f, WHITE);    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }

        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
 
        }

        LimitMovement();
    }
};



class Paddle2: public Paddle{

    public: 

    void Update(){
          if (IsKeyDown(KEY_W)) {
            y -= speed;
        }

        if (IsKeyDown(KEY_S)) {
            y += speed;
        }

        LimitMovement();
        
    };

    void Draw() {
    Rectangle sourceRec = {0.0f, 0.0f, (float)player2_skin.width, (float)player2_skin.height}; // întreaga imagine
    Rectangle destRec = {x, y, width, height}; // 25 x 120
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(player2_skin, sourceRec, destRec, origin, 0.0f, WHITE);
}

};
//clase
Ball ball;
Paddle Player1;
Paddle2 Player2;

int main() 
{

cout << "Metin2 PingPong" << endl;
const int screen_width=1280;
const int screen_height=800;
InitWindow( screen_width, screen_height, "Metin2 ping pong");
SetTargetFPS(80);

//music
InitAudioDevice();
Music metin2Music = LoadMusicStream("assets/metin2m.mp3");
PlayMusicStream(metin2Music);
SetMusicVolume(metin2Music, 0.5f);
metin2Music.looping= true;


Texture2D background = LoadTexture("assets/metin.jpg");
 player1_skin = LoadTexture("assets/war.png");
 player2_skin = LoadTexture("assets/ninja.jpg");


ball.radius=20;
ball.x=screen_width/2;
ball.y=screen_height/2;
ball.speed_x=7;
ball.speed_y=7;


Player1.width=25;
Player1.height=120;
Player1.x = screen_width - Player1.width -10;
Player1.y=screen_height/2 - Player1.height/2;
Player1.speed=10;


Player2.height = 120;
Player2.width= 25;
Player2.x = 10;
Player2.y=screen_height/2-Player2.height/2;
Player2.speed = 10;



while (WindowShouldClose()==false){
BeginDrawing();
UpdateMusicStream(metin2Music);

//updates
ball.Update();
Player1.Update();
Player2.Update();


//collisions
if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{Player1.x, Player1.y, Player1.width, Player1.height} ))
{
    ball.speed_x *= -1;
}
if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{Player2.x, Player2.y, Player2.width, Player2.height} ))
{
    ball.speed_x *= -1;
}



//drawing elements
DrawTexture(background, 0 ,0 , WHITE);
DrawLine(screen_width / 2 ,0, screen_width /2, screen_height, WHITE);
ball.Draw();
Player1.Draw();
Player2.Draw();
DrawText(TextFormat("%i",player1_score), screen_width/4-20, 20, 80, WHITE);
DrawText(TextFormat("%i",player2_score), 3*screen_width/4-20, 20, 80, WHITE);

//textures
if (player1_skin.id == 0) cout << "Player1 skin failed to load!" << endl;
if (player2_skin.id == 0) cout << "Player2 skin failed to load!" << endl;
if (background.id == 0) cout << "Failed to load background!" << endl;
if (metin2Music.stream.buffer == 0) cout << "Failed to load music!" << endl;

EndDrawing();
}
UnloadTexture(background);
UnloadTexture(player1_skin);
UnloadTexture(player2_skin);
StopMusicStream(metin2Music);
UnloadMusicStream(metin2Music);
CloseAudioDevice();
CloseWindow();

    return 0;
}