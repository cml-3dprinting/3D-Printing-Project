#Create a C++ plugin module for FreeCad


1. 
依照此網頁"Using the FreeCAD Build Tool"下的內容，用內建的Python工具自動產生新WorkBench的基本檔案，
生成檔案路徑可參考網頁說明：http://www.freecadweb.org/wiki/index.php?title=Module_Creation    

python tool interface:

![01](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/01.png)




2.
找到"FreeCAD_x86\src\Mod"底下的CMakeLists.txt，加入一行"add_subdirectory(模組名稱)"，
這樣子重新Build Up FreeCAD後，開啟FreeCAD在View->WorkBench下就可以找到剛剛新增的WorkBench，
選取後會啟動模組，工具列上會多出模組的選單，裡面預設的一個"Hello"按鈕按下去，
左下角的Console會顯示"Hello World"(滑鼠游標要離開按鈕上面才不會被其他提示文字蓋掉)

![03](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/03.png)





3.
首先打開"FreeCAD_x86\src\Mod\模組名稱\Gui\WorkBench.cpp"，找到以下敘述：
*test << 右邊的字串是按鈕的宣告，有幾顆按鈕就要宣告幾個對應字串。

![05](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/05.png)




然後打開"FreeCAD_x86\src\Mod\模組名稱\Gui\Command.cpp"，裡面可以找到像這樣的敘述：
:Command的建構子丟入剛剛在WorkBench.cpp內宣告的對應字串
sMenuText是按鈕上要顯示的字，activated()函式內是按鈕按下後要做的事，
CreateTestModCommands()內則要加入增加的command.
這個函式裡把剛剛宣告的按鈕Class的實體丟入addCommand()內。

![07](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/07.png)


而如果要在activated()函式內呼叫自行定義的C++ Class可以在Command.cpp檔頭Include .h和.cpp，路徑如下：
當然這兩個檔案也要做一些匯入的動作，見下步。




4.
.h檔和.cpp檔的內容可參考附件，此處則可自行發揮

![08a](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/08a.png)
![08b](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/08b.png)

最後修改CMakeLists.txt內容，讓cmake可以順利生成專案與檔案索引
開啟"FreeCAD_x86\src\Mod\模組名稱\App\CMakeLists.txt"，
在以下段落加入.h檔和.cpp檔檔名：

![10](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/10.png)
![11](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/11.png)


5.
重新編譯FreeCAD好反應新增的內容，附件是建來測試用的簡單WorkBench。
[附件](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/Module_c-_Creation/TestMod.rar)

以上大概就是FreeCAD使用C++來建立WorkBench的大致流程
