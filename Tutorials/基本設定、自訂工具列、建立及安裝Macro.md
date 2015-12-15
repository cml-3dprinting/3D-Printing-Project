#基本設定、自訂工具列、建立及安裝Macro

最近更新: 2015/12/15<br />
官方文件: http://www.freecadweb.org/wiki/index.php?title=Macros_recipes

<br />
##FreeCAD基本設定

1. 選擇「Edit > Preference...」做介面修改。<br />
![01_1](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/01_1.png)<br />

2. 在General的General分頁選擇語言，這裡設定為中文（需注意第一個中文為簡體，第二個為繁體，這裡我們維護的部分為繁體中文）。<br />
![01_2](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/01_2.png)<br />

3. 因為我們直接修改Part的工作列，因此也要將Start up的Auto load部分改為Part這個工作列。<br />
![01_3](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/01_3.png)<br />

4. 設定完成後按OK，接著重新啟動FreeCAD即可。<br />
![01_4](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/01_4.png)<br />

5. 另外下方的報表檢視與Python控制台為編輯Macro時Debug使用，可以從「檢視 > 檢視 > 報表檢視（或Python控制台）」處關閉。<br />
![01_5](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/01_5.png)<br />

<br />
##建立Macro

1. 這裡我們會將建立的Macro放在「qtbuild/macros」中。<br />
![02_1](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_1.png)<br /> 

2. 也可以將現有的Macro放到這個資料夾來安裝到FreeCAD上。<br />
![02_2](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_2.png)<br /> 

3. FreeCAD中是從「巨集 > 巨集...」來做設定。<br />
![02_3](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_3.png)<br /> 

4. 將巨集目標設定為「qtbuild/macros」這個資料夾後就能夠使用該資料夾中的Macro。<br />
![02_4](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_4.png)<br /> 

5. 按下建立則可以開始編寫新的Macro，若想要編輯現有的Macro則在選取該Macro後點選編輯即可。<br />
![02_5](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_5.png)<br /> 


<br />
##自訂工具列及安裝Macro

1. 選擇「工具 > 自訂...」。<br />
![02_6](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_6.png)<br /> 

2. 在巨集的分頁中可以設定Macro的名稱、圖示、快捷鍵等參數，設定完成後按「新增」，稍後就能在自訂的工具列中擺上這個Macro。<br />
![02_7](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_7.png)<br /> 

3. 接著到工具列分頁安裝Macro到自訂工具列，首先須將左方的功能選取部分調到「巨集」（注意是上面那個巨集，下面那個是FreeCAD的巨集功能，也就是剛剛前面用到的新增、編輯、執行等功能），右邊則是選擇Part這個Workbench。<br />
![02_8](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_8.png)<br /> 

4. 按下右邊的新增來在Part的Workbench上建立一個自訂的工具列。<br />
![02_9](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_9.png)<br /> 

5. 左邊選取你的Macro，右邊選取剛剛建立的工具列，按下向右的按鈕就可以把Macro裝到你的工具列上。<br />
![02_10](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_10.png)<br /> 

6. 接下來你就能在工具列上找到你的Macro功能了。<br />
![02_11](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/02_11.png)<br /> 


<br />
##Q&A

Q. 在Macro裝上工具列之前或是Macro編輯中可以測試他的功能嗎？<br />
A. 可以，裝上工具列之前可以從「巨集 > 巨集」的視窗中按右上角的「執行」，編輯中可以從「巨集 > 執行巨集」來測試<br />
　 目前的功能。<br />
　 ![03_1](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/03_1.png)<br /> 
　 ![03_2](https://github.com/yclilian/3D-Printing-Project/blob/master/Tutorials/Images/macro/03_2.png)<br /> 
