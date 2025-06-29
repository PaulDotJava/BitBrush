#include <string>

#include "StartupScene.h"
#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_window_file_dialog.h"

GuiWindowFileDialogState fileDialogState;
Image image;

void StartupScene::OnUpdate(){
  if (fileDialogState.SelectFilePressed) {
    if (IsFileExtension(fileDialogState.fileNameText, ".png")) {
      strcpy(fileNameToLoad, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
      image = LoadImage(fileNameToLoad);
      fileSelected = true;
    }
    fileDialogState.SelectFilePressed = false;
  }
  if (fileDialogState.windowActive) GuiLock();

  if (GuiButton({ 10, 10, 100, 30 }, GuiIconText(ICON_FILE_OPEN, "Open Image"))) fileDialogState.windowActive = true;
  if (fileSelected) {
    DrawText(std::string("Selected: " + std::string(fileNameToLoad)).c_str(), 30, 100, 15, BLACK);
  }
  int BtnHeight = GetScreenHeight() - 50;
  int BtnMid = GetScreenWidth() / 2;
  if(GuiButton((Rectangle){BtnMid - 150, BtnHeight, 100, 40}, "Open Image")) {
    if (fileSelected) {
      //Open Editor with Image
    }
  }

  if(GuiButton((Rectangle){BtnMid + 50, BtnHeight, 100, 40}, "Open New")) {
    //Open Editor with empty Image
  }

  GuiUnlock();

  GuiWindowFileDialog(&fileDialogState);
  fileDialogState.windowBounds.x = 0;
  fileDialogState.windowBounds.y = 0;
}
void StartupScene::OnEnter(){
  fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
}
void StartupScene::OnLeave(){}