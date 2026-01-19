#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum GameScreen { Splash, GamePlay, AudioControl, Credits } GameScreen;

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
  InitAudioDevice();

  Music music = LoadMusicStream("music.mp3");

  PlayMusicStream(music);

  float timePlayed = 0.0f;
  bool pause = false;

  float pan = 0.0f;
  SetMusicPan(music, pan);

  float volume = 0.8f;
  SetMusicVolume(music, volume);

  int frameCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    UpdateMusicStream(music);

    // get normalized time played for current music stream
    timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);

    if (timePlayed > 1.0f) {
      timePlayed = 1.0f;
    }

    if (IsKeyPressed(KEY_M)) {
      currentScreen = AudioControl;
    }

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
        printf("%s: %d\n", sekai[i].name, sekai[i].lifeSpan);

        if (sekai[i].lifeSpan <= 0) {
          color = GRAY;
          nameColor = DARKGRAY;
        }
        DrawCircle(sekai[i].posX, sekai[i].posY, sekai[i].radius, color);
        DrawText(sekai[i].name, sekai[i].posX, sekai[i].posY, sekai[i].radius,
                 nameColor);
      }

    } break;
    case AudioControl: {
      ClearBackground(RAYWHITE);

      if (IsKeyPressed(KEY_CAPS_LOCK)) {
        currentScreen = GamePlay;
      }

      if (IsKeyPressed(KEY_SPACE)) {
        StopMusicStream(music);
        PlayMusicStream(music);
      }

      if (IsKeyPressed(KEY_P)) {
        pause = !pause;

        if (pause) {
          PauseMusicStream(music);
        } else {
          ResumeMusicStream(music);
        }
      }

      if (IsKeyDown(KEY_LEFT)) {
        pan -= 0.05f;

        if (pan < -1.0f) {
          pan = -1.0f;
        }

        SetMusicPan(music, pan);
      } else if (IsKeyDown(KEY_RIGHT)) {
        pan += 0.05f;
        if (pan > 1.0f) {
          pan = 1.0f;
        }

        SetMusicPan(music, pan);
      }

      if (IsKeyDown(KEY_DOWN)) {
        volume -= 0.05f;

        if (volume < 0.0f) {
          volume = 0.0f;
        }

        SetMusicVolume(music, volume);

      } else if (IsKeyDown(KEY_UP)) {

        volume += 0.05f;

        if (volume > 1.0f) {
          volume = 1.0f;
        }

        SetMusicVolume(music, volume);
      }

      DrawText("LEFT-RIGHT for PAN CONCROL", 320, 74, 10, DARKBLUE);
      DrawRectangle(300, 100, 200, 12, LIGHTGRAY);
      DrawRectangleLines(300, 100, 200, 12, GRAY);
      DrawRectangle((int)(300 + (pan + 1.0f) / 2.0f * 200 - 5), 92, 10, 28,
                    DARKGRAY);

      DrawRectangle(200, 200, 400, 12, LIGHTGRAY);
      DrawRectangle(200, 200, (int)(timePlayed * 400.0f), 12, MAROON);
      DrawRectangleLines(200, 200, 400, 12, GRAY);

      DrawText("PRESS SPACE TO RESTART MUSIC", 215, 250, 20, LIGHTGRAY);
      DrawText("PRESS P TO PAUSE/RESUME MUSIC", 208, 280, 20, LIGHTGRAY);

      DrawText("UP-DOWN for VOLUME CONTROL", 320, 334, 10, DARKGREEN);
      DrawRectangle(300, 360, 200, 12, LIGHTGRAY);
      DrawRectangleLines(300, 360, 200, 12, GRAY);
      DrawRectangle((int)(300 + volume * 200 - 5), 352, 10, 28, DARKGRAY);

    } break;
    default:
      break;
    }

    EndDrawing();
  }

  UnloadMusicStream(music);

  CloseAudioDevice();

  CloseWindow();

  return 0;
}
