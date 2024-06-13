/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <random>
#include <time.h>
#include "Critter.h"
#include "Destroyer.h"
#include "Map.h"


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Critter* critters[CRITTER_COUNT]{}; //Root critters array.

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    //SetTargetFPS(60);

    srand(time(NULL));

    //Load textures after opening the window.
    const Texture2D t_critter = LoadTexture("res/10.png");
    const Texture2D t_destroyer = LoadTexture("res/9.png");

    Map map = Map();

    //Initialize the destroyer.
    Critter* destroyer = new Destroyer();
    destroyer->Spawn();
    destroyer->SetTexture(&t_destroyer);
    critters[0] = destroyer;

    //Initialize critters.
    for (int i = 1; i < CRITTER_COUNT; i++)
    {
        //Create a critter in a random location and load its texture.
        Critter* c = new Critter();
        critters[i] = c;
        c->Spawn();
        c->SetTexture(&t_critter);
    }

    //Initialize timers.
    unsigned int tick = 0;
    float timer = 1;
    Vector2 nextSpawnPos = destroyer->GetPosition();

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float delta = GetFrameTime();

        timer -= delta; //Update timer.
        bool respawn = false;
        if (timer <= 0) { timer = 1; respawn = true; } //Reset timer and allow respawning 1 dead critter.

        loop(i, 0, CRITTER_COUNT)
        {
            if (!critters[i]->IsDead()) //Update living critter.
            {
                critters[i]->Update(delta); //Update each critter (dirty flags will be cleared during update).
                map.Collisions(critters[i]);
            }
            else if (respawn) //Respawn critter.
            {
                Vector2 normal = Vector2Normalize(destroyer->GetVelocity());

                 //Get a position behind the destroyer, and far enough away that the critter won't bump into it again.
                 Vector2 pos = destroyer->GetPosition();
                 pos = Vector2Add(pos, Vector2Scale(normal, -50));
                 critters[i]->Init(pos, Vector2Scale(normal, -(float)MAX_VELOCITY));
                 nextSpawnPos = destroyer->GetPosition();
            }
            map.Reset();
        }
        //----------------------------------------------------------------------------------
        


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        loop(i, 0, CRITTER_COUNT)
        {
            critters[i]->Draw();
        }
        map.Draw();
        //cout << delta << endl;

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //Only 2 textures need to be unloaded, because only 2 were loaded in the first place.
    UnloadTexture(t_critter);
    UnloadTexture(t_destroyer);


    // De-Initialization
    //--------------------------------------------------------------------------------------   
    loop(i, 0, CRITTER_COUNT)
    {
        delete critters[i];
    }
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}