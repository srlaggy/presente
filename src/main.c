
#include <raylib.h>
#include <math.h>

#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;
    // Frames
    int frames=0;

    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    // Load textures
    Texture2D powerups = LoadTexture("../resources/powerups.png");
    Texture2D tinta = LoadTexture("../resources/mancha.png");

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);

    // Level with textures
    lvl->texture_pw = powerups;
    lvl->texture_t = tinta;

    level_fill_random(lvl,6);
    level_powerups(lvl); // Add powerups in the level

    // Initialize state (and add enemies)
    state *sta = state_new();
    sta->flag_ink=0; // Ink powerup influence (0: without influence)
    sta->flag_speed=0; // Speed powerup influence (0: without influence)
    sta->timer_pw_ink=0; // 0 seconds with ink powerup
    sta->timer_pw_speed=0; // 0 seconds with speed powerup
    state_populate_random(lvl,sta,40);

    // Main loop
    while(!WindowShouldClose()){
        // Update powerups frames.
        frames++;
        lvl->frame_speed_health=frames%4; // 4 textures for speed and health powerup
        lvl->frame_ink=frames%2; // 2 textures for ink powerup

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta);

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);

            DrawText("Presente profe!",190,200,20,LIGHTGRAY);

        EndDrawing();

    }

    // Unload textures
    UnloadTexture(powerups);
    UnloadTexture(tinta);

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
