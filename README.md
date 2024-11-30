# QKeyMapper

<p align="left">
    <a href="./LICENSE"><img src="https://img.shields.io/github/license/Zalafina/QKeyMapper"></a>
    <a href="https://github.com/Zalafina/QKeyMapper/releases"><img src="https://img.shields.io/github/v/release/Zalafina/QKeyMapper?color=09e"></a>
    <a href="https://github.com/Zalafina/QKeyMapper/stargazers"><img src="https://img.shields.io/github/stars/Zalafina/QKeyMapper?color=ccf"></a>
    <a href="https://github.com/Zalafina/QKeyMapper/releases/latest" target="_blank"><img src="https://img.shields.io/github/downloads/Zalafina/QKeyMapper/total.svg"/></a>
</p>

## 在Win10和Win11下可以正常使用的按键映射工具，使用Qt Widget + WinAPI开发，v1.2.8(2022-12-24)开始更新了对Qt6的支持，v1.2.8及之后的Release中使用Qt6编译的版本，v1.3.6(Build 20231220)新增游戏手柄按键和虚拟游戏手柄支持。v1.3.7(Build 20240410)增加多键鼠+多虚拟手柄支持。
---------------
### 最新Release版本压缩包下载:
### https://github.com/Zalafina/QKeyMapper/releases/latest
### https://gitee.com/asukavov/QKeyMapper/releases/latest
### ※ QKeyMapper_vX.Y.Z_x64/x86开头的ZIP包是编译好的可执行文件压缩包Build_YYYYMMDD代表编译日期，较新的编译日期有相应的新增功能说明。
---------------
### Win10及Win11系统推荐使用Qt6版本，提供Qt5版本只是为了能兼容Win7系统。Win7下如果无法使用Qt6版本的话请下载Qt5版本使用。
### 注意: 使用时可能需要安装 Visual C++ Redistributable 64位运行库。<br>VC++ 2015-2022 64位运行库，微软下载网址：<br>https://aka.ms/vs/17/release/vc_redist.x64.exe
* ( 32位系统则下载安装32位运行库 https://aka.ms/vs/17/release/vc_redist.x86.exe )

### [注意: Win7系统使用虚拟手柄功能需要自己安装ViGEMBus v1.16.116](https://github.com/Zalafina/ViGEmBus_v1.16.116_Win7_InstallFiles)
* https://github.com/Zalafina/ViGEmBus_v1.16.116_Win7_InstallFiles
---------------
## 按键映射工具使用技巧等参考Wiki页面：
* [QKeyMapper使用技巧等Wiki](https://github.com/Zalafina/QKeyMapper/wiki)
---------------
## 使用教学视频合集请点击下方图片
[<div align="center"><img src="https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/show_video.png" width="572" height="auto"/></div>](https://space.bilibili.com/4572027/channel/collectiondetail?sid=2468700)
---------------
## 使用中有疑问也可以加Q群咨询 (群号: 906963961)
<div align="center"><img src="https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_QGroup_Number.png" width="357" height="auto"/></div>

---------------
### 新添加功能列表(根据更新时间降序排列)
* v1.3.7(Build 20241130)
    * 映射项设定窗口中添加"不可打断"勾选框，勾选后同一个原始按键的映射按键未发送完毕之前再次按下相同的原始按键不会进行任何动作。未勾选状态下默认重复按下相同原始按键会打断当前正在发送中的映射按键，重新开始发送映射按键。
    * 映射项设定窗口中编辑映射按键时对重复的映射按键检查规则增加，同一映射按键使用不同的前后缀添加时也会检查为重复按键，例如："A+！A" 和 "A+A⏱200" 都会检查为存在重复按键。
* v1.3.7(Build 20241126)
    * 修复11月新版程序导入以前版本的mapdata INI文件崩溃问题。
* v1.3.7(Build 20241124)
    * 添加映射按键"Mouse-Move_WindowPoint"和"Mouse-Move_ScreenPoint"，可以指定将鼠标指针移动到窗口内或屏幕内的特定坐标点，坐标点设置方式与鼠标按键点击映射相同，L-Ctrl+鼠标左键选取全屏坐标点，L-Alt+鼠标左键在当前选定好的窗口标题对应窗口内选取坐标点。
    * 映射项设定窗口中可以给(Mouse-L|R|M|X1|X2|Move_WindowPoint)和(Mouse-L|R|M|X1|X2|Move_ScreenPoint)这些鼠标坐标点映射加入":BG"，配合同时勾选"发送到同名窗口"勾选框，可以只发送PostMessage鼠标事件给指定标题的窗口，屏幕上鼠标指针位置不发生移动。
      * 示例：PostMessage方式发送窗口内鼠标左键点击x坐标500，y坐标100位置 -> "Mouse-L:W:BG(500,100)"
      * 示例：PostMessage方式发送屏幕内鼠标左键点击x坐标500，y坐标100位置 -> "Mouse-L:BG(500,100)"
    * 修复11月近期版本中引入的安装/卸载"ViGEm"驱动时程序界面卡死问题。
* v1.3.7(Build 20241120)
    * 映射项设定窗口中添加"检查组合键按下顺序"勾选框，勾选后如果原始按键是组合键则检查组合键触发时按键的按下顺序是否与原始按键排列顺序一致，一致时才触发组合键。例如："A+B"的原始按键组合键勾选"检查组合键按下顺序"后，先按下A再按下B才会触发组合键。"检查组合键按下顺序"默认值为启用，如果不希望检查组合键按下顺序则取消勾选。
* v1.3.7(Build 20241116)
    * 映射项设定窗口中添加"按键录制"按钮，按下此按钮弹出按键录制对话框。录制对话框下按下"F11"键开始进行按键录制，按下"F12"键停止按键录制，也可以鼠标左键点击"开始录制"/"停止录制"按钮来开始和停止按键录制。按键录制结束后的按键记录显示在编辑框中，并且自动复制到了剪贴板。之后可以直接将按键记录内容粘贴到"映射按键"编辑框等位置。
* v1.3.7(Build 20241112)
    * 映射项设定窗口中添加"发送时机"下拉选择列表，可以选择"正常/按下/抬起/按下+抬起/正常+抬起"，可以在不同的原始按键按下或释放时机发送映射按键。原有的"按键抬起时动作"勾选框被替代并移除。
    * 映射项设定窗口中添加"抬起映射"编辑框，可以单独编译原始按键抬起时发送的映射按键，默认内容与"映射按键"相同。"映射按键"对应原始按键按下时发送的映射键，"抬起映射"对应原始按键抬起时发送的映射键。
    * 映射项设定窗口中添加"映射按键解锁"勾选框，勾选"锁定"勾选框后可以追加勾选"映射按键解锁"勾选框。作用是短按映射按键中的任意按键可以解除锁定状态并释放当前锁定的按键。例如："L-Shift⏲500" 映射到 "L-Shift" 并勾选锁定，长按L-Shift后L-Shift会处于按下锁定状态，再次长按L-Shift解除锁定释放L-Shift键。如果同时勾选了"映射按键解锁"勾选框，长按L-Shift锁定后短按L-Shift键(映射按键)即可解除锁定释放L-Shift键。
    * 扩展了映射项设定窗口中的"映射按键列表"添加"！"前缀的按键后覆盖功能，可以支持物理按键和映射后的虚拟按键(包括键盘按键和鼠标按键)。
* v1.3.7(Build 20241030)
    * 连发按键按下有可能导致程序崩溃问题修复。
    * 停止映射状态下，映射软件主窗口前台显示时按下"L-Ctrl+S"执行"保存设定"动作。
    * 其他影响使用体验的问题修复。
* v1.3.7(Build 20241024)
    * "按键序列按下保持"功能问题修复。
* v1.3.7(Build 20241022)
    * 添加映射按键"KeySequenceBreak"，用于打断"»"连接起来的按键序列发送。例如：设置原始按键Q，映射按键选择"KeySequenceBreak"，按下键盘按键Q时，会立即打断所有当前映射表中正在发送中的按键序列。
    * 按键连发发送方式优化。
    * 按键连发停止或者按键序列发送停止时检测当前仍然处于按下状态的物理按键并补发此物理按键的按下消息，使其仍然检测为按下状态。
    * 添加"--scale="启动参数用于强制指定软件启动后的界面缩放比例，例如：快捷方式中设置 "QKeyMapper.exe --scale=1.0" 会强制以1.0缩放比例启动程序，不传递"--scale="参数时如果系统缩放比例为1.0会默认以1.25缩放比例启动。
* v1.3.7(Build 20241012)
    * 游戏手柄检测SDL2库更新到SDL2-2.30.8(2024-10-02发布)，游戏手柄检测数据库更新。
* v1.3.7(Build 20241006)
    * "映射表设定"对话框窗口添加"映射项描述"编辑框，可以对保存的某一条按键映射进行描述备注，备注信息在鼠标悬停在映射列表的原始按键格内会以提示框的形式悬浮显示在鼠标指针位置。
    * 主窗口右上角添加"显示备注"可勾选按钮，默认"显示备注"按钮是未勾选抬起状态，原始按键列表不会在末尾追加备注信息显示。如果点击"显示备注"按钮会切换为勾选按下状态，此时映射表中原始按键会以"原始按键【映射项备注】"的形式显示。
    * 映射按键发送并发处理方式优化。
* v1.3.7(Build 20240928)
    * 映射项设定窗口中添加"按键按下时循环"和"循环次数"勾选框，两个勾选框只能同时勾选其中一个，"按键按下时循环"用于原始按键持续按下状态循环重复发送按键序列，"循环次数"可以指定按下一次原始按键会循环重复发送多少次按键序列。
    * 映射项设定窗口中的"映射按键列表"添加"！"前缀，此前缀添加在普通键盘或鼠标映射按键前面，用于实现按键后覆盖功能。例如："D"键映射到"！A"，先按下"A"键再按下"D"键会自动发送释放"A"键，"D"键抬起时如果"A"键物理按键仍然处于按下状态则会自动发送"A"键按下消息。(这个字符不是键盘上的叹号，需要使用映射项设定窗口的映射按键列表进行添加，或者从其他地方复制)
    * 主窗口"保存设定"按钮下方添加了"映射设定描述"编辑框，可以对保存的进程和标题对应的设定进行描述备注，备注信息在设定选择列表中会以"process.exe|TitleX【映射设定描述】"的形式显示。
    * 语言选择下拉列表移动到"通用"设定标签页。
    * 主窗口右上角添加"进程列表"可勾选按钮，默认"进程列表"按钮是勾选按下状态，会在主窗口左侧显示进程列表。如果点击"进程列表"按钮会切换为未勾选抬起状态，此时主窗口左侧进程列表隐藏，右侧映射表宽度变宽占据进程列表原来位置进行显示。
* v1.3.7(Build 20240916)
    * 单个设定选择项(进程名+标题)下支持添加多套映射表，默认的映射表标签名是"Tab1"，鼠标左键双击"+"标签页按钮添加一个空白映射表，标签页名称自动按照数字排序"Tab2"、"Tab3"……
    * 鼠标左键双击已存在的映射表标签名位置进入"映射表设定"对话框，可以对"映射表名"和"映射表快捷键"进行修改，修改后需要点击"更新"按钮生效。更新后的"映射表名"和"映射表快捷键"需要点击"保存设定"按钮才会保存到设定文件中。
    * "映射表快捷键"用于在游戏中映射生效状态下通过快捷键切换当前激活的映射表，这样游戏中可以随时切换几套不同按键映射。如果快捷键前面加入"$"字符，表示快捷键设置的按键键触发之后不会被拦截，仍然会发送给应用程序。
    * "映射表设定"对话框窗口添加"导出映射表"按钮，可以导出某一个映射表中的全部按键映射数据到INI文件中，默认导出文件名是"mapdatatable.ini"，可在文件保存对话框中自己设置文件名。
    * "映射表设定"对话框窗口添加"导入映射表"按钮，可以选择INI文件来导入之前导出的映射表数据文件，数据导入后追加到所选映射表的末尾。由于同一映射表中不能存在相同按键的重复映射，如果导入数据的原始按键与表中已存在数据的原始按键相同会被过滤掉。
    * 物理手柄按键检测输入检测可以检测到虚拟手柄输入，可以将虚拟手柄按键映射和物理手柄按键映射组合来使用。例如：可以同时添加 vJoy-Mouse2RS 和 Joy-RS-Up、Joy-RS-Down、Joy-RS-Left、Joy-RS-Right 映射到键盘按键，达到鼠标向上下左右移动触发键盘按键的效果。
* v1.3.7(Build 20240812)
    * 原始按键列表中"Joy-"开头的物理手柄按键可以添加"@" + "0到9" 的数字编号来选择输入手柄的玩家编号(PlayerIndex)来进行区分映射，可支持0到9总共10个玩家编号。不添加"@" + "0到9" 的数字编号则映射来自所有物理手柄的输入。
    * 添加"游戏手柄"下拉组合框用于配合"原始按键"列表选择原始按键映射的游戏手柄玩家编号(PlayerIndex)，根据所选择的游戏手柄玩家编号(PlayerIndex)在添加"Joy-"开头的原始按键映射时候在后面追加"@+数字编号0~9"，例如："Joy-Key1(A/×)@0"表示0号游戏手柄的(A/×)按键。
    * 移除功能 [鼠标点击高亮选择一条映射表项目后，按下键盘"Backspace"键可以删除最后一个"»"或"+"连接的映射按键]，映射按键可以通过映射项设定窗口中的"映射按键"编辑框进行修改。
* v1.3.7(Build 20240711)
    * "映射按键列表"添加SendText映射，选择SendText后在"文本"单行编辑框中输入文字可以在按下原始按键时向当前前台窗口或指定窗口发送SendText()括号内的字符串。
    * "显示切换键"和"映射开关键"设置按键字符串时可以在前面加入"$"字符，表示"显示切换键"和"映射开关键"设置的按键键触发之后不会被拦截，仍然会发送给应用程序。
    * "通用"标签页中添加"提示信息"组合框，可以选择映射状态变化是否在屏幕上显示提示信息。提示信息显示位置可以选择"顶部左侧"、"顶部居中"、"顶部右侧"、"底部左侧"、"底部居中"、"底部右侧"。
    * 修改为多个QKeyMapper程序可以同时在系统中运行，将QKeyMapper解压后的目录复制多份，可以为同时运行的多个程序设置各自独立的配置文件。
    * "映射开关键"分离为"映射开启键"和"映射关闭键"，可以给开启和关闭设置不同的快捷键。
    * 映射项设定窗口中的"映射按键列表"添加"↓"、"↑"、"⇵"前缀，这三种前缀可以添加在普通映射按键前面，用于映射按键按下的时机仅发送映射键的按下、抬起和同时发送按下+抬起。
* v1.3.7(Build 20240622)
    * 映射列表中添加"WindowPoint"映射,可以使用L-Alt+鼠标左键来标记当前映射设定对应窗口的窗口内相对坐标，选择Mouse-L|R|M|X1|X2_WindowPoint可以发送窗口内的相对鼠标坐标点击。"F8"按键显示当前设定映射窗口内的WindowPoint坐标点。窗口内坐标点颜色等其他规则与之前添加的"F9"按键显示的全屏坐标点相同。
    * 在"映射设定"标签页中添加"发送到同名窗口"勾选框，勾选此设定时，映射按键会发送到与当前"标题"显示名称相同的所有窗口，即使窗口已最小化到任务栏未在前台显示。
* v1.3.7(Build 20240610)
    * 添加设定"标签页"，将所有软件设定项分页归类到几个独立"标签页"中。标签页包括"通用"、"映射设定"、"虚拟游戏手柄"、"多输入设备"、"极限竞速"。
    * 映射项设定窗口中"原始按键"和"映射按键"编辑功能。
        * 双击映射列表弹出的映射设定窗口中"原始按键"编辑框和"映射按键"编辑框中可以对原始按键和映射按键进行编译，编辑完成后按下编辑框尾部对应的"更新"按钮或者编辑框获取焦点状态按下键盘回车键(Enter)会更新"原始按键"或"映射按键"。更新成功时窗口中央显示绿色字体弹出消息"更新成功"，3秒后消失。更新失败窗口中央显示红色字体弹出消息提示更新失败原因，3秒后消失。
        * 鼠标右键单击"原始按键列表"和"映射按键列表"可以将当前列表显示的内容根据当前光标位置添加到"原始按键"和"映射按键"编辑框中。
* v1.3.7(Build 20240604)
    * 鼠标左键双击映射列表中某一行在窗口中央弹出此按键的映射设定对话框，其中可以更改 "连发"、"锁定"、"按键抬起时动作"、"原始按键穿透"状态。
    * 按键映射列表下方的 "连发按下"时间 和 "连发抬起"时间 数值调节框从主窗口移动到映射设定对话框中，每条按键映射的"连发按下"时间和"连发抬起"时间都可以单独进行设定和保存。
    * 系统托盘图标添加右键菜单项"显示"/"隐藏"用于显示和隐藏主窗口，输入设备列表窗口显示中无效。
    * 系统托盘图标添加右键菜单项"退出"，可以直接结束程序。
    * 按键映射列表中的项增加拖拽功能。
    * 按下"保存设定"按钮保存当前映射设定成功时，窗口中央显示绿色字体弹出消息"保存成功 : 设定项名称"，3秒时间逐渐淡出消失。
    * 将"自动映射并最小化"勾选框设定拆分为 "自动匹配并启用映射" 和 "启动后自动最小化" 两个勾选框设定。
    * 最后一次成功保存的设定文件会备份一份在QKeyMapper.exe相同路径下，文件名是"keymapdata_latest.ini"，如果遇到映射数据出错的问题，可以尝试用此文件替换"keymapdata.ini"进行恢复。
    * 支持".exe"后缀以外的可执行文件进程名称。
    * 映射设定对话框中添加 "按键序列按下保持" 勾选框，勾选状态下，原始按键按下不抬起时，按键序列的最后一组映射键(最后一个"»"之后的部分)保持按下状态。当原始按键抬起时发送按键序列的最后一组映射键的按键抬起。
* v1.3.7(Build 20240519)
    * 添加"长按"和"双击"时间数值调节框(通过数值框前面的下拉列表选择按压种类)，可以对按键长按达到特定时间进行映射(1~9999毫秒范围内)，也可以对按键在特定时间间隔内双击两次进行映射。
    * 按键映射PassThrough模式的切换键由"F2"按键变为"F12"按键。
    * 增加了映射的KeyUp_Action模式，选择映射表中某一条映射，按下"F2"按键，原始按键字符串变为下划线字体显示，则此条映射不在原始按键按下的时机触发映射按键，而是在原始按键抬起时触发映射按键。
    * 鼠标右键点击"原始按键"列表控件，可以将当前显示的"原始按键"按键名称追加到"原始组合键"编辑框中，比直接手动填写或者复制填写组合键名称简便一些。
    * 鼠标点击高亮选择一条映射表项目后，按下键盘"Backspace"键可以删除最后一个"»"或"+"连接的映射按键，映射键只有一个按键时不再删除。
    * 修复"长按"和"双击"映射对"连发"和"锁定"功能的支持(Build 20240519)。
* v1.3.7(Build 20240416)
    * 支持最多添加4个虚拟游戏手柄并可以分别独立进行控制。
        * 多虚拟手柄功能1：在虚拟手柄类型组合列表框后面加入了可增加减少手柄数量的"微调框"，数量范围1到4之间，点击微调框向上箭头增加手柄数量(根据手柄类型选择框决定添加的手柄类型X360/DS4)，点击向下箭头每次删除最后添加的一个手柄。
        * 多虚拟手柄功能2：已添加的手柄通过虚拟手柄列表组合列表框来查看和选择，添加映射虚拟手柄按键时候在手柄按键后根据当前选择的虚拟手柄来添加"@+数字编号0~3"，表示映射的是哪个虚拟手柄的按键。虚拟手柄选择组合列表框为空时候添加映射后面不添加"@+数字编号"，默认映射到0号虚拟手柄按键上。
    * 启用多输入设备时可以使用"筛选键"勾选框来开启和关闭是否过滤掉同一个键盘上同一按键持续按下时候的按键重复发送，与Windows控制面板的筛选键开关功能相同，但是Windows自带的筛选键在同一PC上同时连接的多个键盘上的不同按键同时按下时会失效，此多输入设备筛选键解决了此问题。筛选键设定保存到每个映射配置文件中，可以为不同的应用窗口设置不同的筛选键开关状态，根据前台窗口自动切换映射配置也会加载相应的筛选键设定。
    * 启用多输入设备时使用Interception驱动进行键鼠输入监听，比WinAPI低级键鼠钩子函数的拦截更底层，可对某些低级键鼠钩子无法拦截输入的游戏进行按键映射。
    * 增加了映射的PassThrough模式，选择映射表中某一条映射，按下"F2"按键，原始按键字符串显示颜色会变为"橙色"，表示此条映射变为PassThrough模式，也就是原始按键按下后会发送映射按键，但是原始按键并不会被拦截，会与映射按键一起触发。
* v1.3.7(Build 20240330)
    * 支持多输入设备区分功能(最大可以接收10个不同键盘和10个不同鼠标设备的输入)。
        * 多输入设备功能1：多输入设备GroupBox框内的"安装驱动"和"卸载驱动按钮用于卸载和安装多输入设备支持驱动程序(驱动程序安装和卸载之后都需要重新启动系统才能生效)。
        * 多输入设备功能2：多输入设备GroupBox框内的"启用"勾选框勾选状态下才会对不同的键盘和鼠标设备的输入进行区分，不勾选则不区分输入设备操作。
        * 多输入设备功能3：多输入设备GroupBox框内的"设备列表"按钮弹出键盘和鼠标输入设备列表，列表中会显示当前系统中连接的键盘和鼠标设备，并显示各设备的"设备描述"、"硬件ID"、"VID"、"PID"、"厂商"、"产品名"、"制造商"信息。多输入设备启用状态下最后操作过的键盘和鼠标设备在设备列表中会处于高亮选中状态。
        * 多输入设备功能4："设备列表"按钮弹出键盘和鼠标输入设备列表中的禁用勾选框可以对键盘和鼠标设备禁用，勾选禁用后点击确认按钮退出设备列表时禁用生效，并且保存列表同禁用的键盘和鼠标设备到禁用列表中，下次程序启动会自动加载之前保存过的禁用设备列表。(禁用设备时此设备的任何输入都无法接收到，请谨慎使用，不要把当前正在使用的输入设备禁用后无法进行操作)。
        * 多输入设备功能5："键盘"和"鼠标"下拉组合框用于配合"原始按键"列表选择原始按键映射的输入设备编号，根据选择的设备会在添加原始按键映射时候在后面追加"@+数字编号0~9"，例如："A@0"表示0号键盘的A键，"Mouse-L@1"表示1号鼠标的左键。
        * 多输入设备功能6："原始组合键"文本编辑框中可以直接输入特定输入设备编号的组合键，例如: "L-Ctrl@2+F@2" 表示2号键盘的LCtrl键加F键的组合键，"L-Alt+3@1" 表示任意键盘的L-Alt键加1号键盘3键的组合键。
        * 多输入设备功能7：多输入设备启用状态下，如果按键映射列表中存在多个匹配当前按键的映射时候，以从上到下第一个匹配的映射条目生效，其他不生效。例如: 映射列表中对"W@2" 和 "W" 两个原始按键都进行了映射，按下2号键盘的W键时候 "W@2" 排在上则触发 "W@2"，"W" 排在上则触发 "W"。
#### ※ 注意: 安装多设备驱动后不要反复对系统连接的USB设备进行插拔，Interception驱动的键盘/鼠标设备ID上限是10，每次拔插时设备的ID上限会增加1，超过上限会导致设备无法检测输入，只有重新启动操作系统才能复归。系统进入休眠状态再复归也会与拔插设备类似的增加设备ID，也会发生设备ID增加到超过上限10的问题，也需要避免。建议使用多设备驱动时，先将需要使用的输入设备都连接好后重新启动系统使用，并且使用过程中不要拔插设备。
* v1.3.6(Build 20240320)
    * 修复映射停止时，锁定且处于按下状态的虚拟按键没有释放的问题。
    * 修复映射按键的延时设置大于1000毫秒以上无法生效的问题，映射按键延时设置上限增大到9999毫秒。
* v1.3.6(Build 20240316)
    * 映射按键列表加入Mouse-(L/R/M/X1/X2)_Point，用于模拟鼠标按键移动到屏幕上特定坐标点进行点击的效果。"L-Ctrl+鼠标左键"点击屏幕任意位置更新"坐标"显示标签中的“X:???,Y:???”坐标点显示。例如：映射按键选择"Mouse-L_Point"配合"坐标"显示标签，添加后映射列表加入Mouse-L(aaa,bbb)表示模拟鼠标左键点击屏幕横坐标aaa、纵坐标bbb的位置。按下键盘"F9"会用半透明窗口+彩色圆点的形式显示当前映射列表中鼠标点击坐标的位置，不同鼠标按键的圆点颜色不同，左键(红色)、右键(绿色)、中键(黄色)、侧键1(蓝色)、侧键2(紫色)。
    * 原始按键列表加入 Joy-LS_2vJoyLS、Joy-RS_2vJoyRS、Joy-LS_2vJoyRS、Joy-RS_2vJoyLS可以将物理手柄摇杆完全映射到虚拟手柄摇杆。
    * 原始组合键添加鼠标滚轮支持，"Mouse-WheelUp"和"Mouse-WheelDown"。
* v1.3.6(Build 20240312)
    * 为Parsec等高优先级进程窗口添加兼容性支持，其他由于权限原因无法读取进程可执行文件名称的情况进程名统一显示为QKeyMapperUnknown
    * 添加"Func-"前缀的功能性映射按键，Func-Refresh(刷新)/Func-LockScreen(锁屏)/Func-Shutdown(关机)/Func-Reboot(重启)/Func-Logoff(注销)/Func-Sleep(睡眠)/Func-Hibernate(休眠)
* v1.3.6(Build 20240305)
    * 【极限竞速: 地平线】键盘可使用虚拟手柄 "vJoy-Key11(LT)_BRAKE" 映射来根据 "刹车阈值" 自动控制刹车力度。
    * 更改组合键映射策略，"原始组合键"改为文本框来手动输入，现在可以支持 [CombinationSupportKeys.txt 文件的按键列表](https://github.com/Zalafina/QKeyMapper/wiki/CombinationSupportKeys)中列出的所有按键进行组合，支持键盘按键与鼠标按键组合使用。支持的按键列表参考版本压缩包中的 CombinationSupportKeys.txt 文件，编写时候按键之间用"+"连接，例如："L-Ctrl+Home"、"A+B+C"。
    * "显示切换键"和"映射开关键"热键也改为文本框来手动输入。
    * 删除"禁用Win键"勾选框，现在可以通过映射按键中选择"BLOCKED"来禁用任意按键。
    * 为鼠标控制虚拟游戏手柄左/右摇杆的功能(Mouse2Joystick)添加了两个可映射的控制按键，Mouse2vJoy-Hold(按下后当前的摇杆偏移保持不再变化，按键抬起后摇杆偏移归0)，Mouse2vJoy-Direct(按下后摇杆偏移跟随鼠标移动方向变化，按键抬起后摇杆偏移归0)。
    * 添加鼠标键功能，可以通过映射按键列表中的"Key2Mouse-"前缀的按键控制鼠标指针移动，同样通过"X轴速度"和"Y轴速度"来控制鼠标指针移动速度，速度1~15，1最慢。

#### ※ 注意: v1.3.6(Build 20240223)对部分按键名称进行了更改(按键名称变更列表可参考[KeyNameChanged wiki页面](https://github.com/Zalafina/QKeyMapper/wiki/KeyNameChanged))，可能出现无法加载旧版本配置文件的情况，建议更新此版本前备份保存可执行文件路径下的 keymapdata.ini 配置文件。可以根据新Release版本ZIP压缩包中的 CombinationSupportKeys.txt 文件中的按键名称编辑修改 keymapdata.ini 配置文件中原来的按键名称来继续使用旧配置文件。
* v1.3.6(Build 20240131)
    * UI控件整体布局变化。
    * 增加虚拟手柄类型选择(X360/DS4), 如果使用以前版本的设定文件时提示"从INI文件加载了无效的设定数据"，在程序路径下备份keymapdata.ini后，使用文本编辑工具对keymapdata.ini进行文本替换后可继续使用。替换内容：(A) -> (A/×)、(B) -> (B/○)、(X) -> (X/□)、(Y) -> (Y/△)
* v1.3.6(Build 20240125)
    * 增加了窗口显示切换键编辑框，可以用于更改显示和隐藏窗口到系统托盘的快捷键。
    * 用于匹配窗口标题的单行文本编辑框可以手动进行内容更改并保存到设定了，同一个进程可以保存多个不同的窗口标题设定了(同一进程最多保存9个不同标题的设定)，不同的标题会保存到<process.exe|TitleX>形式的设定中。再次保存同一进程名相同标题的设定会覆盖之前已经存在的设定。
    * 双击左侧进程列表后，如果进程名和标题与已经保存的设定完全匹配，会自动加载显示之前已经保存过的设定。
    * 界面上控件位置微调，设定选择列表放在了进程名和标题名文本框的下面。给虚拟手柄设定添加了GroupBox框。
    * 窗口可见状态下，每隔3秒自动刷新左侧显示的进程列表。
    * ADD按键右侧"»"勾选框添加按键序列可以支持"vJoy"开头的虚拟手柄按键。
    * "保存设定"按钮可以保存当前窗口位置，隐藏后重新显示窗口会显示在隐藏前的窗口位置。程序启动时按照上次保存设定时的窗口位置进行显示。
    * 使用"»"勾选框添加按键序列可以使用延时功能了。
    * 窗口标题加入Build Number显示。
    * 增加"音效"复选框，勾选后开始映射和停止映射时会播放音效。
    * 增加游戏手柄左/右摇杆控制鼠标指针的功能(Joy-LS2Mouse & Joy-RS2Mouse)。
* v1.3.6(Build 20240112)
    * 增加了固定的全局映射设定项(QKeyMapperGlobalSetting)，如果全局映射勾选了自动开始映射，开始映射状态下从匹配的窗口退出后过几秒时间会自动切换到全局映射设定并启用映射。为全局映射状态加了一个专门的托盘图标。
* v1.3.6(Build 20240106)
    * 增加了原始快捷键编辑框，可以将包含Ctrl、Shift、Alt按键的组合键设定为原始输入(原始按键下拉框为空时，才会添加原始快捷键编辑框中的设定按键)。
    * 增加了按键映射停止时的音效。
* v1.3.6(Build 20231230)
    * 为映射按键增加"延时"数值调节框，可以适当增加组合按键之间的按下和抬起时的等待时间。
* v1.3.6(Build 20231225)
    * 添加"锁定光标"复选框，勾选后鼠标控制虚拟游戏手柄摇杆时鼠标光标被锁定在屏幕右下角位置(使用此功能前请提前确认映射开关组合键可用，避免鼠标无法移动也无法关闭按键映射恢复鼠标移动)。
    * 添加鼠标滚轮上滚和下滚映射功能。
* v1.3.6(Build 20231223)
    * 添加了通过鼠标控制虚拟游戏手柄左/右摇杆的功能(Mouse2Joystick)，通过在映射表中添加"vJoy-Mouse2LS"或"vJoy-Mouse2RS"来使用。鼠标控制摇杆的X轴和Y轴灵敏度范围"1~1000"，数值越小越灵敏。
    * "自动映射并最小化" 按钮变为三态复选框，设置为中间状态时软件启动仅最小化到托盘，不自动开始按键映射。
* v1.3.6(Build 20231220)
    * 添加了虚拟游戏手柄功能(通过ViGEmBus实现)，点击"安装ViGEmBus"，显示绿色字"ViGEmBus可用"之后，勾选"启用虚拟手柄"，之后可以将键盘按键映射到"vJoy"开头的虚拟手柄按键。
* v1.3.6(Build 20231125)
    * 添加了将游戏手柄按键作为原始按键映射到键盘按键的功能，原始按键列表中选择"Joy"开头的按键，映射按键选择想触发的键盘按键即可。
* v1.3.5(Build 20230806)
    * 切换映射开始和停止的快捷键，可以通过KeySequenceEdit控件进行自定义设置，鼠标点击KeySequenceEdit控件后按下想要设置的快捷键，此自定义快捷键设置每个配置可以保存设置不同值。
* v1.3.5(Build 20230805)
    * 添加可以直接在任意状态下切换映射开始和停止的快捷键，按下"Ctrl + F6"快捷键，无论在前台或者托盘显示状态都可以在开始映射和停止映射状态之间立即切换。
* v1.3.5
    * 添加中文界面，可以使用语言切换下拉列表进行中英文界面切换，适配4K/2K/1K分辨率。
* v1.3.3
    * 按键列表中添加了对鼠标侧键XButton1和XButton2的支持。
* v1.3.3
    * 在ADD按键右侧增加了"»"勾选框，用于添加按键序列，例如: Ctrl + X 之后 Ctrl + S，设置后效果参考README中显示的截图。
* v1.3.2
    * 在"KeyMappingStart"(循环检测)状态下，如果检测到到前台窗口与当前SelectSetting的按键映射配置设定一致时候会播放一个音效提示进入到按键映射生效状态。
* v1.3.1
    * 加入单例进程支持，只能同时运行一个QKeyMapper程序, 运行第二个QKeyMapper程序时会将第一个运行的实例程序窗口显示到前台。
* v1.3.1
    * "Auto Startup"勾选框可以让QKeyMapper按键映射程序在Windows用户登录的时候自动启动，配合"Auto Start Mapping"勾选框开机启动后可以自动最小化到系统托盘图标，取消勾选框则取消开机登录自动启动。
* v1.3.0
    * 开始支持"SaveMapData"可以将多个程序的不同按键映射配置都保存到"keymapdata.ini"文件中。如果配置了"Auto Start Mapping"功能，那么在"KeyMappingStart"状态下会根据当前前台窗口的进程可执行文件名进行自动匹配切换到对应的按键映射配置。
---------------
### 基本功能列表
1. 左侧显示当前正在运行的可见的窗口进程列表，进程可执行exe文件的文件名和对应的窗口标题名都会显示出来，信息会用于匹配当前处于前台的窗口。
2. 鼠标左键双击左侧窗口程序列表的某一行可以将选定的窗口程序的可自行文件名和窗口标题设定到图标/文件名/窗口标题区域。
3. 按下"KeyMappingStart"按钮可以开始执行按键映射处理流程，映射工具会定时循环检测当前处于前台的窗口与设定的可自行文件名和窗口标题是否匹配，按键映射功能可以只在前台窗口与当前进程可执行文件名和窗口标题都匹配的情况才生效，前台窗口不匹配的情况下按键映射自动失效。
4. 支持在右侧添加和删除按键映射表，下拉列表获取焦点时按下特定键盘按键可以自动将按键名设置到下拉列表上。
5. "SaveMapData"按钮会将按键映射表中的信息和进程及窗口标题信息保存到同一路径下的ini设定文件中，之后按键映射工具下次启动时可以自动加载同一路径下的"keymapdata.ini"文件读取已保存的设定值。
6. 按下"Ctrl + `"组合键会自动将QKeyMapper最小化显示到任务栏的系统程序托盘上，左键双击程序托盘图标会恢复显示程序窗口。
7. 将多个按键映射到同一个原始按键会按照"A + B"的形式来显示在按键映射表中，以此来支持用一个原始按键来同时映射多个按键。
8. 加入了"禁用WIN键"功能可以让键盘上的Windows按键在游戏中无效。
9. 右侧按键映射表中加入了连发(Burst)选择框，可以按照设定的连发按下时间(BurstPress)和连发抬起时间(BurstRelease)设定来反复发送映射表中的按键。
10. 右侧按键映射表中加入了锁定(Lock)选择框，选择后第一次按下对应的原始按键后会保持此按键的按下状态，再次按下此原始按键后接触锁定状态，支持与连发(Burst)选择框来组合使用，映射表中的Lock列的ON和OFF表示当前按键锁定状态。
11. 加入了"Auto Start Mapping"功能可以让程序启动后自动根据加载的配置文件开始按键映射，并且最小化到系统托盘, 。
12. 增加了SelectSetting下拉列表，可以保存最多10组不同的设定，并且通过下拉列表随时切换。
13. 增加了支持将鼠标左键&右键&中键映射到各种按键。

---------------
## 软件截图
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_screenshot_02.png)
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_screenshot_03.png)
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_screenshot_04.png)

---------------
## XBox手柄按键名称布局参照图
<div align="center"><img src="https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/XBox_Controller_layout_en.png" width="700" height="auto"/></div>
<div align="center"><img src="https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/XBox_Controller_layout_cn.png" width="700" height="auto"/></div>

---------------
## VirScan result
![Screenshot](https://raw.githubusercontent.com/Zalafina/QKeyMapper/master/screenshot/QKeyMapper_VirScan.png)
