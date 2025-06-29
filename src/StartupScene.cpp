#include <string>

#include "StartupScene.h"
#include "EditorScene.h"
#include "raylib.h"
#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_window_file_dialog.h"

static GuiWindowFileDialogState fileDialogState;
static Image image;

void StartupScene::OnUpdate()
{
  if (fileDialogState.SelectFilePressed)
  {
    if (IsFileExtension(fileDialogState.fileNameText, ".png"))
    {
      strcpy(fileNameToLoad, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
      image = LoadImage(fileNameToLoad);
      fileSelected = true;
    }
    fileDialogState.SelectFilePressed = false;
  }
  if (fileDialogState.windowActive)
    GuiLock();

  if (GuiButton({10, 10, 100, 30}, GuiIconText(ICON_FILE_OPEN, "Open Image")))
    fileDialogState.windowActive = true;
  if (fileSelected)
  {
    DrawText(std::string("Selected: " + std::string(fileNameToLoad)).c_str(), 30, 100, 15, BLACK);
  }
  int BtnHeight = GetScreenHeight() - 50;
  int BtnMid = GetScreenWidth() / 2;
  if (GuiButton((Rectangle){BtnMid - 150, BtnHeight, 100, 40}, "Open Image"))
  {
    if (fileSelected)
    {
      App::SwitchScenes<EditorScene>(image);
    }
  }


  //Text-Input
  if (IsKeyPressed(KEY_TAB)) {
      editWidth = !editWidth;
      editHeight = !editHeight;
  }

  GuiTextBox((Rectangle){300, 30, 50, 30}, newFileWidth, 10, editWidth);
  GuiTextBox((Rectangle){400, 30, 50, 30}, newFileHeight, 10, editHeight);


  //Open-Buttons
  if (GuiButton((Rectangle){BtnMid + 50, BtnHeight, 100, 40}, "Open New"))
  {
    Image newImage;
    newImage.width = atoi(newFileWidth);
    newImage.height = atoi(newFileHeight);
    newImage.format = 4;
    newImage.mipmaps = 1;
    App::SwitchScenes<EditorScene>(newImage);
  }

  GuiUnlock();

  GuiWindowFileDialog(&fileDialogState);
  fileDialogState.windowBounds.x = 0;
  fileDialogState.windowBounds.y = 0;
}
void StartupScene::OnEnter()
{
  fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
}
void StartupScene::OnLeave() {}
