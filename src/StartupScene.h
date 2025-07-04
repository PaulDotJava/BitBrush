#pragma once

#include "App.h"

class StartupScene: public AppScene
{
public:
  virtual void OnUpdate() override;
  virtual void OnEnter() override;
  virtual void OnLeave() override;

private:
  char fileNameToLoad[512] = { 0 };
  char newFileWidth[10] = { 0 };
  char newFileHeight[10] = { 0 };
  bool fileSelected = false;

  bool editHeight = true;
  bool editWidth = false;
};
