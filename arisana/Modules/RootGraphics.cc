#include "arisana/Modules/RootGraphics.hh"
#include "TApplication.h"
#include "TSystem.h"
#include <iostream>
#include <cmath>

//#include "TEnv.h"

arisana::RootGraphics::RootGraphics() : thread(RootGraphics::ThreadEntryPoint,this),
                               pause(true), quit(false), mutex()
{
  if(!gApplication){
    TApplication* app = new TApplication("app",0,0);
    app->SetReturnFromRun(kTRUE);
    
  }
}

arisana::RootGraphics::RootGraphics(bool TApp) : 
    thread(RootGraphics::ThreadEntryPoint,this),
    pause(true), quit(false), mutex()
{
    if(TApp && !gApplication)
    {
	TApplication* app = new TApplication("app",0,0);
	app->SetReturnFromRun(kTRUE);
    }
}

void  arisana::RootGraphics::Start()
{
  pause = false;
}

void  arisana::RootGraphics::Pause()
{
  pause = true;
}

void  arisana::RootGraphics::Stop()
{
  quit = true;
  if(thread.joinable()){
    thread.join();
  }
    
}

void*  arisana::RootGraphics::ThreadEntryPoint(void* graphics)
{
  RootGraphics* gr = (RootGraphics*)graphics;
  while(!gr->quit){
    gSystem->Sleep(100);
    if(gr->pause) continue;
    gr->mutex.lock();
    if(gSystem->ProcessEvents())
      break;
    gr->mutex.unlock();
  }
  return 0;
}

void arisana::divide_canvas(TCanvas& can, int npads){
  int width = floor(sqrt(npads*1.77));
  int height = ceil(npads/floor(sqrt(npads*1.77)));
  can.Divide(width,height);

}
