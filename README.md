#CEGUI Android Test Project
    
## Building instructions
1. Before continuing make sure you have completed [this guide](https://github.com/ironsteel/cegui/blob/android-port/README.md)
2. Clone [this repo](https://github.com/ironsteel/cegui-android-test)
3. Before downloading the android sdk make sure you have installed openjdk 1.6 and apache ant. Use your distros package manager
4. Download android sdk for linux from [this link](http://dl.google.com/android/android-sdk_r21.0.1-linux.tgz)
5. Extract the archive in your home dir and run the *android* executable from the *tools* directory in the sdk
6. The android sdk manager should pop up. Check the Android SDK Tools and Android SDK Platform tools packages.
7. Find the Android 4.0.3 (API 15) platform entry and select SDK Platform and ARM EABI v7a System image.
8. Click on install packages and wait for the installation.
9. Open your bashrc/profile file and add the root dir of the sdk, platform tools dir and tools dir to your $PATH env var.
10. Run the android sdk manager once again and click on Tools menu -> Manage AVDs.
11. The emulator manager will pop up, click on the new button. Name your emulator, select your screen size, select android 4.0.3 target.
    Make sure CPU/ABI is armeabi-v7a.
12. Enter some values for internal storage and sdcard size (for example 400mb). Click on the Use Host GPU option end hit OK.
13. Run the emulator and while still booting proceed to 14 :)
14. Using a terminal go to the dir of the cegui test project in  jni dir. From there run the *build.sh* script to build the c++ code.
15. If everythig was successful and the emulator has finished booting run the *run.sh* script.
16. After the script finishes successfuly go to the emulator and you should se a gray window named GLES1 Test with a button in it :)
17. Email me if you have any problems or suggestions.
18. Have a brake (drink a coffee or something :D) 
    
