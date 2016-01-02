#使用QtCreator在Windows環境中Build FreeCAD

最近更新: 2015/12/14<br />
官方教學: http://www.freecadweb.org/wiki/index.php?title=CompileOnWindows

<br />
##前言

在安裝過程中會有許多版本相容問題，因此建議依照教學中所使用相同版本來build以減少過程中產生的錯誤。<br />
(目前試過有build成功的系統環境有Windows 7、Windows 8.1以及Windows 10，其他的系統環境還有待測試)

<br />
##前置作業

1. 請clone一份最新版本的程式碼(SourceCode)到Local端做開發。<br />

2. 下載FreeCAD的Library Package解壓縮到你想放的地方，可將該資料夾名稱修改為libpack方便之後設定。<br />
注意這裡要下載和電腦中的Visual Studio以及欲開發的FreeCAD版本所相對應的package。
壓縮檔名稱中最後的數字為Visual Studio的**版本號**，而非*年份*（例如： Visual Studio **10** *2010*、Visual Studio **11** *2012*、Visual Studio **12** *2013*）。<br />
我電腦中用的是Visual Studio 2013且這次要開發的是x86版本，所以下載 [FreeCADLibs_11.0_**x86**_**VC12**.7z](http://sourceforge.net/projects/free-cad/files/FreeCAD%20LibPack/FreeCADLibs_11.1_x86_VC12.7z/download) 這個檔案。<br />
（需要其他版本則可至 [這裡](http://sourceforge.net/projects/free-cad/files/FreeCAD%20LibPack/) 選擇）<br />

3. 下載 [Cmake v3.1.1](https://cmake.org/files/v3.1/cmake-3.1.1-win32-x86.exe)，一直按下一步安裝即可，但請記得你裝在哪裡，因為後面步驟將會用到它。<br />
（也可從 [官方網站](https://cmake.org/download/) 下載最新版本）<br />

4. 下載 [doxygen v1.8.10](http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.10-setup.exe) 並安裝，記得裝好後要在環境變數的Path中加入它。<br />
（若上方連結失效可從 [官方網站](http://www.stack.nl/~dimitri/doxygen/download.html) 下載最新版本）<br />

5. 安裝python v2.7.9，但因為使用了FreeCAD libpack所以此項為非必要，因為在libpack裡面已經有包含python了，所以可以跳過這一步。<br />

6. 下載 [Qt v5.5.1](https://download.qt.io/archive/qt/5.5/5.5.1/qt-opensource-windows-x86-msvc2013-5.5.1.exe) 並安裝他。
（[官方網站](https://download.qt.io/archive/qt/5.5/5.5.1/)）<br />

7. 下載 [Windows Driver Kit 8.1](http://go.microsoft.com/fwlink/p/?LinkId=393659) ，進入後選擇「wdk\wdksetup.exe」即可，下載完成後安裝，也請記得安裝的位置。<br />
（PS1: 新版的Qt需要使用到kit，因此必須安裝這個才能繼續往下走，詳細可以參考 [官方網站](https://msdn.microsoft.com/en-us/windows/hardware/hh852365.aspx) ） <br /> 
（PS2: Windows 10可以下載[Windows driver kit 10](http://go.microsoft.com/fwlink/p/?LinkId=526733)）<br/>

<br />
##設定Qt相關參數

1. 打開Qt，選擇Tools > Options...<br />
![01_1](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/01_1.png)<br />

2. 在Text Editor中選取Behavior分頁，把File Encoding中的Default Encoding改為**ISO-8859-1 /...csISOLatin1**。<br />
![01_2](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/01_2.PNG)<br />

3. 在Build & Run中選取CMake分頁，新增CMake路徑如下圖。另外建議也新增一個CMake GUI方便之後使用。<br />
![01_3](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/01_3.PNG)<br />

4. 同樣在Build & Run中，選取Kits分頁來設定需要的Kit。設定如下圖所示，因為我們要開發x86的版本所以選擇MSVC 2013的x86版本，Debugger同樣也選擇x86版，Qt Version則設為None。
另外跟上一步一樣，建議新增一個使用CMake GUI的Kit，兩者僅在CMake Tool處選取不同的選項。<br />
![01_4](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/01_4.PNG)
![01_5](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/01_5.PNG)<br />

<br />
##使用CMake建立Qt專案

1. 選擇File > Open File or Project...，找到剛才clone的FreeCAD資料夾，打開最外層的CMakeLists.txt。<br />
![02_1](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_1.PNG)<br />

2. 選擇Build的路徑，因稍早clone的FreeCAD資料夾內已有qtbuild資料夾且該資料夾中存有日後所需的資料，因此推薦設為FreeCAD/qtbuild。（另外在qtbuild資料夾中有些資料夾內的檔案需要另外下載，詳見該資料夾內的README.md檔案）<br />
![02_2](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_2.PNG)<br />

3. Run CMake時Generator的部分選擇剛剛設定好的Kit(MSVC2013 x86)，接著按Run CMake。<br />
![02_3](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_3.PNG)<br />

4. 此時會出錯因為找不到libpack，可將上方的Generator改為先前設定的有CMake GUI的Kit(MSVC2013 x86 CMake GUI)，按下Run CMake後會開啟GUI。<br />
![02_4](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_4.PNG)<br />

5. 這裡要為Project做一些設定，首先找到CMAKE_BUILD_TYPE，將它設定為Release。<br />
![02_5](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_5.PNG)<br />

6. 接著找到FREECAD_LIBPACK_DIR將路徑設為你的libpack路徑。<br />
![02_6](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_6.PNG)<br />

7. 檢查BUILD_ROBOT與BUILD_PATH是否有勾選，預設我應該有把它關掉了，但如果他還有就把它勾掉（有這兩個的話build會出錯）。<br />

8. 按下Configure，出現成功就關掉，不要Generate。如果你的Configure一直出現找不到boost_python的錯誤，請見下方Q&A。<br />

9. 把Kit換回沒有GUI的MSVC2013 x86，按Run CMake，這次應該會成功了，接著按Finish就會出現Qt的專案了。<br />
![02_7](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/qtbuild/02_7.png)<br />

10. 按左下角的Build等他跑完（這一步非常非常久）。<br />

11. Build完成後把「libpack/bin」中的所有檔案複製一份到「FreeCAD/qtbuild/bin」裡後，FreeCAD.exe就可以使用了。<br />

<br />
##Q & A

Q. 我可以使用其他版本來做嗎？<br />
A. 可以，但不保證用同樣步驟可以成功，歡迎幫忙測試和更新這份教學！<br />

Q. 我的在CMake時一直顯示缺少boost_python該怎麼辦？<br />
A. 可以從討論區 [這篇](http://forum.freecadweb.org/viewtopic.php?t=12631) 的留言中下載，並將\*.lib檔案放入「libpack/lib」、\*.dll檔放入「libpack/bin」即可解決。<br />
　 (只適用Visial Studio 2013版本)<br />

Q. 為什麼要修改File Encoding中的Default Encoding，直接使用預設的UTF-8不行嗎？<br />
A. 也是可以，不過在官方文件中有提到假如使用UTF-8編碼來Encoding，會存在一些字元讓Qt Creator產生error或是warning，<br />
　 而這個動作似乎可以解決這些問題。假如你真的不想改預設編碼，可以找到會出錯的字元們把他們通通改成能用的符號，<br />
　 不過這樣實在很辛苦所以不推薦。<br />
