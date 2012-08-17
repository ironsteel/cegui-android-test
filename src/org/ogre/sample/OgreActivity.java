package org.ogre.sample;

import android.app.NativeActivity;

public class OgreActivity extends NativeActivity {

	
	static {
		System.loadLibrary("iconv");
		System.loadLibrary("tinyxml");
		System.loadLibrary("native-activity");
	}
}
