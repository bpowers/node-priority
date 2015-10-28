// Copyright 2015 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <nan.h>

using v8::FunctionTemplate;


NAN_METHOD(Get) {
	if (info.Length() != 3) {
		Nan::ThrowError("getpriority requires 3 args");
		return;
	}
	if (!info[0]->IsNumber()) {
		Nan::ThrowError("getpriority requires a number for its first (`which`) arg");
		return;
	}
	if (!info[1]->IsNumber()) {
		Nan::ThrowError("getpriority requires a number for its second (`who`) arg");
		return;
	}
	if (!info[2]->IsFunction()) {
		Nan::ThrowError("getpriority requires a callback as its third arg");
		return;
	}

	int which = info[0]->Int32Value();
	int who = info[1]->Int32Value();
	v8::Local<v8::Function> cb = info[2].As<v8::Function>();

	// since getpriority can legitimately return -1, we need to
	// clear errno and check it upon return.
	errno = 0;
	int priority = getpriority(which, who);
	if (priority == -1 && errno) {
		v8::Local<v8::Value> jsErr = Nan::New(errno);
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 1, &jsErr);
		return;
	}

	v8::Local<v8::Value> results[2];
	results[0] = Nan::Undefined();
	results[1] = Nan::New(priority);

	Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 2, results);
}

NAN_METHOD(Set) {
	if (info.Length() != 4) {
		Nan::ThrowError("setpriority requires 4 args");
		return;
	}
	if (!info[0]->IsNumber()) {
		Nan::ThrowError("setpriority requires a number for its first (`which`) arg");
		return;
	}
	if (!info[1]->IsNumber()) {
		Nan::ThrowError("setpriority requires a number for its second (`who`) arg");
		return;
	}
	if (!info[2]->IsNumber()) {
		Nan::ThrowError("setpriority requires a number for its third (`prio`) arg");
		return;
	}
	if (!info[3]->IsFunction()) {
		Nan::ThrowError("setpriority requires a callback as its fourth arg");
		return;
	}

	int which = info[0]->Int32Value();
	int who = info[1]->Int32Value();
	int prio = info[2]->Int32Value();
	v8::Local<v8::Function> cb = info[3].As<v8::Function>();

	int priority = setpriority(which, who, prio);
	if (priority != 0) {
		// FIXME: provide more detail
		v8::Local<v8::Value> jsErr = Nan::New("setpriority failed").ToLocalChecked();
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 1, &jsErr);
		return;
	}

	v8::Local<v8::Value> result = Nan::Undefined();

	Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 1, &result);
}

NAN_MODULE_INIT(Init) {
	Nan::Set(target, Nan::New("get").ToLocalChecked(),
		 Nan::GetFunction(Nan::New<FunctionTemplate>(Get)).ToLocalChecked());
	Nan::Set(target, Nan::New("set").ToLocalChecked(),
		 Nan::GetFunction(Nan::New<FunctionTemplate>(Set)).ToLocalChecked());

	// constants
	Nan::Set(target, Nan::New("Process").ToLocalChecked(), Nan::New((int)PRIO_PROCESS));
	Nan::Set(target, Nan::New("Pgrp").ToLocalChecked(), Nan::New((int)PRIO_PGRP));
	Nan::Set(target, Nan::New("User").ToLocalChecked(), Nan::New((int)PRIO_USER));
}

NODE_MODULE(priority, Init)
