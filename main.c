#include "raylib.h"
#include <stdio.h>

typedef enum GameScreen { Splash, GamePlay, Credits } GameScreen;

typedef struct {
  int posX;
  int posY;
  int fontSize;
  char *text;
} Text;

typedef struct {
  int id;
  char *type;
  char *name;
  int posX;
  int posY;
  int radius;
  int lifeSpan;
} Base;

int main(void) {

  int screenWidth = 800;
  int screenHeight = 450;
  Text title = {10, 10, 20, "Sekai"};
  Text splash = {320, 180, 48, "Loading..."};

  GameScreen currentScreen = Splash;

  Base kami = {0, "Entity", "Kami", 100, 100, 50, 800};
  Base ent1 = {1, "Entity", "Musashi Miamoto", 200, 200, 40, 300};
  Base ent2 = {2, "Entity", "Satoshi Nakamoto", 300, 300, 30, 200};
  Base art1 = {3, "Artefact", "Fuji", 400, 400, 45, 500};

  Base sekai[4] = {kami, art1, ent1, ent2};

  InitWindow(screenWidth, screenHeight, title.text);

  int frameCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    switch (currentScreen) {
    case Splash: {
      frameCounter = frameCounter + 2;
      if (frameCounter > 250) {
        currentScreen = GamePlay;
      }
    } break;
    default:
      break;
    }
    BeginDrawing();
    switch (currentScreen) {
    case Splash: {
      ClearBackground(RAYWHITE);
      DrawText(splash.text, splash.posX, splash.posY, splash.fontSize,
               DARKGRAY);
      DrawRectangle(300, 400, frameCounter, 10, GREEN);
    } break;
    case GamePlay: {

      ClearBackground(RAYWHITE);
      DrawText(title.text, title.posX, title.posY, title.fontSize, DARKGRAY);

      for (int i = 0; i < 4; i++) {
        sekai[i].lifeSpan--;
        Color color = RED;
        Color nameColor = GRAY;
        printf("%s: %d\n",sekai[i].name, sekai[i].lifeSpan);

        if (sekai[i].lifeSpan <= 0) {
          color = GRAY;
          nameColor = DARKGRAY;
        }
        DrawCircle(sekai[i].posX, sekai[i].posY, sekai[i].radius, color);
        DrawText(sekai[i].name, sekai[i].posX, sekai[i].posY, sekai[i].radius,
                 nameColor);
      }

    } break;
    default:
      break;
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
