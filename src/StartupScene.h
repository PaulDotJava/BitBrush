#pragma once

#include "App.h"

class StartupScene : public AppScene
{
public:
  virtual void OnUpdate() override;
  virtual void OnEnter() override;
  virtual void OnLeave() override;
};
