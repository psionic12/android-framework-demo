#define LOG_TAG "CDEServiceJNI"
#include "jni.h"
#include "android_runtime/AndroidRuntime.h"
#include <hardware/hardware.h>
#include <hardware/cde.h>
#include "JNIHelp.h"
#include <utils/misc.h>
#include <string.h>


cde_module_t* module = NULL;
cde_device_t* device = NULL;

namespace android
{
	static jint init(JNIEnv* env, jobject clazz) {

		if (hw_get_module("cde",(const struct hw_module_t**)&module) == 0) {
			if((module->cdev).methods->open((const struct hw_module_t*)&(module->cdev),"cde",(struct hw_device_t **)&device) == 0) {
				return 1;
			}
		}
		return 0;
	}
	static void write_mem(JNIEnv* env, jobject clazz, jstring str) {
		if (device == NULL)	
		{
			return;
		}
		const char* const_mem;
		const_mem = env->GetStringUTFChars(str, false); 
		char* mem = NULL;
		strcpy(mem,const_mem);
		device->write_mem(device,mem);
		env->ReleaseStringUTFChars(str, mem); 
	}
	static jstring read_mem(JNIEnv* env, jobject clazz) {
		if (device == NULL)	
		{
			return 0;
		}
		char* mem = NULL;
		device->read_mem(device,mem);
		return env->NewStringUTF(mem);
	}
	static const JNINativeMethod method_table[] = {
		{"init_native","()I",(void*)init},
		{"write_mem_native","(Ljava/lang/String;)V",(void*)write_mem},
		{"read_mem_native","()Ljava/lang/String;",(void*)read_mem},
	};
	int register_android_server_CDEService(JNIEnv *env) {
		return jniRegisterNativeMethods(env, "com/android/server/CDEServe", method_table, NELEM(method_table));
	}
}