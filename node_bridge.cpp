#include <node.h>
#include <string.h>
#include "result.h"

extern "C"{
	  struct ping_result ping(char *svr, int count);
}

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;

void l2Ping(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 2) {
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(Exception::TypeError(
		String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return;
	}

	if (!args[0]->IsString() || !args[1]->IsNumber()) {
		isolate->ThrowException(Exception::TypeError(
		String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

	int count = args[1]->NumberValue();
	String::Utf8Value str(args[0]);
	ping_result res = ping( *str, count);
	Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "sent"),Number::New(isolate, res.sent));
	obj->Set(String::NewFromUtf8(isolate, "received"),Number::New(isolate, res.received));
	obj->Set(String::NewFromUtf8(isolate, "avg"),Number::New(isolate, res.average));
	args.GetReturnValue().Set(obj);

}

void init(Local<Object> exports) {
	NODE_SET_METHOD(exports, "l2ping", l2Ping);
}

NODE_MODULE(addon, init)
