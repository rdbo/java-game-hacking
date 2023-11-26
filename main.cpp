#include "jni.h"
#include <iostream>

#define JNI_VERSION JNI_VERSION_1_8

/*
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;

	std::cout << "JNI_OnLoad called" << std::endl;
	jvm->GetEnv((void **)&env, JNI_VERSION);

	jclass main = env->FindClass("main/Main");
	printf("Main class pointer: %p\n", (void *)main);

	jfieldID myNumberID = env->GetStaticFieldID(main, "myNumber", "I");
	printf("myNumber ID address: %p\n", (void *)myNumberID);

	jint myNumber = env->GetStaticIntField(main, myNumberID);
	printf("myNumber value: %d\n", myNumber);

	env->SetStaticIntField(main, myNumberID, 1337);
	printf("changed number value\n");

	return JNI_VERSION;
}
*/

void __attribute__((constructor))
dl_entry()
{
	JavaVM *jvm;
	JNIEnv *env;
	JavaVMAttachArgs attach_args;

	std::cout << "Library loaded!" << std::endl;

	std::cout << "JNI_GetCreatedJavaVMs: " << JNI_GetCreatedJavaVMs(&jvm, 1, NULL) << std::endl;
	std::cout << "JavaVM pointer: " << (void *)jvm << std::endl;

	attach_args.version = JNI_VERSION;
	attach_args.name = nullptr;
	attach_args.group = nullptr;

	jvm->AttachCurrentThread((void **)&env, (void *)&attach_args);

	std::cout << "JNIEnv pointer: " << (void *)env << std::endl;

	jclass main = env->FindClass("main/Main");
	printf("Main class pointer: %p\n", (void *)main);

	jfieldID myNumberID = env->GetStaticFieldID(main, "myNumber", "I");
	printf("myNumber ID address: %p\n", (void *)myNumberID);

	jint myNumber = env->GetStaticIntField(main, myNumberID);
	printf("myNumber value: %d\n", myNumber);

	env->SetStaticIntField(main, myNumberID, 1337);
	printf("changed number value\n");
}
