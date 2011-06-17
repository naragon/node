// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SRC_NODE_TIMER_H_
#define SRC_NODE_TIMER_H_

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <ev.h>

namespace node {

class Timer : ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);

 protected:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;

  Timer() : ObjectWrap() {
    // dummy timeout values
    ev_timer_init(&watcher_, OnTimeout, 0., 1.);
    watcher_.data = this;
  }

  ~Timer();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> Start(const v8::Arguments& args);
  static v8::Handle<v8::Value> Stop(const v8::Arguments& args);
  static v8::Handle<v8::Value> Again(const v8::Arguments& args);
  static v8::Handle<v8::Value> RepeatGetter(v8::Local<v8::String> property,
                                            const v8::AccessorInfo& info);
  static void RepeatSetter(v8::Local<v8::String> property,
                           v8::Local<v8::Value> value,
                           const v8::AccessorInfo& info);

 private:
  static void OnTimeout(EV_P_ ev_timer *watcher, int revents);
  void Stop();
  ev_timer watcher_;
};

}  // namespace node
#endif  // SRC_NODE_TIMER_H_