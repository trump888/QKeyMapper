# QKeyMapper
---------------
## 在Win10和Win11下可以正常使用的键盘映射工具，使用Qt Widget + WinAPI开发，v1.2.8(2022-12-24)开始更新了对Qt6的支持，v1.2.8及之后的Release中使用Qt6编译的版本，v1.3.6(Build 20231220)新增游戏手柄按键和虚拟游戏手柄支持。
### Win10及Win11系统推荐使用Qt6版本，提供Qt5版本只是为了能兼容Win7系统。Win7下如果无法使用Qt6版本的话请下载Qt5版本使用。
### 注意: 使用时需要 Visual C++ Redistributable for Visual Studio 2015 64位运行库。<br>VC++ 2015 64位运行库，微软下载网址：<br>https://www.microsoft.com/zh-cn/download/confirmation.aspx?id=48145
### 注意: v1.3.6(Build 20231125)版本修改了鼠标按键存储在ini配置文件中的名称，设定选择1.3.6版本之前存储的带有鼠标按键的设定有可能会提出加载出错，如果软件自己加入的容错处理未生效，可以尝试手动在ini文件中将L-Mouse、R-Mouse、M-Mouse、X1-Mouse、X2-Mouse替换为Mouse-L、Mouse-R、Mouse-M、Mouse-X1、Mouse-X2
### 注意: v1.3.6(Build 20231220)版本新添加的虚拟游戏手柄功能需要安装ViGEmBus驱动，频繁的反复安装和卸载ViGEmBus驱动有导致系统蓝屏重启风险，请谨慎使用，避免反复安装和卸载驱动。如果软件上的"安装ViGEmBus"按钮无法正常安装驱动，也可以使用软件压缩包中附带的"ViGEmBus_1.22.0_x64_x86_arm64.exe" 驱动安装程序自己手动安装 ViGEmBus驱动。
---------------
## 使用教学视频请点击下方图片
[![](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/show_video.png)](https://www.bilibili.com/video/BV1Re411f7YS/?share_source=copy_web&vd_source=9602438c12e2a27bbe08c10cd8723515)
---------------
## 使用中有疑问也可以加Q群咨询 (群号: 906963961)
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_QGroup_Number.png)
---------------
### 新添加功能列表(根据更新时间降序排列)
* v1.3.6(Build 20231225) -> 添加"锁定光标"复选框，勾选后鼠标控制虚拟游戏手柄摇杆时鼠标光标被锁定在屏幕右下角位置。
* v1.3.6(Build 20231223)
    * 添加了通过鼠标控制虚拟游戏手柄左/右摇杆的功能(Mouse2Joystick)，通过在映射表中添加"vJoy-Mouse2LS"或"vJoy-Mouse2RS"来使用。鼠标控制摇杆的X轴和Y轴灵敏度范围"1~1000"，数值越小越灵敏。
    * "自动映射并最小化" 按钮变为三态复选框，设置为中间状态时软件启动仅最小化到托盘，不自动开始按键映射。
* v1.3.6(Build 20231220) -> 添加了虚拟游戏手柄功能(通过ViGEmBus实现)，点击"安装ViGEmBus"，显示绿色字"ViGEmBus可用"之后，勾选"启用虚拟手柄"，之后可以将键盘按键映射到"vJoy"开头的虚拟手柄按键。
* v1.3.6(Build 20231125) -> 添加了将游戏手柄按键作为原始按键映射到键盘按键的功能，原始按键列表中选择"Joy"开头的按键，映射按键选择想触发的键盘按键即可。
* v1.3.5(Build 20230806) -> 切换映射开始和停止的快捷键，可以通过KeySequenceEdit控件进行自定义设置，鼠标点击KeySequenceEdit控件后按下想要设置的快捷键，此自定义快捷键设置每个配置可以保存设置不同值。
* v1.3.5(Build 20230805) -> 添加可以直接在任意状态下切换映射开始和停止的快捷键，按下"Ctrl + F6"快捷键，无论在前台或者托盘显示状态都可以在开始映射和停止映射状态之间立即切换。
* v1.3.5 -> 添加中文界面，可以使用语言切换下拉列表进行中英文界面切换，适配4K/2K/1K分辨率。
* v1.3.3 -> 按键列表中添加了对鼠标侧键XButton1和XButton2的支持。
* v1.3.3 -> 在ADD按键右侧增加了"»"勾选框，用于添加按键序列，例如: Ctrl + X 之后 Ctrl + S，设置后效果参考README中显示的截图。
* v1.3.2 -> 在"KeyMappingStart"(循环检测)状态下，如果检测到到前台窗口与当前SelectSetting的键盘映射配置设定一致时候会播放一个音效提示进入到键盘映射生效状态。
* v1.3.1 -> 加入单例进程支持，只能同时运行一个QKeyMapper程序, 运行第二个QKeyMapper程序时会将第一个运行的实例程序窗口显示到前台。
* v1.3.1 -> "Auto Startup"勾选框可以让QKeyMapper键盘映射程序在Windows用户登录的时候自动启动，配合"Auto Start Mapping"勾选框开机启动后可以自动最小化到系统托盘图标，取消勾选框则取消开机登录自动启动。
* v1.3.0 -> 版本开始支持"SaveMapData"可以将多个程序的不同键盘映射配置都保存到"keymapdata.ini"文件中。如果配置了"Auto Start Mapping"功能，那么在"KeyMappingStart"状态下会根据当前前台窗口的进程可执行文件名进行自动匹配切换到对应的键盘映射配置。
---------------
### 基本功能列表
1. 左侧显示当前正在运行的可见的窗口程序列表，进程可执行exe文件的文件名和对应的窗口标题名都会显示出来，信息会用于匹配当前处于前台的窗口。
2. 鼠标左键双击左侧窗口程序列表的某一行可以将选定的窗口程序的可自行文件名和窗口标题设定到图标/文件名/窗口标题区域。
3. 按下"KeyMappingStart"按钮可以开始执行键盘映射处理流程，映射工具会定时循环检测当前处于前台的窗口与设定的可自行文件名和窗口标题是否匹配，键盘映射功能可以只在前台窗口与当前进程可执行文件名和窗口标题都匹配的情况才生效，前台窗口不匹配的情况下键盘映射自动失效。
4. 支持在右侧添加和删除键盘映射表，下拉列表获取焦点时按下特定键盘按键可以自动将按键名设置到下拉列表上。
5. "SaveMapData"按钮会将键盘映射表中的信息和进程及窗口标题信息保存到同一路径下的ini设定文件中，之后键盘映射工具下次启动时可以自动加载同一路径下的"keymapdata.ini"文件读取已保存的设定值。
6. 按下"Ctrl + `"组合键会自动将QKeyMapper最小化显示到任务栏的系统程序托盘上，左键双击程序托盘图标会恢复显示程序窗口。
7. 将多个按键映射到同一个键盘初始按键会按照"A + B"的形式来显示再键盘映射表中，以此来支持用一个键盘初始按键来同时映射多个按键。
8. 加入了"Disable WIN Key"功能可以让键盘上的Windows按键在游戏中无效。
9. 右侧键盘映射表中加入了连发(Burst)选择框，可以按照设定的连发按下时间(BurstPress)和连发抬起时间(BurstRelease)设定来反复发送映射表中的按键。
10. 右侧键盘映射表中加入了锁定(Lock)选择框，选择后第一次按下对应的键盘初始按键后会保持此按键的按下状态，再次按下此键盘初始按键后接触锁定状态，支持与连发(Burst)选择框来组合使用，映射表中的Lock列的ON和OFF表示当前按键锁定状态。
11. 加入了"Auto Start Mapping"功能可以让程序启动后自动根据加载的配置文件开始键盘映射，并且最小化到系统托盘, 。
12. 增加了SelectSetting下拉列表，可以保存最多10组不同的设定，并且通过下拉列表随时切换。
13. 增加了支持将鼠标左键&右键&中键与键盘按键进行互相映射。
---------------
## Screenshot
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_screenshot_02.png)
---------------
## VirScan result
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_VirScan.png)
