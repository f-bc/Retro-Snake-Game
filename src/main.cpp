#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

Color darkgreen = {0, 73, 83, 255};
Color green = {123, 160, 91, 255};
Color teal ={0, 122, 116, 255};

int cellsize = 30;
int cellCount = 25;//25cells per column/row=>will cover an area of 750x750pixels (25x30=750)
int offset=75;//width of the border

double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime=GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool EltInDeque(Vector2 elt, deque<Vector2> deq){
    for(unsigned int i = 0; i<deq.size(); i++){
        if(Vector2Equals(deq[i],elt)){
            return true;
        }
    }
    return false;
}

class Snake{
    public:
    deque<Vector2> body ={Vector2{6,9}, Vector2{5,9}, Vector2{4,9}}; //body: deque containing every cell in the body {head, ..., tail}
    Vector2 direction ={1,0};//default is moving forward(we add 1 to x and 0 to y)
    bool addSegment=false;

    void Draw(){
        for(unsigned int i=0; i<body.size();i++){
            float x=body[i].x;
            float y=body[i].y;
            Rectangle segment = Rectangle{offset+ x*cellsize,offset+ y*cellsize, (float)cellsize, (float)cellsize};//+offset: the snake moves inside the border only
            DrawRectangleRounded(segment, 0.5, 6, darkgreen);
            //DrawRectangleRounded(Rectangle r, float roundness, int segments(nbre of line segments to be used to draw each corner: nbre high=>smoother corners), Color c)
        }
    }

    void update(){
        body.push_front(Vector2Add(body[0], direction));
        if(addSegment==true){
            addSegment=false;
        }else{
            body.pop_back();
        }
    }

    void reset(){
        body ={Vector2{6,9}, Vector2{5,9}, Vector2{4,9}} ;
        direction = {1,0};
    }
};
//We can move the snake object by removing the last cell in the collection and adding a new cell to the beginning of the collection
//when the snake eats food, we will add a new segment to the beginning of its body and not move the snake for that call 
//of the update method.  We should not move it at the same time as this can create an unnatural, jumpy appearance.
class Food{
    public:
    Vector2 pos = {5, 6};//coordinates(not pixels but cells=>row,column :5th_row,7th_column)
    Texture2D texture;

    Food(deque<Vector2> snakebody){
        Image image = LoadImage("media/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        pos = GenerateRandomPos(snakebody);
    }
    ~Food(){
        UnloadTexture(texture);
    }

    void draw() {
        DrawTexture(texture,offset+ pos.x*cellsize,offset+ pos.y*cellsize, WHITE);//texture, posx(of its top left corner) ,posy ,tint
        //white => no color filtering is applied
    }

    Vector2 GenerateRandomCell(){
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x,y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> body){
        Vector2 pos=GenerateRandomCell();
        while(EltInDeque(pos, body)){//we check if the new position is on top of the body of the snake
            pos=GenerateRandomCell();
        }
        return pos;
    }

};

class Game{
    public:
    Snake snake=Snake();
    Food food=Food(snake.body);
    bool running = true;
    int score=0;
    Sound eatSound;
    Sound wallSound;
    int bestScore=0;
    bool muted = false;
    bool started = false;

    Game(){
        InitAudioDevice();//This function initializes the audio device for playing sound in a game. This function sets up the audio system and prepares it for use in the game.
        eatSound = LoadSound("media/eat.mp3");
        wallSound = LoadSound("media/wall.mp3");
    }
    ~Game(){
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw(){
        food.draw();
        snake.Draw();
    }

    void Update(){
        if(running){
            snake.update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood(){
        if(Vector2Equals(snake.body[0], food.pos)) {
            food.pos = food.GenerateRandomPos(snake.body);
            snake.addSegment=true;
            score++;
            if(!muted) PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges(){
        if(snake.body[0].x == cellCount || snake.body[0].x==-1){//gone past the right edge || the left edge
            GameOver();
        }
        if(snake.body[0].y == cellCount || snake.body[0].y==-1){//gone past the bottom edge || the upper edge
            GameOver();
        }
    }

    void GameOver(){
        if(score > bestScore) bestScore = score;
        snake.reset();
        food.pos = food.GenerateRandomPos(snake.body);
        running=false;
        score=0;
        if(!muted) PlaySound(wallSound);
    }

    void CheckCollisionWithTail(){
        deque<Vector2> headlessbody=snake.body;
        headlessbody.pop_front();
        if(EltInDeque(snake.body[0], headlessbody)){
            GameOver();
        }
    }
};

int main(){
    cout<<"Starting The Game..."<<endl;
    InitWindow(2*offset+cellsize*cellCount, 2*offset+cellsize*cellCount,"Retro Snake");//(width, height, title)
    SetTargetFPS(60);
    
    Game game=Game();

    while(WindowShouldClose() == false){
        BeginDrawing();
        
        if(!game.started && IsKeyPressed(KEY_ENTER)){
            game.started = true;
            game.running = true;
        }//to start the game you press enter

        else if(game.started && !game.running && IsKeyPressed(KEY_ENTER)){
            game.snake.reset();
            game.food.pos = game.food.GenerateRandomPos(game.snake.body);
            game.running = true;
        }//if the game is over, to replay you press enter key

        if(game.started && eventTriggered(0.2)) game.Update();//we update the mvt of the snake every 200milliseconds(instead of inside the game loop so 60times per second) so that the mvt is visible

        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1){//&& if the snake isn't moving down(it can't change directions to the opposite direction)
            game.snake.direction={0,-1};//x+0,y-1(the origine of the axes is the top left corner of the window)
            game.running=true;
        }
        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1){
            game.snake.direction={0,1};
            game.running=true;
        }
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x !=1){
            game.snake.direction={-1,0};
            game.running=true;
        }
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1){
            game.snake.direction={1,0};
            game.running=true;
        }

        if(IsKeyPressed(KEY_L)){
            game.muted = true;
            cout << "Muted ON" << endl;
        }
        if(IsKeyPressed(KEY_S)){
            game.muted = false;
            cout << "Muted OFF" << endl;
        }

        //Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset-5,(float)offset-5,(float)cellsize*cellCount+10,(float)cellsize*cellCount+10},5,teal);
        DrawText("Retro Snake", offset-5,20,40,teal);
        DrawText(TextFormat("Score: %i",game.score),offset-5,offset+cellsize*cellCount+10,40,teal);
        
        if(!game.started){
            const char* title = "RETRO SNAKE";
            const char* start = "Press ENTER to Start";
            const char* mute = "Press L to Mute / S to Unmute";
            
            int titleSize = 50;
            int textSize = 25;

            DrawText(title,
                (cellsize*cellCount+2*offset - MeasureText(title,titleSize))/2,
                offset,
                titleSize,
                teal);//int textWidth = MeasureText(text, fontSize); It returns the width (in pixels) of the text when drawn with that font size.

            DrawText(TextFormat("Best Score: %i", game.bestScore),
                (cellsize*cellCount+2*offset - MeasureText("Best Score: 000",textSize))/2,
                offset + 100,
                textSize,
                teal);

            DrawText(start,
                (cellsize*cellCount+2*offset - MeasureText(start,textSize))/2,
                offset + 180,
                textSize,
                DARKGREEN);

            DrawText(mute,
                (cellsize*cellCount+2*offset - MeasureText(mute,textSize))/2,
                offset + 230,
                textSize,
                DARKGREEN);
        }

        if(game.started) game.Draw();

        if(!game.running){
            const char* text = "GAME OVER!! (Press ENTER to replay)";
            int fontSize = 30;
            int textWidth = MeasureText(text, fontSize);

            DrawText(
                text,
                (cellsize * cellCount+2*offset - textWidth) / 2, // center horizontally
                (cellsize * cellCount+2*offset) / 2,             // center vertically
                fontSize,
                RED
            );
        }//if game over, shows a message
        DrawText(TextFormat("Best Score: %i",game.bestScore),offset + 300,offset + cellsize*cellCount + 10,40,teal);

        //show whether i'm muted or not
        const char* muteText = game.muted ? "MUTED" : "SOUND ON";
        int fontSize = 20;
        int textWidth = MeasureText(muteText, fontSize);// measure text width to align right
        DrawText(muteText,(cellsize * cellCount + 2*offset) - textWidth - 10, /*10px margin from right*/
                10, /*top margin*/fontSize, game.muted ? RED : DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
