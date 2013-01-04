package uk.org.cegui;

import android.app.NativeActivity;

public class CEGUITestActivity extends NativeActivity {
	static {
		System.loadLibrary("iconv");
		System.loadLibrary("native-activity");
	}
}
