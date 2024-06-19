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
#include <time.h>
#include "Destroyer.h"
#include "Map.h"
#include <iostream>

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Critter* critters[CRITTER_COUNT]{}; //Critters array. Even though we could also access them through the map, this is faster and more convenient.

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Owen BROOKS - Code Design and Data Structures 1: Design game optimisations");

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
    critters[CRITTER_COUNT - 1] = destroyer; //Set to last item.

    //Initialize critters.
    loop(i, 0, CRITTER_COUNT - 1) //End at CRITTER_COUNT - 1 because the last one is the destroyer.
    {
        //Create a critter in a random location and load its texture.
        Critter* c = new Critter();
        critters[i] = c; //Add to the array.
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
        float delta = GetFrameTime(); //The magic number.

        timer -= delta; //Starts at 1, decreases towards zero by delta time.
        bool respawn = false; //Whether or not to respawn a dead critter.
        if (timer <= 0) { timer = 1; respawn = true; } //When the timer hits 0, reset it and allow 1 dead critter to respawn.

        map.Reset();
        loop(i, 0, CRITTER_COUNT) //Updating movement, adding critters to the collisions map, checking for collisions, and respawning critters are now all part of the same loop.
        {
            if (!critters[i]->IsDead()) //Update living critter.
            {
                map.Collisions(critters[i]); //Only adding living critters to the collision map means a lot less checks.
                critters[i]->Update(delta); //Update each critter (includes wallbouncing).
            }
            else if (respawn) //Respawn critter.
            {
                Vector2 normal = Vector2Normalize(destroyer->GetVelocity());

                 //Get a position behind the destroyer, and far enough away that the critter won't bump into it again.
                 Vector2 pos = destroyer->GetPosition();
                 pos = Vector2Add(pos, Vector2Scale(normal, -50));
                 critters[i]->Init(pos, Vector2Scale(normal, -(float)MAX_VELOCITY));
                 nextSpawnPos = destroyer->GetPosition();
                 respawn = false; //Only 1 respawn per timer.
            }
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
        //map.Draw(); //Debug only - shows the map's nodes but is performance intensive.
        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    loop(i, 0, CRITTER_COUNT) //Includes destroyer.
    {
        delete critters[i];
    }

    //Only 2 textures need to be unloaded, because only 2 were loaded in the first place.
    UnloadTexture(t_critter);
    UnloadTexture(t_destroyer);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}