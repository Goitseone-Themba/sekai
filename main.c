#include "raylib.h"
#include <stdio.h>

typedef struct {
  int id;
  char *type;
  char *name;
  int posX;
  int posY;
  int radius;
} Base;

int main(void) {

  Base kami = {0, "Entity", "Kami", 100, 100, 50};
  Base ent1 = {1, "Entity", "Musashi Miamoto", 200, 200, 40};
  Base ent2 = {2, "Entity", "Satoshi Nakamoto", 300, 300, 30};
  Base art1 = {3, "Artefact", "Fuji", 400, 400, 45};

  Base sekai[4] = {kami, art1, ent1, ent2};

  for (int i = 0; i < 4; i++) {
    printf("ID: %d\nType: %s\n", sekai[i].id, sekai[i].type);
  }

  InitWindow(800, 450, "Sekai");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Sekai", 10, 10, 20, DARKGRAY);

    for (int i = 0; i < 4; i++) {
      DrawCircle(sekai[i].posX, sekai[i].posY, sekai[i].radius, RED);
      DrawText(sekai[i].name, sekai[i].posX, sekai[i].posY, sekai[i].radius,
               DARKGRAY);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
