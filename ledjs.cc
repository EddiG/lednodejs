#include <node.h>
#include <v8.h>

extern "C" {
#include "ws2812-RPi.h" 
}

using namespace v8;

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void initPWM(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  init_pwm();
}

void disposePWM(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  dispose_pwm();
}

void show(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  show();
}

void setPixel(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 4) {
    isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber() ||
      !args[2]->IsNumber() || !args[3]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  int pixel = args[0]->NumberValue();
  char r = args[1]->NumberValue();
  char g = args[2]->NumberValue();
  char b = args[3]->NumberValue();

  setPixelColor(pixel, r, g, b);
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "initPWM", initPWM);
  NODE_SET_METHOD(target, "disposePWM", disposePWM);
  NODE_SET_METHOD(target, "show", show);
  NODE_SET_METHOD(target, "setPixel", setPixel);
}

NODE_MODULE(ledjs, init);