#pragma once

#include "App.h"
#include "Image2D.h"

class EditorScene : public AppScene
{
public:
  EditorScene(Image2D image);

  virtual void OnUpdate() override;
  virtual void OnEnter() override;
  virtual void OnLeave() override;

private:
  struct Image2D image;
};
