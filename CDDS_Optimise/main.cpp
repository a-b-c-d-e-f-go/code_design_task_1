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
    const int screenWidth = Map::SCREEN_WIDTH;
    const int screenHeight = Map::SCREEN_HEIGHT;

    //Const variables for initializing critters.
    const int CRITTER_COUNT = Map::NODE_CAPACITY;
    const int MAX_VELOCITY = 80;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(60);

    srand(time(NULL));

    //Load textures after opening the window.
    const Texture2D t_critter = LoadTexture("res/10.png");
    const Texture2D t_destroyer = LoadTexture("res/9.png");

    Map map = Map();

    //Initialize the destroyer.
    Critter* destroyer = new Destroyer();
    destroyer->Spawn(screenWidth, screenHeight, MAX_VELOCITY);
    destroyer->SetTexture(&t_destroyer);
    map.Add(destroyer);

    //Initialize critters.
    for (int i = 1; i < CRITTER_COUNT; i++)
    {
        //Create a critter in a random location and load its texture.
        Critter* c = new Critter();
        c->Spawn(screenWidth, screenHeight, MAX_VELOCITY);
        c->SetTexture(&t_critter);
        map.Add(c);
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

        map.Update(delta);
        //for (int i = 0; i < CRITTER_COUNT; i++)
        //{
        //    if (!critters[i]->IsDead())
        //    {
        //        critters[i]->Update(delta); //Update each critter (dirty flags will be cleared during update).
        //        critters[i]->WallBounce(screenWidth, screenHeight); //Check each critter against screen bounds.
        //        //Loop through all other critters.
        //        for (int j = 0; j < CRITTER_COUNT; j++) {
        //            if (i != j && !critters[i]->IsDirty() && !critters[j]->IsDead()) // note: the other critter (j) could be dirty - that's OK
        //            {
        //                //Check every critter against every other critter.
        //                if (critters[i]->Collides(critters[j]))
        //                {
        //                    //Break the second loop on collision (still looping through i).
        //                    critters[i]->OnCollide(critters[j], MAX_VELOCITY);
        //                    break;
        //                }
        //            }
        //        }
        //    }
        //}

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

            //Find any dead critters and spit them out (respawn).

            //for (int i = 0; i < CRITTER_COUNT; i++)
            //{
            //    if (critters[i]->IsDead())
            //    {
            //        Vector2 normal = Vector2Normalize(destroyer->GetVelocity());

            //        // get a position behind the destroyer, and far enough away that the critter won't bump into it again
            //        Vector2 pos = destroyer->GetPosition();
            //        pos = Vector2Add(pos, Vector2Scale(normal, -50));
            //        critters[i]->Init(pos, Vector2Scale(normal, -MAX_VELOCITY));
            //        break;
            //    }
            //}
            nextSpawnPos = destroyer->GetPosition();
        }
        //----------------------------------------------------------------------------------
        


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        map.Draw();

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //Only 2 textures need to be unloaded, because only 2 were loaded in the first place.
    UnloadTexture(t_critter);
    UnloadTexture(t_destroyer);


    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}