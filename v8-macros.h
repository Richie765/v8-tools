#ifndef __V8_MACROS_H
#define __V8_MACROS_H

/*

v8-macros.h

These macros can help to make your code work with multiple v8 versions.

This version is not yet fully tested but should work generally.

For the latest version see:

https://github.com/Richie765/v8-tools

*/

// First v8 version that uses "SetWeak" and not "MakeWeak"

#define V8_SETWEAK_VERSION 0x032224

#if (V8_VERSION < 0x031803)
    #define V8_STRING_NEW2(cstr, len) v8::String::New(cstr, len)
#else
    #define V8_STRING_NEW2(cstr, len) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), cstr, v8::String::kNormalString, len)
#endif

#if (V8_VERSION < 0x031903)
    typedef v8::Handle<v8::Value> SwigV8ReturnValue;
    typedef v8::Arguments SwigV8Arguments;
    typedef v8::AccessorInfo SwigV8PropertyCallbackInfo;
    #define V8_RETURN(val) return scope.Close(val)
    #define V8_RETURN_INFO(val, info) return scope.Close(val)
#else
    typedef void SwigV8ReturnValue;
    typedef v8::FunctionCallbackInfo<v8::Value> SwigV8Arguments;
    typedef v8::PropertyCallbackInfo<v8::Value> SwigV8PropertyCallbackInfo;
    #define V8_RETURN(val) args.GetReturnValue().Set(val); return
    #define V8_RETURN_INFO(val, info) info.GetReturnValue().Set(val); return
#endif

#if (V8_VERSION < 0x032117)
    #define V8_HANDLESCOPE() v8::HandleScope scope
    #define V8_HANDLESCOPE_ESC() v8::HandleScope scope
    #define V8_ESCAPE(val) return scope.Close(val)
#elif (V8_VERSION < 0x032224)
    #define V8_HANDLESCOPE() v8::HandleScope scope(v8::Isolate::GetCurrent());
    #define V8_HANDLESCOPE_ESC() v8::HandleScope scope(v8::Isolate::GetCurrent());
    #define V8_ESCAPE(val) return scope.Close(val)
#else
    #define V8_HANDLESCOPE() v8::HandleScope scope(v8::Isolate::GetCurrent());
    #define V8_HANDLESCOPE_ESC() v8::EscapableHandleScope scope(v8::Isolate::GetCurrent());
    #define V8_ESCAPE(val) return scope.Escape(val)
#endif

#if (V8_VERSION < 0x032224)
    #define V8_ADJUST_MEMORY(size) v8::V8::AdjustAmountOfExternalAllocatedMemory(size)
    #define V8_CURRENT_CONTEXT() v8::Context::GetCurrent()
    #define V8_THROW_EXCEPTION(err) v8::ThrowException(err)
    #define V8_STRING_NEW(str) v8::String::New(str)
    #define V8_SYMBOL_NEW(sym) v8::String::NewSymbol(sym)
#else
    #define V8_ADJUST_MEMORY(size) v8::Isolate::GetCurrent()->AdjustAmountOfExternalAllocatedMemory(size)
    #define V8_CURRENT_CONTEXT() v8::Isolate::GetCurrent()->GetCurrentContext()
    #define V8_THROW_EXCEPTION(err) v8::Isolate::GetCurrent()->ThrowException(err)
    #define V8_STRING_NEW(str) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str)
    #define V8_SYMBOL_NEW(sym) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), sym)
#endif

#if (V8_VERSION < 0x032318)
    #define V8_ARRAY_NEW() v8::Array::New()
    #define V8_BOOLEAN_NEW(bool) v8::Boolean::New(bool)
    #define V8_EXTERNAL_NEW(val) v8::External::New(val)
    #define V8_FUNCTEMPLATE_NEW(func) v8::FunctionTemplate::New(func)
    #define V8_FUNCTEMPLATE_NEW_VOID() v8::FunctionTemplate::New()
    #define V8_INT32_NEW(num) v8::Int32::New(num)
    #define V8_INTEGER_NEW(num) v8::Integer::New(num)
    #define V8_INTEGER_NEW_UNS(num) v8::Integer::NewFromUnsigned(num)
    #define V8_NUMBER_NEW(num) v8::Number::New(num)
    #define V8_OBJECT_NEW() v8::Object::New()
    #define V8_UNDEFINED() v8::Undefined()
    #define V8_NULL() v8::Null()
#else
    #define V8_ARRAY_NEW() v8::Array::New(v8::Isolate::GetCurrent())
    #define V8_BOOLEAN_NEW(bool) v8::Boolean::New(v8::Isolate::GetCurrent(), bool)
    #define V8_EXTERNAL_NEW(val) v8::External::New(v8::Isolate::GetCurrent(), val)
    #define V8_FUNCTEMPLATE_NEW(func) v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), func)
    #define V8_FUNCTEMPLATE_NEW_VOID() v8::FunctionTemplate::New(v8::Isolate::GetCurrent())
    #define V8_INT32_NEW(num) v8::Int32::New(v8::Isolate::GetCurrent(), num)
    #define V8_INTEGER_NEW(num) v8::Integer::New(v8::Isolate::GetCurrent(), num)
    #define V8_INTEGER_NEW_UNS(num) v8::Integer::NewFromUnsigned(v8::Isolate::GetCurrent(), num)
    #define V8_NUMBER_NEW(num) v8::Number::New(v8::Isolate::GetCurrent(), num)
    #define V8_OBJECT_NEW() v8::Object::New(v8::Isolate::GetCurrent())
    #define V8_UNDEFINED() v8::Undefined(v8::Isolate::GetCurrent())
    #define V8_NULL() v8::Null(v8::Isolate::GetCurrent())
#endif

#if (V8_VERSION < 0x031710)
    #define V8_SET_CLASS_TEMPL(class_templ, class) class_templ = v8::Persistent<v8::FunctionTemplate>::New(class);
#elif (V8_VERSION < 0x031900)
    #define V8_SET_CLASS_TEMPL(class_templ, class) class_templ = v8::Persistent<v8::FunctionTemplate>::New(v8::Isolate::GetCurrent(), class);
#else
    #define V8_SET_CLASS_TEMPL(class_templ, class) class_templ.Reset(v8::Isolate::GetCurrent(), class);
#endif

#endif // __V8_MACROS_H
