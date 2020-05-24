#include "draw.h"

#include <raylib.h>

void draw_level(const level *lvl){
    // Draw cells, iterate, including borders outside the level
    for(int y=-1;y<=lvl->size_y;y++){
        for(int x=-1;x<=lvl->size_x;x++){
            char cell = level_get(lvl,x,y);
            // If the cell is a wall, paint it
            if(cell=='#'){
                DrawRectangle(TILE_SIZE*x,TILE_SIZE*y,TILE_SIZE,TILE_SIZE,BROWN);
            }
            //Draw powerups
            if(cell=='H'){
                Vector2 position = {TILE_SIZE*x,TILE_SIZE*y};
                Rectangle f_health = {336 + lvl->frame_speed_health*48, 720, 48, 48};
                DrawTextureRec(lvl->texture_pw, f_health, position, RAYWHITE);
            }
            if(cell=='I'){
                Vector2 position = {TILE_SIZE*x,TILE_SIZE*y};
                Rectangle f_ink = {480 + lvl->frame_ink*48, 384, 48, 48};
                DrawTextureRec(lvl->texture_pw, f_ink, position, RAYWHITE);
            }
            if(cell=='S'){
                Vector2 position = {TILE_SIZE*x,TILE_SIZE*y};
                Rectangle f_speed = {lvl->frame_speed_health*48, 192, 48, 48};
                DrawTextureRec(lvl->texture_pw, f_speed, position, RAYWHITE);
            }
        }
    }
}

void draw_state(const level *lvl, state *sta){

    // Initialize a camera to be used as drawing context
    Camera2D cam;
    // make the camera follow the player
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    // make it so that the player is in the middle of the screen
    cam.offset.x = GetScreenWidth()/2.0;
    cam.offset.y = GetScreenHeight()/2.0;
    // set the camera rotation to 0
    cam.rotation = 0.0;
    // set the camera zoom to 1
    cam.zoom = 1.0;

    // Draw everything relative to the camera from now on
    BeginMode2D(cam);

    // Draw level
    draw_level(lvl);

    // Draw enemies
    for(int i=0;i<sta->n_enemies;i++){
        // Get a copy of the enemy entity
        entity ent = sta->enemies[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity, color depends on the enemy type
        if(sta->enemies[i].kind == MINION){
            DrawCircleV(vec,ent.rad,YELLOW);
        }else{
            DrawCircleV(vec,ent.rad,RED);
        }
    }

    // Draw player
    {
        // Get a copy of the player's entity
        entity ent = sta->pla.ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity
        DrawCircleV(vec,ent.rad,BLUE);
    }

    // Draw bullets
    for(int i=0;i<sta->n_bullets;i++){
        // Get a copy of the bullet entity
        entity ent = sta->bullets[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity
        DrawCircleV(vec,ent.rad,PINK);
    }

    // Stop drawing relative to the camera
    EndMode2D();

    // Draw ink in position player if flag is activated
    if(sta->flag_ink==1){
        DrawTexture(lvl->texture_t, (800/2)-(lvl->texture_t.width/2), (600/2)-(lvl->texture_t.height/2), WHITE);
        // Ink powerup causes effects for 10 secs
        if((GetTime()-sta->timer_pw_ink)>10) sta->flag_ink=0;
    }
}
