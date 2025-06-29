#pragma once

#include "App.h"
#include "Image.h"

class EditorScene : public AppScene
{
public:
  EditorScene(Image image);

  virtual void OnUpdate() override;
  virtual void OnEnter() override;
  virtual void OnLeave() override;

private:
  struct Image image;
};
