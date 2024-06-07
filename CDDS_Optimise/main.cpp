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
#include "QuadTree.h"


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(60);

    srand(time(NULL));

    //Load textures after opening the window.
    const Texture2D t_critter = LoadTexture("res/10.png");
    const Texture2D t_destroyer = LoadTexture("res/9.png");

    //Const variables for initializing critters.
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    //QuadTree map = QuadTree(AABB(Vector2{ 0, 0 }, Vector2{ (float)screenWidth, (float)screenHeight }));
    QuadTree map = QuadTree(AABB(Vector2{ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f }, Vector2{ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f }));
    map.Subdivide(1); //Subdivide with 1 extra recursion (the children will also subdivide, leaving us with 16 nodes).

    //Initialize the destroyer.
    Critter* destroyer = new Destroyer(); //Pointer to the destroyer.
    destroyer->Spawn(screenWidth, screenHeight, MAX_VELOCITY);
    destroyer->SetTexture(&t_destroyer);
    std::cout << "\n----------NEW DESTROYER----------\n";
    map.Add(destroyer);

    //Initialize critters.
    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        //Create a critter in a random location and load its texture.
        Critter* c = new Critter();
        c->Spawn(screenWidth, screenHeight, MAX_VELOCITY);
        c->SetTexture(&t_critter);
        std::cout << "\n----------NEW CRITTER----------\n";
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

        map.Update(delta, tick);
        tick++;
        tick %= 10000000;
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
            //        looking_for_dead = false;
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
        //Draw the critters and destroyer.
        /*for (int i = 0; i < CRITTER_COUNT; i++)
        {
            critters[i]->Draw();
        }*/

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //Cleanup
    cout << "\n----------CLEANUP----------\n";
    //Only 2 textures need to be unloaded, because only 2 were loaded in the first place.
    UnloadTexture(t_critter);
    UnloadTexture(t_destroyer);


    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}