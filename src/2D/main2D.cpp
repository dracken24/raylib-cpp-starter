#include "../../myIncludes/game.hpp"
#include "../../myIncludes/class2D/squareProps.hpp"
#include "../../myIncludes/class2D/envitems.hpp"

// void	ftRoutine(Game *Game, Player *player, Camera2D *camera, SquareProps *blocks, SquareProps *platforms);

void	ftMode2D(Game *Game, Menu *menu)
{
	Player	*player;
	player = new Player;
	player->ftSetPosition((Vector2){500, 300});

	Props	blocks;
	blocks.ftInitSquareProps(5, "blocks");
	blocks.ftAddProps((Vector2){200, 200}, (Vector2){24, 24}, BLUE, true, 0, "blocks");
	blocks.ftAddProps((Vector2){160, 200}, (Vector2){24, 24}, RED, true, 1, "blocks");
	blocks.ftAddProps((Vector2){120, 200}, (Vector2){24, 24}, YELLOW, true, 2, "blocks");
	blocks.ftAddProps((Vector2){240, 200}, (Vector2){24, 24}, PINK, true, 3, "blocks");
	blocks.ftAddProps((Vector2){80, 200}, (Vector2){24, 24}, PURPLE, true, 4, "blocks");

	Texture tmp;
	EnvItems envItems;
	// envItems = new EnvItems;
	envItems.ftNewEnvItem(9);
	envItems.ftInitEnvitem((Vector2){0, 0}, (Vector2){1000, 400}, 0, LIGHTGRAY, tmp, 0);
	envItems.ftInitEnvitem((Vector2){0, 400}, (Vector2){1000, 200}, 1, GRAY, tmp, 1);
	envItems.ftInitEnvitem((Vector2){300, 150}, (Vector2){400, 10}, 1, GRAY, tmp, 2);
	envItems.ftInitEnvitem((Vector2){250, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 3);
	envItems.ftInitEnvitem((Vector2){650, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 4);
	envItems.ftInitEnvitem((Vector2){-850, 350}, (Vector2){700, 205}, 1, GRAY, tmp, 5);
	envItems.ftInitEnvitem((Vector2){1100, 380}, (Vector2){400, 13}, 1, GRAY, tmp, 6);
	envItems.ftInitEnvitem((Vector2){700, 100}, (Vector2){150, 10}, 1, GRAY, tmp, 7);
	envItems.ftInitEnvitem((Vector2){450, 500}, (Vector2){180, 15}, 1, GRAY, tmp, 8);


	// EnvItem envItems[] = {
	// 	{{0, 0, 1000, 400}, 0, LIGHTGRAY},
	// 	{{0, 400, 1000, 200}, 1, GRAY},
	// 	{{300, 150, 400, 10}, 1, GRAY},
	// 	{{250, 250, 100, 10}, 1, GRAY},
	// 	{{650, 250, 100, 10}, 1, GRAY},
	// 	{{-850, 350, 700, 205}, 1, GRAY},
	// 	{{1100, 380, 400, 13}, 1, GRAY},
	// 	{{700, 100, 150, 10}, 1, GRAY},
	// 	{{450, 500, 180, 15}, 1, GRAY}};
	// Props	plateforms;
	// plateforms.ftInitSquareProps(9, "plateforms");
	// plateforms.ftAddProps((Vector2){0, 0}, (Vector2){1000, 400}, LIGHTGRAY, false, 0, "plateforms");
	// plateforms.ftAddProps((Vector2){0, 400}, (Vector2){1000, 200}, LIGHTGRAY, true, 1, "plateforms");
	// plateforms.ftAddProps((Vector2){300, 150}, (Vector2){400, 10}, LIGHTGRAY, true, 2, "plateforms");
	// plateforms.ftAddProps((Vector2){250, 250}, (Vector2){100, 10}, LIGHTGRAY, true, 3, "plateforms");
	// plateforms.ftAddProps((Vector2){650, 250}, (Vector2){100, 10}, LIGHTGRAY, true, 4, "plateforms");
	// plateforms.ftAddProps((Vector2){-850, 350}, (Vector2){100, 10}, LIGHTGRAY, true, 5, "plateforms");
	// plateforms.ftAddProps((Vector2){1100, 380}, (Vector2){400, 13}, LIGHTGRAY, true, 6, "plateforms");
	// plateforms.ftAddProps((Vector2){700, 100}, (Vector2){150, 10}, LIGHTGRAY, true, 7, "plateforms");
	// plateforms.ftAddProps((Vector2){450, 500}, (Vector2){180, 15}, LIGHTGRAY, true, 8, "plateforms");

	//--------------------------------------------------------------------------------------//
	// Init Camera and windows
	// Camera player
	Camera2D camera = {0};
	camera.target = player->ftReturnPlayerPosition();
	camera.offset = (Vector2){Game->screenWidth / 2.0f, Game->screenHeight / 2.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	RenderTexture playing = LoadRenderTexture(Game->screenWidth - 300, Game->screenHeight);
	Rectangle splitScreenRectPlay = {0.0f, 0.0f, (float)playing.texture.width, (float)-playing.texture.height};

	// Camera panel side up
	Camera2D menuCamSideUp = {0};
	menuCamSideUp.target = {0, 0};
	menuCamSideUp.offset = (Vector2){0.0f, 0.0f};
	menuCamSideUp.rotation = 0.0f;
	menuCamSideUp.zoom = 1.0f;
	RenderTexture menuTextSideUp = LoadRenderTexture(300, Game->screenHeight / 3);
	Rectangle splitScreenRectPanSideUp = {0.0f, 0.0f, (float)menuTextSideUp.texture.width, (float)-menuTextSideUp.texture.height};

	// Camera panel side down
	Camera2D menuCamSideDown = {0};
	menuCamSideDown.target = {0, 0};
	menuCamSideDown.offset = (Vector2){0.0f, 0.0f};
	menuCamSideDown.rotation = 0.0f;
	menuCamSideDown.zoom = 1.0f;
	RenderTexture menuTextSideDown = LoadRenderTexture(300, Game->screenHeight / 3 * 2);
	Rectangle splitScreenRectPanSideDown = {0.0f, 0.0f, (float)menuTextSideDown.texture.width, (float)-menuTextSideDown.texture.height};

	// Multiple camera
	// void (*cameraUpdaters[])(Camera2D *, Player *, EnvItem *, int, float, int, int) = {
	// 	ftUpdateCameraCenter};
	Game->cameraUpdaters[0] = {ftUpdateCameraCenter};

	int cameraUpdatersLength = sizeof(1) / sizeof(Game->cameraUpdaters[0]);
	std::cout << "Help 3" << std::endl;
//--------------------------------------------------------------------------------------
	// SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		//** Drawning **//

		//Draw Play screen
		BeginTextureMode(playing);
			ClearBackground(LIGHTGRAY);
			BeginMode2D(camera);

				if (menu->ftReturnStart() == 0) // Meni intro
				{
					ftChooseMenu(menu);
					DrawTextEx(Game->font1 ,"Untitled Adventure Game", {100, 100}, 40, 2, BLACK);
					// DrawText("Untitled Adventure Game", 100, 100, 40, BLACK);
					DrawText("Choose Your Character", 100, 200, 20, DARKGRAY);
					DrawText("Start Game", 100, 250, 20, DARKGRAY);
				}
				else if (menu->ftReturnStart() == 1)// Menu choose character
				{
					ftMenuChooseCharacter(player, menu);
				}
				else // Main loop
				{
					// for (int i = 0; i < 9; i++)
					// 	DrawRectangleRec(envItems.ftReturnRectangle(i), envItems.ftReturnEnviColor(i));
					ftRoutine(Game, player, &camera, &blocks, &envItems);
				}
			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side up
		BeginTextureMode(menuTextSideUp);
			ClearBackground(DARKGRAY);
			BeginMode2D(menuCamSideUp);

				ftSideUpMenu2D(Game, player, menu);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side down
		BeginTextureMode(menuTextSideDown);
		ClearBackground(DARKGRAY2);
		BeginMode2D(menuCamSideDown);

		ftSideDownMenu2D(Game, player, menu);

		EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw both views render textures to the screen side by side
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTextureRec(playing.texture, splitScreenRectPlay, (Vector2){0, 0}, WHITE);
			DrawTextureRec(menuTextSideUp.texture, splitScreenRectPanSideUp, (Vector2){(float)Game->screenWidth - 300.0f, 0}, WHITE);
			DrawTextureRec(menuTextSideDown.texture, splitScreenRectPanSideDown, (Vector2){(float)Game->screenWidth - 300.0f, (float)Game->screenHeight / 3}, WHITE);
			ftDrawBoarders(Game);
		EndDrawing();
	}
//--------------------------------------------------------------------------------------//
	// CloseWindow();
	UnloadRenderTexture(playing);
	UnloadRenderTexture(menuTextSideUp);
	UnloadRenderTexture(menuTextSideDown);
	// blocks.ftKillSquareProps();
	delete player;
	// delete envItems;
	// delete blocks;
}

void	ftDrawBoarders(Game *Game)
{
	DrawLineEx({(float)Game->screenWidth - 302, 0}, {(float)Game->screenWidth - 302, (float)Game->screenHeight}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 2, 0}, {(float)Game->screenWidth - 2, (float)Game->screenHeight}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, (float)Game->screenHeight / 3}, {(float)Game->screenWidth, (float)Game->screenHeight / 3}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, + 2}, {(float)Game->screenWidth, + 2}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, (float)Game->screenHeight - 2}, {(float)Game->screenWidth, (float)Game->screenHeight - 2}, 5, DARKGRAY1);
}

// void	ftSideUpMenu2D(Game *Game, Player *player, Menu *menu)
// {
// 	ftMouseControl(Game, player, menu);
// }

void	ftSideDownMenu2D(Game *Game, Player *player, Menu *menu)
{
	DrawText("Test down", 10, 10, 20, BLACK);
}