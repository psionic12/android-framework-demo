package com.android.server;

import android.content.Context;
import android.os.ICDEService;
import android.util.Slog;

public class CDEService extends ICDEService.Stub {
	private static final String TAG = "CDEService";
	private  int mPtr = 0;

	CDEService() {
		mPtr = init_native();
	}
	public void write_mem(String mem) {
		if (mPtr == 0) {
			return;
		}
		write_mem_native(mem);

	}
	public String read_mem() {
		if (mPtr == 0) {
			return "failed";
		}
		return read_mem_native();
	}
	private static native int init_native();
	private static native void write_mem_native(String mem);
	private static  native String read_mem_native();
};